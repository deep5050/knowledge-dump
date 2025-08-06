Given two strings `s` and `t`, _determine if they are isomorphic_.

Two strings `s` and `t` are isomorphic if the characters in `s` can be replaced to get `t`.

All occurrences of a character must be replaced with another character while preserving the order of characters. 
No two characters may map to the same character, but a character may map to itself.
**Example 1:**

**Input:** s = "egg", t = "add"

**Output:** true

**Explanation:**

The strings `s` and `t` can be made identical by:

- Mapping `'e'` to `'a'`.
- Mapping `'g'` to `'d'`.

**Example 2:**

**Input:** s = "foo", t = "bar"

**Output:** false

**Explanation:**

The strings `s` and `t` can not be made identical as `'o'` needs to be mapped to both `'a'` and `'r'`.

**Example 3:**

**Input:** s = "paper", t = "title"

**Output:** true

**Constraints:**

- `1 <= s.length <= 5 * 104`
- `t.length == s.length`
- `s` and `t` consist of any valid ascii character.

## C++ Implementation of Isomorphic Strings

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

bool areIsomorphic(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) {
        return false; // If lengths are different, they cannot be isomorphic
    }

    std::unordered_map<char, char> mapping1;
    std::unordered_map<char, char> mapping2;

    for (size_t i = 0; i < str1.length(); ++i) {
        char char1 = str1[i];
        char char2 = str2[i];

        // Check mapping from str1 to str2
        if (mapping1.find(char1) != mapping1.end()) {
            if (mapping1[char1] != char2) {
                return false; // Mismatch found
            }
        } else {
            mapping1[char1] = char2; // Create new mapping
        }

        // Check mapping from str2 to str1
        if (mapping2.find(char2) != mapping2.end()) {
            if (mapping2[char2] != char1) {
                return false; // Mismatch found
            }
        } else {
            mapping2[char2] = char1; // Create new mapping
        }
    }

    return true; // All characters mapped correctly
}

int main() {
    std::string str1 = "egg";
    std::string str2 = "add";

    if (areIsomorphic(str1, str2)) {
        std::cout << "The strings are isomorphic." << std::endl;
    } else {
        std::cout << "The strings are not isomorphic." << std::endl;
    }

    return 0;
}
```

### Explanation of the Code

1. **Function Definition**: The function `areIsomorphic` takes two strings as input and returns a boolean indicating whether they are isomorphic.
2. **Length Check**: It first checks if the lengths of the two strings are equal. If not, it returns `false`.
3. **Mapping Creation**: Two unordered maps (`mapping1` and `mapping2`) are used to store the character mappings from `str1` to `str2` and vice versa.
4. **Character Iteration**: The function iterates through each character of the strings:
   - It checks if the current character from `str1` is already mapped to a character in `str2`. If it is, it verifies that the mapping is consistent.
   - It does the same for the character from `str2` to `str1`.
5. **Return Value**: If all characters can be mapped correctly, the function returns `true`; otherwise, it returns `false`.

### Example Usage

In the `main` function, you can test the `areIsomorphic` function with different string pairs. The example provided checks if "egg" and "add" are isomorphic, which they are, so it will output:

```
The strings are isomorphic.
```

You can modify the strings in the `main` function to test other cases as needed.