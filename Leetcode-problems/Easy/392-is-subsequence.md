## Problem statement: LeetCode 392 - is subsequence

Given two strings s and t, return `true` if s is a subsequence of t, or `false` otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

 

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: `true`


Example 2:

Input: s = "axc", t = "ahbgdc"
Output: `false`
 

Constraints:

```
0 <= s.length <= 100
0 <= t.length <= 104
```


s and t consist only of lowercase English letters.
 

To determine if a string `s` is a subsequence of another string `t`, you can use a two-pointer approach. A string `s` is considered a subsequence of `t` if you can remove some characters from `t` (without reordering the remaining characters) to get `s`.

## 📝 C++ Solution

Here’s a C++ solution to check if `s` is a subsequence of `t`:

```cpp
#include <iostream>
#include <string>

bool isSubsequence(const std::string& s, const std::string& t) {
    int sIndex = 0; // Pointer for string s
    int tIndex = 0; // Pointer for string t

    // Iterate through both strings
    while (sIndex < s.length() && tIndex < t.length()) {
        // If characters match, move the pointer in s
        if (s[sIndex] == t[tIndex]) {
            sIndex++;
        }
        // Always move the pointer in t
        tIndex++;
    }

    // If we have traversed all characters in s, it is a subsequence
    return sIndex == s.length();
}

int main() {
    std::string s = "abc";
    std::string t = "ahbgdc";
    bool result = isSubsequence(s, t);
    
    std::cout << "Is '" << s << "' a subsequence of '" << t << "'? " << (result ? "Yes" : "No") << std::endl;
    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Initialize Pointers**: Use two pointers, `sIndex` for string `s` and `tIndex` for string `t`, both starting at 0.
2. **Iterate Through Both Strings**: Use a while loop to traverse both strings:
   - If the characters at `sIndex` and `tIndex` match, increment `sIndex` to check the next character in `s`.
   - Always increment `tIndex` to continue checking characters in `t`.
3. **Check Completion**: After the loop, if `sIndex` equals the length of `s`, it means all characters in `s` were found in `t` in order, so return true.
4. **Return Result**: If not all characters in `s` were found, return false.

### 📊 Complexity:
- **Time Complexity**: O(n), where n is the length of string `t`, since we traverse `t` once.
- **Space Complexity**: O(1), as we are using a constant amount of extra space for pointers.

This solution efficiently checks if `s` is a subsequence of `t` using a straightforward two-pointer technique.
