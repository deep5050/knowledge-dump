## A cheatsheet for the initial code flow of the Linux kernel on an x86 machine:


1. **Bootloader** (e.g. GRUB) loads kernel into memory
	* Loaded into physical address 0x100000 (assuming x86)
2. **Kernel decompression**: kernel image is decompressed
	* `arch/x86/boot/header.S`: contains boot header
	* `arch/x86/boot/compressed/decompress.c`: decompression code
3. **start_kernel()**: kernel initialization function
	* `init/main.c`: entry point of kernel initialization
4. **setup_arch()**: architecture-specific initialization
	* `arch/x86/kernel/setup.c`: x86-specific initialization
5. **mm_init()**: memory management initialization
	* `mm/init.c`: memory management initialization
6. **fs_init()**: file system initialization
	* `fs/fs.c`: file system initialization
7. **initcalls**: execute kernel modules' initialization functions
	* `init/main.c`: execute initcalls
8. **scheduler**: start kernel threads and scheduler
	* `kernel/sched.c`: scheduler implementation
9. **init process**: start init process (PID 1)
	* `init/init.c`: init process implementation
10. **user space**: execute user-space programs
	* `init/init.c`: execute user-space programs

Key functions:

* `start_kernel()`: `init/main.c`
* `setup_arch()`: `arch/x86/kernel/setup.c`
* `mm_init()`: `mm/init.c`

Key data structures:

* `struct task_struct`: `include/linux/sched.h`
* `struct mm_struct`: `include/linux/mm.h`

Note: This is a high-level overview of the kernel's initial code flow. There are many details and nuances that are not included here.
