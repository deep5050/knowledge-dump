## Check palindrome

```cpp
class Solution {
public:
    bool isPalindrome(int original) {
    if (original < 0 || (original != 0 && original%10 == 0))
        return false;
    long long num = original;
    long long reverse = 0;
    while (num > 0)
    {
        int d = num % 10;
        num = num / 10;
        reverse = reverse * 10 + d;
    }
    if (original == reverse)
       return true;
    return false;   
    }
};

```
Time Complexity: **O(logn)**
