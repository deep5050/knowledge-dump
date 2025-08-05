## **complex data types** 

| **Complex Data Type**               | **Syntax**                                                                                     | **Description**                                                                                     |
|-------------------------------------|------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------|
| **Array of Pointers**               | `type **arrayName[size];`                                                                     | An array where each element is a pointer to a variable of type `type`.                             |
| **Example**                         | `int *arr[10];`                                                                                | An array of 10 pointers to integers.                                                                |
| **Pointer to Array**               | `type (*pointerName)[size];`                                                                  | A pointer that points to an entire array of type `type`.                                           |
| **Example**                         | `int (*ptr)[5];`                                                                                | A pointer to an array of 5 integers.                                                                |
| **Function Pointer**                | `returnType (*pointerName)(parameterTypes);`                                                 | A pointer that points to a function with a specific return type and parameter types.               |
| **Example**                         | `void (*funcPtr)(int, float);`                                                                | A pointer to a function that takes an `int` and a `float` and returns `void`.                      |
| **Array of Function Pointers**     | `returnType (*arrayName[size])(parameterTypes);`                                             | An array where each element is a pointer to a function with a specific return type and parameter types. |
| **Example**                         | `void (*funcArr[10])(int, float);`                                                            | An array of 10 pointers to functions that take an `int` and a `float` and return `void`.          |
| **Pointer to Pointer**              | `type **pointerName;`                                                                          | A pointer that points to another pointer of type `type`.                                           |
| **Example**                         | `int **ptr;`                                                                                   | A pointer to a pointer to an integer.                                                                |
| **Array of Structures**             | `struct typeName arrayName[size];`                                                            | An array where each element is a structure of type `typeName`.                                     |
| **Example**                         | `struct Student { char name[50]; int age; }; struct Student students[100];`                  | An array of 100 `Student` structures.                                                                |
| **Pointer to Structure**            | `struct typeName *pointerName;`                                                               | A pointer that points to a structure of type `typeName`.                                           |
| **Example**                         | `struct Student *ptr;`                                                                          | A pointer to a `Student` structure.                                                                  |
| **Array of Pointers to Structures** | `struct typeName *arrayName[size];`                                                           | An array where each element is a pointer to a structure of type `typeName`.                        |
| **Example**                         | `struct Student *students[100];`                                                               | An array of 100 pointers to `Student` structures.                                                  |

### Key Points
- **Array of Pointers** and **Pointer to Array** are useful for managing dynamic data structures.
- **Function Pointers** and **Array of Function Pointers** enable flexible function calls and callbacks.
- **Pointer to Pointer** is often used in dynamic memory allocation scenarios, such as creating a 2D array.
- **Array of Structures** and **Pointer to Structure** are essential for organizing related data in a structured manner.
- **Array of Pointers to Structures** allows for dynamic management of collections of structures, enhancing flexibility in data handling.
