## **dynamic allocation techniques** in C
| **Technique**                | **Function**                     | **Description**                                         | **Example**                          |
|------------------------------|----------------------------------|---------------------------------------------------------|--------------------------------------|
| **Allocate Memory**          | `malloc(size_t size)`           | Allocates a specified number of bytes and returns a pointer to the allocated memory. The memory is uninitialized. | `int *arr = (int *)malloc(5 * sizeof(int));` |
| **Allocate and Initialize**   | `calloc(size_t num, size_t size)` | Allocates memory for an array of `num` elements of `size` bytes each and initializes all bytes to zero. | `int *arr = (int *)calloc(5, sizeof(int));` |
| **Reallocate Memory**        | `realloc(void *ptr, size_t size)` | Resizes the memory block pointed to by `ptr` to `size` bytes. If the new size is larger, the additional memory is uninitialized. | `arr = (int *)realloc(arr, 10 * sizeof(int));` |
| **Free Memory**              | `free(void *ptr)`               | Deallocates the memory previously allocated by `malloc`, `calloc`, or `realloc`. | `free(arr);` frees the allocated memory for the array. |
| **Allocate for Structures**  | `malloc` or `calloc`            | Use `malloc` or `calloc` to allocate memory for structures dynamically. | `struct Student *s = (struct Student *)malloc(sizeof(struct Student));` |
| **Dynamic 2D Array**         | `malloc` with pointer to pointer | Allocate a dynamic 2D array using an array of pointers. | `int **matrix = (int **)malloc(rows * sizeof(int *)); for (int i = 0; i < rows; i++) matrix[i] = (int *)malloc(cols * sizeof(int));` |
| **Dynamic Array of Structures** | `malloc` or `calloc`          | Allocate an array of structures dynamically. | `struct Student *students = (struct Student *)malloc(numStudents * sizeof(struct Student));` |

### Key Points
- **Dynamic memory allocation** allows for flexible memory usage, enabling the creation of data structures whose size can change at runtime.
- **`malloc`** allocates memory without initialization, while **`calloc`** allocates and initializes memory to zero.
- **`realloc`** is useful for resizing previously allocated memory blocks, allowing for dynamic growth of data structures.
- Always remember to **`free`** dynamically allocated memory to prevent memory leaks.
