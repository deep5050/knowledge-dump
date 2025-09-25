## Embedded‑Linux Boot Sequence

### 1. Hardware Reset / Power‑On  
- **SoC reset logic** brings the processor into a known state.  
- **Boot ROM** (often in on‑chip ROM) runs first‑stage code.

### 2. First‑Stage Bootloader (e.g., SPL, X‑loader)  
| Task | Typical implementation |
|------|------------------------|
| Initialize minimal hardware (clocks, DDR, UART) | Bare‑metal C/assembly; sets up DRAM controller so RAM can be used |
| Load second‑stage bootloader from storage (eMMC, SD, NAND, SPI flash) | Reads raw sectors or uses a simple filesystem (FAT, raw NAND) |
| Verify image (checksum, signature) | Optional security step |
| Jump to second‑stage bootloader | Passes control with CPU registers set for execution in RAM |

*Examples*: U‑Boot SPL, ARM Trusted Firmware (BL1/BL2), RedBoot, Barebox SPL.

### 3. Second‑Stage Bootloader (U‑Boot, Barebox, etc.)  
- **Full hardware init**: clocks, pin‑mux, Ethernet, USB, display, etc.  
- **Environment handling**: reads boot arguments from flash or EEPROM.  
- **Load kernel image** (`zImage`, `uImage`, `Image`) and **initramfs** (or separate rootfs) into RAM.  
- **Set up device tree** (`*.dtb`) describing the hardware to the kernel.  
- **Pass boot parameters** (cmdline, dtb address) and **jump to kernel entry point**.

### 4. Linux Kernel Early Init (arch‑specific)  
1. **Decompress** kernel (if `zImage`).  
2. **Early console** (earlyprintk) for debugging.  
3. **Memory management**: page tables, zone init.  
4. **Parse device tree** to discover peripherals.  
5. **Initialize core subsystems** (interrupts, scheduler, early I/O).  
6. **Mount initramfs** (if present) as temporary root (`/`).

### 5. initramfs (`/init`) – Often Minimal for Embedded  
- May be a **busybox**‑based shell script.  
- Performs tasks specific to the board:  
  - **Root filesystem selection** (e.g., mount NFS, MMC, NAND, or overlayfs).  
  - **Decrypt / verify** partitions if secure boot is used.  
  - **Switch root** (`pivot_root`/`switch_root`) to the real root filesystem.  
- Executes the **init system** (PID 1).

### 6. Init System (usually `systemd` or `busybox init`)  
- Reads configuration from `/etc/inittab` (busybox) or systemd unit files.  
- Starts essential services tailored for embedded use:  
  - `udevd` – creates device nodes.  
  - `networkd` / `dhcpcd` – brings up Ethernet/Wi‑Fi.  
  - `mdev` or `systemd‑udevd` for hot‑plug.  
  - Application‑specific daemons (e.g., `mosquitto`, `lighttpd`, `rtsp-server`).  
- May launch a **graphical stack** (Qt, Wayland) or directly start the main application.

### 7. Application / User Space  
- The **main embedded application** runs as a foreground service or via an init script.  
- Often a single binary (e.g., a control loop) that interacts with GPIO, I²C, SPI, etc.  
- System may stay in this mode indefinitely until a reboot or power loss.

---

### Typical Flow Diagram for an Embedded Board

```
Power‑On → SoC ROM (first‑stage bootloader) → SPL / X‑loader
      → Full bootloader (U‑Boot) → Load kernel + dtb + initramfs
      → Kernel early init (device tree parsing)
      → initramfs /init → switch to real rootfs
      → init system (systemd / busybox) → start services
      → Embedded application(s)
```

**Key differences from a PC boot**  

- **Two‑stage bootloader** is common because the SoC starts with only on‑chip SRAM; the SPL brings up DRAM before the full bootloader can run.  
- **Device tree** is essential to describe hardware that the kernel cannot probe automatically.  
- **initramfs** is often tiny, sometimes omitted entirely if the root filesystem resides on a ready‑to‑mount partition.  
- **Security** (secure boot, signed images, encrypted partitions) is frequently integrated into the early boot stages.  


-----------------------------------

## Typical x86 Linux Kernel Entry Points  

| Stage | Source file (arch/x86) | Symbol / Function | What it does |
|-------|------------------------|-------------------|--------------|
| **Early boot (real‑mode)** | `boot/compressed/head_64.S` (or `head_32.S` for 32‑bit) | `start_kernel` **is not reached yet** – the very first code executed is the **boot stub** `start` (real‑mode entry) that sets up a minimal environment, switches to protected/long mode, and jumps to the compressed kernel image. |
| **Decompression entry** | `arch/x86/boot/compressed/misc.c` | `decompress_kernel` (called from the boot stub) – inflates the `vmlinux` image into its final load address. |
| **Kernel proper entry** | `arch/x86/kernel/head_64.S` (64‑bit) / `head_32.S` (32‑bit) | `start_kernel` (C function) – the first C‑level entry point after the assembly bootstrap. |
| **C entry point** | `arch/x86/kernel/init.c` | `start_kernel(void)` | Initializes core subsystems: <br>• `setup_arch()` – parses the boot parameters and device tree. <br>• `mm_init()` – sets up memory management. <br>• `sched_init()` – initializes the scheduler. <br>• `rest_init()` – creates the first kernel thread (`kernel_thread`) that runs `kernel_init_freeable()`. |
| **First kernel thread** | `init/main.c` | `kernel_init_freeable(void *unused)` (called via `kernel_thread`) | Continues initialization after the scheduler is up: <br>• Calls `do_basic_setup()` (module init, console init). <br>• Starts the **init** process (`/sbin/init`) via `kernel_thread(init, NULL, CLONE_FS | CLONE_SIGHAND | CLONE_FILES)`. |
| **Init process (PID 1)** | `init/main.c` | `init(void *unused)` | The userspace‑style init thread that eventually execs the real init program (`/sbin/init` or systemd). It also runs `do_initcalls()` which executes all initcall levels (`pure_initcall`, `core_initcall`, `postcore_initcall`, …). |
| **Interrupt/exception vectors** | `arch/x86/kernel/entry_64.S` (or `entry_32.S`) | `entry_SYSCALL_64`, `entry_INT80_compat`, `entry_IRQ` etc. | Assembly stubs that the CPU jumps to on system calls, hardware interrupts, and exceptions. They save registers, switch to the kernel stack, and call the corresponding C handlers (`do_syscall_64`, `do_IRQ`, `do_error_trap`). |

### Call‑flow Overview (64‑bit)

1. **Boot ROM / BIOS/UEFI** → loads the **boot stub** (`start` in `head_64.S`).  
2. Stub sets up **real‑mode → protected → long mode**, loads the compressed kernel image.  
3. `decompress_kernel` inflates the image at its load address.  
4. Execution continues at the **assembly entry point** `startup_64` → jumps to `start_kernel`.  
5. `start_kernel` (C) performs architecture‑specific setup, memory, scheduler, etc.  
6. `rest_init()` creates the first kernel thread that runs `kernel_init_freeable`.  
7. `kernel_init_freeable` finishes early init, then spawns the **init** task (`init`).  
8. `init` runs all initcalls and finally execs the userspace init program (systemd, SysVinit, etc.).  

The same logical flow exists on 32‑bit x86, but the files are `head_32.S`, `entry_32.S`, and the entry point is still `start_kernel` defined in `arch/x86/kernel/init.c`.
