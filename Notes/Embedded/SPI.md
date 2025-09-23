## DTS – *Device Tree Source*  

In embedded Linux systems the kernel must know details about the hardware it runs on (CPU type, memory map, peripheral addresses, interrupt lines, etc.). Rather than hard‑coding this information into the kernel source, the **Device Tree** mechanism provides a separate, data‑only description of the hardware.  

The textual representation of that description is the **Device Tree Source (DTS)** file, which is compiled into a binary **Device Tree Blob (DTB)** and passed to the kernel at boot time.

### Why DTS is needed

| Reason | Explanation |
|--------|-------------|
| **Hardware abstraction** | The same kernel image can run on multiple board variants; only the DTS/DTB changes. |
| **Simplifies kernel maintenance** | Board‑specific code is removed from the kernel, reducing compile‑time and making upstream contributions easier. |
| **Supports dynamic configuration** | Different DTBs can be selected at boot (e.g., via bootloader) to match the actual board or to enable/disable features. |
| **Facilitates bootloader‑kernel hand‑off** | The bootloader loads the DTB into memory and provides its address to the kernel, eliminating the need for the kernel to probe hardware. |
| **Enables open‑source kernels on proprietary boards** | Vendors can ship a DTB without revealing proprietary driver code, while still using a mainline kernel. |

In practice, a DTS file describes nodes (devices) with properties such as `reg` (address/size), `interrupts`, `compatible` strings, and optional configuration parameters. The compiler (`dtc`) turns the DTS into a DTB, which the bootloader (e.g., U‑Boot) loads and passes to the kernel via the `bootargs` or a dedicated register.

Thus, DTS provides a clean, portable way to convey hardware layout to the kernel, making embedded Linux systems more modular and easier to maintain.

## Why a Device Tree isn’t needed on desktops
Standardized firmware interfaces – ACPI is the de‑facto hardware description language for x86/UEFI platforms. It is already a “device tree” of sorts, but it is supplied by the firmware at runtime, not compiled into a separate blob that the OS must load.
In contrast, desktop PCs (x86 architecture) have a standardized hardware environment defined by the Advanced Configuration and Power Interface (ACPI). ACPI tables, provided by the BIOS or UEFI firmware, contain all the information the operating system needs to manage and configure the hardware, including:

Device enumeration: Details about connected devices like PCI, USB, and memory controllers.

Power management: Information about how to control system power states.

Interrupt routing: How to route interrupts from devices to the CPU.

## How a Device Tree Source (DTS) Enables the Kernel to Load an Ethernet Driver

A Device Tree (DT) describes the hardware that is present on a board.  
When the kernel boots, it parses the compiled Device Tree Blob (DTB) and matches the nodes in the tree with driver modules that have registered compatible strings. If a match is found, the kernel loads (or probes) that driver and passes the resources described in the node (register addresses, interrupts, PHY information, etc.).

### Example DTS fragment for a typical Ethernet MAC

```dts
/ {
    /* ... other top‑level nodes ... */

    ethernet0: ethernet@40000000 {
        compatible = "myvendor,my-ethernet-mac";
        reg = <0x40000000 0x1000>;          /* base address + size */
        interrupts = <5>;                   /* IRQ number */
        phy-mode = "rgmii";                 /* interface type */
        phy-handle = <&phy0>;

        status = "okay";
    };

    phy0: phy@0 {
        compatible = "ethernet-phy-ieee802.3-c45";
        reg = <0>;                          /* PHY address on MDIO bus */
        /* optional PHY-specific properties */
    };
};
```

### What happens at boot

1. **DTB is passed to the kernel** – The bootloader (e.g., U‑Boot) loads the compiled DTB and supplies it to the kernel via the `bootargs` or `fdt` command line.
2. **Kernel parses the DTB** – The kernel’s `of` (Open Firmware) subsystem walks the tree.
3. **Driver matching** – The Ethernet MAC driver registers a table like:

   ```c
   static const struct of_device_id my_eth_of_match[] = {
       { .compatible = "myvendor,my-ethernet-mac", },
       {}
   };
   MODULE_DEVICE_TABLE(of, my_eth_of_match);
   ```

   The kernel finds the node `ethernet@40000000` whose `compatible` string matches this table.
4. **Driver probe** – The kernel calls the driver’s `probe()` function, passing a pointer to the device node. Inside `probe()`, the driver reads the `reg`, `interrupts`, `phy-mode`, and `phy-handle` properties to configure the hardware.
5. **Resource allocation** – The driver maps the memory region (`ioremap` of `0x40000000`), requests the IRQ, and registers the PHY using the handle `<&phy0>`.
6. **Network interface appears** – After successful initialization, the driver registers a network interface (e.g., `eth0`) with the networking stack, making the Ethernet port usable.

### Key DT properties used by the driver

| Property      | Purpose |
|---------------|---------|
| `compatible` | Matches driver to node |
| `reg`         | Physical address and size of the MAC registers |
| `interrupts`  | IRQ line the MAC uses |
| `phy-mode`    | Specifies the MAC‑PHY interface (RGMII, GMII, etc.) |
| `phy-handle`  | Links to the PHY node for MDIO configuration |
| `status`      | `"okay"` enables the node; `"disabled"` would skip it |

When any of these entries are missing or mismatched, the kernel will not bind the driver, and the Ethernet interface will remain unavailable. This illustrates how a DTS file directly guides the kernel to load and configure the correct Ethernet driver.
