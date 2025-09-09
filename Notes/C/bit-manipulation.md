## **Bit manipulation** in C

| **Operation**          | **Description**                                         | **Syntax**                          | **Example**                          |
|------------------------|---------------------------------------------------------|-------------------------------------|--------------------------------------|
| **Bitwise AND**        | Compares each bit of two numbers; sets the bit to 1 if both bits are 1. | `result = a & b;`                  | `5 & 3` results in `1` (0101 & 0011 = 0001) |
| **Bitwise OR**         | Compares each bit of two numbers; sets the bit to 1 if at least one bit is 1. | `result = a \| b;`                  | `5 \| 3` results in `7` (0101 \| 0011 = 0111) |
| **Bitwise XOR**        | Compares each bit of two numbers; sets the bit to 1 if the bits are different. | `result = a ^ b;`                  | `5 ^ 3` results in `6` (0101 ^ 0011 = 0110) |
| **Bitwise NOT**        | Inverts all the bits of a number.                      | `result = ~a;`                     | `~5` results in `-6` (in 32-bit: 11111111 11111111 11111111 11111010) |
| **Left Shift**         | Shifts bits to the left, filling with 0s; effectively multiplies by 2 for each shift. | `result = a << n;`                 | `5 << 1` results in `10` (0101 becomes 1010) |
| **Right Shift**        | Shifts bits to the right; fills with 0s for unsigned, sign bit for signed. | `result = a >> n;`                 | `5 >> 1` results in `2` (0101 becomes 0010) |
| **Set a Bit**          | Sets a specific bit to 1.                              | `a \|= (1 << n);`                   | To set the 1st bit of `a`: `a \|= (1 << 1);` |
| **Clear a Bit**        | Clears a specific bit (sets it to 0).                  | `a &= ~(1 << n);`                  | To clear the 1st bit of `a`: `a &= ~(1 << 1);` |
| **Toggle a Bit**       | Toggles a specific bit (changes 1 to 0 and 0 to 1).   | `a ^= (1 << n);`                   | To toggle the 1st bit of `a`: `a ^= (1 << 1);` |
| **Check a Bit**        | Checks if a specific bit is set (1).                   | `if (a & (1 << n)) { /* bit is set */ }` | To check the 1st bit of `a`: `if (a & (1 << 1))` |

### Key Points
- **Bitwise operations** are fundamental for low-level programming, allowing for efficient data manipulation.
- **Shifting operations** can be used for quick multiplication or division by powers of two.
- **Setting, clearing, toggling, and checking bits** are essential techniques for managing flags and binary states in applications.

> NOTE:

Left Shift: Increases the bit count because it **adds zeros to the right**, effectively **multiplying the number.**

Right Shift: ** May decrease the bit count** as bits are shifted out, effectively **dividing the number**
