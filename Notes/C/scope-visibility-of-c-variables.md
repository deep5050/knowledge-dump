## **scope and visibility of C variables**, focusing on the storage classes: **extern**, **static**, **auto**, and **register**. The information is organized in a table format for clarity.

| **Storage Class** | **Description**                                                                 | **Scope**                          | **Visibility**                     | **Lifetime**                     | **Example**                                   |
|--------------------|---------------------------------------------------------------------------------|------------------------------------|------------------------------------|----------------------------------|-----------------------------------------------|
| **extern**         | Used to declare a variable that is defined in another file or scope.           | Global (file scope)                | Accessible from any file that declares it. | Exists for the duration of the program. | `extern int globalVar;`                      |
| **static**         | Limits the visibility of a variable to the file or function where it is declared. | Local (function scope) or global (file scope) | Not visible outside its scope.    | Exists for the duration of the program. | `static int count = 0;`                      |
| **auto**           | Default storage class for local variables.                                      | Local (block scope)                | Limited to the block where declared. | Exists until the block is exited. | `int x = 10;` (implicitly auto)              |
| **register**       | Suggests that a variable be stored in a CPU register for faster access.        | Local (block scope)                | Limited to the block where declared. | Exists until the block is exited. | `register int speed;`                         |

### Key Points
- **extern** is used for variables that need to be shared across multiple files, promoting modular programming.
- **static** can be used to maintain state across function calls without exposing the variable outside its intended context, either at the function level or file level.
- **auto** is the default for local variables, meaning they are automatically allocated and deallocated as the program enters and exits the block.
- **register** is a hint to the compiler to optimize variable access speed, but it does not guarantee that the variable will be stored in a register.

