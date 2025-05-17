### when we build custom application/kernel modules, we include various .h files. how does the compiler know where to find those .h files?

When building a custom application or kernel module in Linux that includes various `.h` (header) files, the compiler needs to know where to find these header files for proper compilation. The compiler uses a set of predefined paths to search for header files, including:

1. **Standard Include Directories**:
   - The compiler automatically searches standard system directories like `/usr/include` for header files.

2. **Additional Include Directories**:
   - You can specify additional directories using the `-I` flag to tell the compiler where to look for header files. For example:
     ```bash
     gcc -I/path/to/include/dir my_program.c -o my_program
     ```

3. **Environment Variables**:
   - Environment variables like `C_INCLUDE_PATH` or `CPLUS_INCLUDE_PATH` can be set to specify additional directories for header file search.

4. **Build System Configuration**:
   - Build systems like Makefiles can define include paths using variables like `CFLAGS` or `CPPFLAGS` to ensure the compiler finds the necessary header files.

By setting these paths appropriately, you can ensure that the compiler locates and includes the required header files during the compilation process of your custom application or kernel module in Linux.

Citations:
[1] https://www.semanticscholar.org/paper/0544e6ee225eaca15b2cf88c40fc72d1bc0cd2c3
[2] https://www.semanticscholar.org/paper/dcd3e924d212a47b8cb2aa1247003f3d611c0d31
[3] https://www.semanticscholar.org/paper/7d0eb978c59867ce884ca880db9bd8eac14d32eb
