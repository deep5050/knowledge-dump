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


```


Set a bit          : x |= (1U << n)               // OR‑in the mask
Clear a bit        : x &= ~(1U << n)              // AND‑out the inverted mask
Toggle a bit       : x ^= (1U << n)               // XOR flips bits
Check a bit        : (x & (1U << n)) != 0         // AND gives mask, non‑zero = set

Isolate lowest set bit : x & -x   (or x & (~x + 1))
Clear lowest set bit   : x &= x - 1

Count set bits (Kernighan):
    cnt = 0;
    while (v) { v &= v - 1; cnt++; }

Parity (odd/even # of 1s):
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x &= 0xF;
    parity = (0x6996 >> x) & 1;

Swap two ints without temp:
    a ^= b; b ^= a; a ^= b;

Reverse bits (32‑bit) – mask‑shift‑or pattern:
    rev = ((x>>1)&0x55555555) | ((x&0x55555555)<<1);
    rev = ((rev>>2)&0x33333333) | ((rev&0x33333333)<<2);
    rev = ((rev>>4)&0x0F0F0F0F) | ((rev&0x0F0F0F0F)<<4);
    rev = ((rev>>8)&0x00FF00FF) | ((rev&0x00FF00FF)<<8);
    rev = (rev>>16) | (rev<<16);

Power of two test : (x != 0) && ((x & (x - 1)) == 0)

Round up to next power of two:
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x++;

Flip count between a and b : popcount(a ^ b)

Get sign mask (0 or -1) : mask = x >> (sizeof(int)*8 - 1)

Absolute value without branch:
    mask = x >> (sizeof(int)*8 - 1);
    abs  = (x + mask) ^ mask;

```
