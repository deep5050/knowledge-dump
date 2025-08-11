## Problem Statement: Length of Last Word

Given a string `s` consisting of words and spaces, return the length of the last word in the string. A word is defined as a maximal substring consisting of non-space characters only. If there are no words in the string, return 0.

### Example:
- Input: `"Hello World"`
- Output: `5` (The last word is "World")

- Input: `"   "`
- Output: `0` (There are no words)

### Constraints:
- The input string `s` has a length in the range of [0, 10^4].

## C++ Code

Here is a simple C++ implementation to solve the problem:

```cpp
#include <iostream>
#include <string>
#include <algorithm>

int lengthOfLastWord(const std::string& s) {
    int length = 0;
    int i = s.size() - 1;

    // Skip trailing spaces
    while (i >= 0 && s[i] == ' ') {
        i--;
    }

    // Count the length of the last word
    while (i >= 0 && s[i] != ' ') {
        length++;
        i--;
    }

    return length;
}

int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);
    int result = lengthOfLastWord(input);
    std::cout << "Length of the last word: " << result << std::endl;
    return 0;
}
```

## Complexity Analysis

### Time Complexity
- The time complexity of this solution is **O(n)**, where `n` is the length of the string `s`. This is because we may need to traverse the entire string in the worst case to find the last word.

### Space Complexity
- The space complexity is **O(1)** since we are using a constant amount of extra space regardless of the input size. We only use a few integer variables for counting and indexing.

## Tricks for the Solution

1. **Skip Trailing Spaces**: The first step is to skip any trailing spaces in the string. This ensures that we start counting the last word correctly.

2. **Count Backwards**: By counting backwards from the end of the string, we can easily identify the last word without needing to split the string into words.

3. **Single Pass**: The algorithm only requires a single pass through the string, making it efficient for larger inputs.

4. **Edge Cases**: The solution handles edge cases such as empty strings or strings with only spaces by returning 0, ensuring robustness.

This approach is efficient and straightforward, making it a good solution for the problem.
