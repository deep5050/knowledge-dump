## Problem Description: LeetCode 3 - Longest Substring Without Repeating Characters

Given a string `s`, find the length of the longest substring without repeating characters.

### Example:
- Input: `s = "abcabcbb"`
- Output: `3` (The longest substring without repeating characters is `"abc"`.)

- Input: `s = "bbbbb"`
- Output: `1` (The longest substring without repeating characters is `"b"`.)

- Input: `s = "pwwkew"`
- Output: `3` (The longest substring without repeating characters is `"wke"`.)

### Constraints:
- `0 <= s.length <= 5 * 10^4`
- `s` consists of English letters, digits, symbols, and spaces.

## C++ Code Implementation

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> charIndexMap; // Map to store the last index of each character
    int maxLength = 0; // Variable to store the maximum length of substring
    int start = 0; // Left pointer for the sliding window

    for (int i = 0; i < s.length(); i++) {
        // If the character is already in the map and its index is within the current window
        if (charIndexMap.find(s[i]) != charIndexMap.end() && charIndexMap[s[i]] >= start) {
            start = charIndexMap[s[i]] + 1; // Move the start pointer to the right of the last occurrence
        }

        charIndexMap[s[i]] = i; // Update the last index of the character
        maxLength = max(maxLength, i - start + 1); // Update the maximum length
    }

    return maxLength; // Return the maximum length found
}

int main() {
    string s = "abcabcbb";
    int result = lengthOfLongestSubstring(s);

    cout << "Length of longest substring without repeating characters: " << result << endl;
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the length of the string `s`. We traverse the string once, and each character is processed in constant time.

### Space Complexity
- The space complexity is **O(min(n, m))**, where `n` is the length of the string and `m` is the size of the character set. In the worst case, we may store all unique characters in the hash map.

## Key Concepts and Tricks

1. **Sliding Window Technique**: This problem is efficiently solved using the sliding window technique. By maintaining a window defined by two pointers (start and end), we can dynamically adjust the size of the window based on the characters encountered.

2. **Hash Map for Index Tracking**: We use a hash map to keep track of the last index of each character encountered. This allows for quick lookups to check if a character has been seen before and to adjust the start pointer accordingly.

3. **Dynamic Length Calculation**: As we iterate through the string, we continuously calculate the length of the current substring and update the maximum length found.

4. **Handling Edge Cases**: The algorithm naturally handles cases where the string is empty or contains all unique characters, returning the correct length in each scenario.

This approach efficiently finds the length of the longest substring without repeating characters, ensuring that we can determine the result in linear time with minimal space usage.
