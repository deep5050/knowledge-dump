Here's a step-by-step explanation of how a C program is loaded into memory on Linux:

### Compilation and Linking

When you compile a C program, the compiler (e.g., GCC) generates an object file that contains machine code, data, and relocation information. The linker (e.g., ld) then takes the object file and resolves external references to create an executable file.

### Program Loading

When you run the executable, the Linux kernel's program loader (ld-linux.so or ld-linux-x86-64.so for x86-64 systems) is responsible for loading the program into memory. Here's what happens:

1. **Executable File Format**: The executable file is in ELF (Executable and Linkable Format) format, which contains metadata, code, and data segments.
2. **Memory Mapping**: The loader creates a new process and maps the executable file into the process's virtual address space using `mmap()`. This creates a memory mapping that allows the kernel to load the file into memory.
3. **Segment Loading**: The loader loads the ELF segments into memory, including:
	* **.text** (code segment): contains the program's machine code.
	* **.data** (initialized data segment): contains initialized global and static variables.
	* **.bss** (uninitialized data segment): contains uninitialized global and static variables.
	* **.rodata** (read-only data segment): contains constant data, such as string literals.
4. **Relocation**: The loader performs relocation, which involves updating the addresses in the code and data segments to reflect the program's loading address in memory.
5. **Stack and Heap Initialization**: The loader initializes the process's stack and heap, which are used for function calls, local variables, and dynamic memory allocation.

### Memory Layout

The resulting memory layout for a C program on Linux is typically as follows:
```
  +---------------------------+
  |  Stack                    |
  +---------------------------+
  |  Heap                     |
  +---------------------------+
  |  .bss                     |
  |  (uninitialized data)     |
  +---------------------------+
  |  .data                    |
  |  (initialized data)       |
  +---------------------------+
  |  .rodata                  |
  |  (read-only data)         |
  +---------------------------+
  |  .text                    |
  |  (code segment)           |
  +---------------------------+
```
Note that this is a simplified overview of the process, and there are many details and nuances involved in loading a C program into memory on Linux.
