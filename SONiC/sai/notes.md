## SAI
The best way to think about the difference is through the lens of **Standardization vs. Specialization**.

If you were building a car, the **SAI** is the steering wheel, pedals, and gear shift—it looks and acts the same regardless of the car. The **SDK** is the specific engine, transmission, and fuel injection system designed by the manufacturer to make the car actually move.

---

## The Comparison Table

| Feature | Switch Abstraction Interface (SAI) | Software Development Kit (SDK) |
| :--- | :--- | :--- |
| **Owner** | Open Compute Project (OCP) / Community | ASIC Vendor (Broadcom, NVIDIA/Mellanox, Intel) |
| **Accessibility** | **Open Source.** Anyone can see the API definitions. | **Proprietary.** Usually requires an NDA to access. |
| **Scope** | **Northbound.** Standardizes how an OS talks to a switch. | **Southbound.** Handles hardware registers and DMA. |
| **Portability** | **High.** Code written for SAI works on any supported ASIC. | **Zero.** SDK code for Broadcom won't work on Intel. |
| **Focus** | Networking logic (VLANs, Routes, ACLs). | Hardware management (SerDes, Buffers, TCAM). |

---

## 1. Switch Abstraction Interface (SAI)
SAI was created to solve the "Vendor Lock-in" problem. Before SAI, if you wrote a Network Operating System (NOS) for a Broadcom chip, you couldn't run it on a Barefoot/Intel chip without rewriting the entire hardware interface.

* **The "What":** It defines a set of C-style APIs (e.g., `sai_create_route_entry`).
* **The Benefit:** It allows OS developers (like those working on **SONiC**) to write their code once. As long as the hardware vendor provides a SAI-compliant driver, the OS just works.
* **The Pipeline:** SAI views the switch as a logical pipeline of tables (Ingress -> Lookup -> Egress).



---

## 2. Software Development Kit (SDK)
The SDK is the low-level toolkit provided by the silicon manufacturer. It is the only way to actually "touch" the hardware.

* **The "How":** It contains the logic to program the specific registers, memory addresses, and cooling fans of a specific chip.
* **The Complexity:** SDKs are massive and complex. They handle the "gritty" details like how long to wait for a SerDes to lock or how to partition the physical TCAM memory into different slices.
* **The Implementation:** In a modern switch, the **SAI layer is actually a "wrapper" around the SDK**. When you call a SAI function, that function internally calls 5–10 SDK functions to get the job done.

---

## How they work together
Imagine you want to set a port to 100G speed:

1.  **NOS (SONiC):** Decides a port needs to be 100G. It calls the standard SAI function: `set_attribute(SAI_PORT_ATTR_SPEED, 100000)`.
2.  **SAI Adapter:** This is the vendor's code. it receives the SAI call and translates it into a Broadcom-specific command: `bcm_port_speed_set(unit, port, 100000)`.
3.  **SDK:** The Broadcom SDK takes that command, calculates the correct voltage and clock frequency for the hardware, and writes the bits to the physical registers on the chip.
4.  **ASIC:** The hardware physics change, and the port lights up at 100G.

Without SAI, the NOS would have to call `bcm_port_speed_set` directly, meaning that OS would be "locked" to Broadcom forever.

## The "User-Space" vs. "Kernel-Space" Split
This is where it gets interesting for an ASIC developer. Most of the "intelligence" is NOT in the driver.

### The Driver (Kernel):
Is kept as "thin" as possible. Its only job is to provide a stable pipe to the hardware and handle interrupts/DMA.

### The SDK (User-Space): 
This is where the millions of lines of code live. ASIC vendors prefer putting the logic here because it's easier to debug, doesn't crash the whole OS if it fails, and allows them to keep their IP (Intellectual Property) in a private library rather than open-sourcing it in the Linux kernel.

## SAI SDK distribution
`dpkg-deb -c libsaibcm_11.2.8.1_amd64.deb`

`-rw-r--r-- root/root 422262920 2025-12-10 11:15 ./usr/lib/libsai.so.1.0`

### The Distribution Flow
Vendor Side: You compile your SAI adapter against your private SDK.

Packaging: You wrap the .so, the kernel drivers, and the firmware into a Debian package (.deb) or a Docker container.

Deployment: In an OS like SONiC, the "Syncd" container loads your libsai.so at runtime. When the SONiC database says "Add Route," Syncd calls your library, and your library talks to the Broadcom/Vendor ASIC.