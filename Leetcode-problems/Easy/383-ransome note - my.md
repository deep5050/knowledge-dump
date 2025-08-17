## Problem Statement: LeetCode 383 - Ransom Note

You are given two strings, ransomNote and magazine. You need to determine if you can construct the ransomNote using the letters from the magazine. Each letter in the magazine can only be used once in the ransom note.

Example:

Input: ransomNote = "a" and magazine = "b"

Output: `false`


Input: ransomNote = "aa" and magazine = "ab"

Output: `false`


Input: ransomNote = "aa" and magazine = "aab"

Output: `true`

## code

```cpp
#include <iostream>
#include <string>
#include <map>

using namespace std;

bool func(string ran, string mag)
{
    map<char, int> memory;
    size_t i = 0;
    for (char c : mag) memory[c]++;
    for (i; i < ran.length(); i++)
    {
        if (memory.find(ran[i]) != memory.end())
        {
            // found one entry , decrement the count 
            if (memory[ran[i]] == 0) return false;
            memory[ran[i]]--;
        }
        else return false;
    }
    if (i == ran.length()) return true;
    else return false;
}

int main()
{
    string ransome = "a";
    string magazine = "ba";
    if (func(ransome, magazine)) cout << "OK" << endl;
    else cout << "NOT OK" << endl;
    return 0;
}
```

## Key Concepts to Solve the Problem

- Character Counting: **Use a frequency count of characters in the magazine to determine if there are enough characters to form the ransomNote.**

- Hash Map or Array: Utilize a hash map (or an array, since the character set is limited) to store the counts of each character in the magazine.

- Iterate and Compare: For each character in the ransomNote, check if it exists in the magazine with sufficient count.

## Complexity Analysis

- **Time Complexity: O(m + n)**, where m is the length of the magazine and n is the length of the ransomNote. We traverse both strings once to count characters and then check the counts.

- Space Complexity: O(1) if we consider the character set to be fixed (like lowercase English letters), as the size of the hash map will not exceed a constant size. If we consider the hash map's size, it would be O(k), where k is the number of unique characters in the magazine.
