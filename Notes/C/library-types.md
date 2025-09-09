## **shared libraries** vs **static libraries** 

| **Aspect**               | **Shared Library**                                         | **Static Library**                                         |
|--------------------------|-----------------------------------------------------------|-----------------------------------------------------------|
| **Definition**           | A library that is loaded into memory at runtime.         | A library that is linked into the executable at compile time. |
| **File Extension**       | Typically `.so` (shared object).                          | Typically `.a` (archive).                                 |
| **Linking**             | Dynamic linking occurs at runtime.                         | Static linking occurs at compile time.                    |
| **Memory Usage**         | Multiple programs can share a single copy in memory.     | Each program has its own copy, leading to higher memory usage. |
| **Updates**              | Easier to update; only the library file needs to be replaced. | Requires recompilation of all dependent programs to update. |
| **Performance**          | Slightly slower due to runtime linking overhead.          | Faster execution since all code is included in the executable. |
| **Size of Executable**   | Smaller executable size, as it references the shared library. | Larger executable size, as it contains all library code.  |
| **Dependency Management**| Can lead to "dependency hell" if versions are mismatched. | No external dependencies; all code is included.           |
| **Use Cases**            | Ideal for applications that require frequent updates or share common code. | Suitable for applications where performance is critical and updates are infrequent. |

### Key Points
- **Shared libraries** in Linux are beneficial for reducing memory usage and simplifying updates, making them ideal for applications that may need to change frequently.
- **Static libraries** provide better performance and create self-contained executables, which can be advantageous in environments where stability and speed are essential.

Here are examples of the `make` commands for compiling and linking both **shared libraries** and **static libraries** in a Linux environment.

### Shared Library Example

1. **Create a source file** (e.g., `mylib.c`):
   ```c
   // mylib.c
   #include <stdio.h>

   void hello() {
       printf("Hello from the shared library!\n");
   }
   ```

2. **Create a `Makefile`** for the shared library:
   ```makefile
   # Makefile for shared library
   CC = gcc
   CFLAGS = -fPIC
   LIBNAME = libmylib.so
   SOURCES = mylib.c
   OBJECTS = $(SOURCES:.c=.o)

   all: $(LIBNAME)

   $(LIBNAME): $(OBJECTS)
       $(CC) -shared -o $@ $^

   clean:
       rm -f $(OBJECTS) $(LIBNAME)
   ```

3. **Build the shared library**:
   ```bash
   make
   ```

### Static Library Example

1. **Create the same source file** (e.g., `mylib.c`):
   ```c
   // mylib.c
   #include <stdio.h>

   void hello() {
       printf("Hello from the static library!\n");
   }
   ```

2. **Create a `Makefile`** for the static library:
   ```makefile
   # Makefile for static library
   CC = gcc
   AR = ar
   CFLAGS = -c
   LIBNAME = libmylib.a
   SOURCES = mylib.c
   OBJECTS = $(SOURCES:.c=.o)

   all: $(LIBNAME)

   $(LIBNAME): $(OBJECTS)
       $(AR) rcs $@ $^

   clean:
       rm -f $(OBJECTS) $(LIBNAME)
   ```

3. **Build the static library**:
   ```bash
   make
   ```

### Summary of Commands
- To build the **shared library**, use `make` in the directory containing the `Makefile` for the shared library.
- To build the **static library**, use `make` in the directory containing the `Makefile` for the static library.

These examples illustrate how to create both types of libraries in a Linux environment using `make`.
