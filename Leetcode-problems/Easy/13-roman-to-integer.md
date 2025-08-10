## Problem Description: LeetCode 13 - Roman to Integer

Given a string representing a Roman numeral, convert it to an integer. The input is guaranteed to be within the range from 1 to 3999.

### Roman Numerals:
- I = 1
- V = 5
- X = 10
- L = 50
- C = 100
- D = 500
- M = 1000

### Example:
- Input: `s = "III"`
- Output: `3`

- Input: `s = "IV"`
- Output: `4`

- Input: `s = "IX"`
- Output: `9`

- Input: `s = "LVIII"`
- Output: `58` (L = 50, V = 5, III = 3)

- Input: `s = "MCMXCIV"`
- Output: `1994` (M = 1000, CM = 900, XC = 90, IV = 4)

### Constraints:
- The input string is guaranteed to be a valid Roman numeral within the range from 1 to 3999.

## C++ Code Implementation

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int romanToInt(string s) {
    unordered_map<char, int> romanMap = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };

    int total = 0;
    int prevValue = 0;

    for (int i = s.length() - 1; i >= 0; i--) {
        char currentChar = s[i];
        int currentValue = romanMap[currentChar];

        // If the current value is less than the previous value, subtract it
        if (currentValue < prevValue) {
            total -= currentValue;
        } else {
            total += currentValue;
        }

        prevValue = currentValue; // Update previous value
    }

    return total;
}

int main() {
    string s = "MCMXCIV";
    int result = romanToInt(s);
    cout << "Integer value: " << result << endl;
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the length of the string `s`. We traverse the string once to calculate the integer value.

### Space Complexity
- The space complexity is **O(1)**. We use a constant amount of extra space for the `unordered_map` and a few integer variables, regardless of the input size.

## Key Concepts and Tricks

1. **Mapping Roman Numerals**: Using a hash map (or unordered map in C++) allows for quick lookups of the integer values corresponding to each Roman numeral character.

2. **Reverse Traversal**: By traversing the string from right to left, we can easily handle the subtraction rule (e.g., IV = 4, IX = 9) by comparing the current numeral with the previous one.

3. **Handling Subtraction**: If the current numeral is less than the previous numeral, it indicates a subtraction scenario, which is efficiently handled in the loop.

4. **Valid Input Assumption**: The problem guarantees that the input will always be a valid Roman numeral, simplifying the implementation since we do not need to handle invalid cases.

This approach is efficient and straightforward, making it a common solution for converting Roman numerals to integers.
