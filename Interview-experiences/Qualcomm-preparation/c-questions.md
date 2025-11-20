# calculate the size of an integer with out using `sizeof()`:
To find the size of an `int` in C without using the `sizeof` operator, you can utilize pointer arithmetic. Here's how you can do it:

## Method Using Pointer Arithmetic

### Code Example

```c
#include <stdio.h>

int main() {
    // Create a type that is one byte
    char c;

    // Calculate the size of int by using pointer arithmetic
    int *p1 = (int*)&c; // Pointer to an int
    int *p2 = p1 + 1;   // Pointer to the next int

    // Calculate the size of int
    int size_of_int = (char*)p2 - (char*)p1;

    printf("Size of int: %d bytes\n", size_of_int);
    return 0;
}
```

### Explanation

1. **Pointer Creation**: We create a pointer to an `int` and then create another pointer `p2` that points to the next `int`.
2. **Pointer Arithmetic**: By subtracting the two pointers and casting them to `char*`, we calculate the difference in bytes.
3. **Output**: This gives the size of the `int` in bytes.

### Key Points
- The calculation `(char*)p2 - (char*)p1` gives the number of bytes between the two pointers.
- This effectively calculates the size of `int` without using the `sizeof` operator.

-----------------
