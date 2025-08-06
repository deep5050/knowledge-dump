To find the index of the first occurrence of a substring in a string without using any library functions, you can implement a simple algorithm that manually checks each position in the main string for a match with the substring.

## 📝 C++ Solution

Here’s a C++ solution that does this:

```cpp
#include <iostream>
#include <string>

int strStr(const std::string& haystack, const std::string& needle) {
    // If needle is empty, return 0
    if (needle.empty()) return 0;

    int haystackLength = haystack.length();
    int needleLength = needle.length();

    // Loop through the haystack
    for (int i = 0; i <= haystackLength - needleLength; i++) {
        // Check for a match
        int j;
        for (j = 0; j < needleLength; j++) {
            if (haystack[i + j] != needle[j]) {
                break; // Break if characters do not match
            }
        }
        // If we found a match
        if (j == needleLength) {
            return i; // Return the starting index
        }
    }

    return -1; // Return -1 if needle is not found
}

int main() {
    std::string haystack = "hello";
    std::string needle = "ll";
    int index = strStr(haystack, needle);
    
    std::cout << "Index of the first occurrence: " << index << std::endl;
    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Check for Empty Needle**: If the `needle` (substring) is empty, return 0.
2. **Loop Through Haystack**: Iterate through the `haystack` string up to the point where the remaining characters are enough to match the `needle`.
3. **Check for Match**: For each position in the `haystack`, check if the substring starting from that position matches the `needle`:
   - Use a nested loop to compare characters.
   - If a mismatch is found, break out of the inner loop.
4. **Return Index**: If a complete match is found (when the inner loop completes), return the starting index. If no match is found after checking all positions, return -1.

### 📊 Complexity:
- **Time Complexity**: O(n * m) in the worst case, where n is the length of the `haystack` and m is the length of the `needle`, as it may need to check each character.
- **Space Complexity**: O(1), as we are using a constant amount of extra space.

This solution effectively finds the index of the first occurrence of a substring in a string without using any library functions.