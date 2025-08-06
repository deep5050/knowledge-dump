##  **Memory Layout of a C Program**:

| **Segment**               | **Purpose**                                                                 | **Contents**                                                                 | **Growth Direction** | **Access Type**     |
|---------------------------|------------------------------------------------------------------------------|------------------------------------------------------------------------------|-----------------------|---------------------|
| **Text (Code)**           | Stores compiled program instructions                                        | Function code (`main()`, `printf()`, etc.)                                  | Fixed                 | Read-only           |
| **Initialized Data**      | Stores global/static variables with initial values                         | `int x = 5;`, `static int y = 10;`                                           | Fixed                 | Read/Write          |
| **Uninitialized Data (BSS)** | Stores global/static variables without initial values (usually filled with 0s)                    | `static int z;`, `int count;`                                               | Fixed                 | Read/Write          |
| **Heap**                  | Used for dynamic memory allocation                                          | `malloc()`, `calloc()`, `realloc()`                                         | Upward ⬆️            | Read/Write          |
| **Stack**                 | Stores local variables, function parameters, return addresses               | `int a;` inside a function, function call frames                            | Downward ⬇️          | Read/Write          |
| **Environment & Args**    | Stores command-line arguments and environment variables                     | `argv[]`, `envp[]`                                                           | Fixed                 | Read-only           |
