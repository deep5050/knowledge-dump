## Problem Statement

The **Happy Number** problem asks whether a given number is a "happy number." A happy number is defined by the following process: starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle that does not include 1. If the number ends in 1, it is considered a happy number; otherwise, it is not.

### Example:
- Input: `n = 19`
- Output: `true`
  - Explanation: 
    - \(1^2 + 9^2 = 82\)
    - \(8^2 + 2^2 = 68\)
    - \(6^2 + 8^2 = 100\)
    - \(1^2 + 0^2 + 0^2 = 1\)

- Input: `n = 2`
- Output: `false`
  - Explanation: 
    - \(2^2 = 4\)
    - \(4^2 = 16\)
    - \(1^2 + 6^2 = 37\)
    - \(3^2 + 7^2 = 58\)
    - \(5^2 + 8^2 = 89\)
    - \(8^2 + 9^2 = 145\)
    - \(1^2 + 4^2 + 5^2 = 42\)
    - \(4^2 + 2^2 = 20\)
    - \(2^2 + 0^2 = 4\) (cycle detected)

## C++ Solution

Here’s a C++ solution to the problem:

```cpp
#include <iostream>
#include <unordered_set>

int getNext(int n) {
    int totalSum = 0;
    while (n > 0) {
        int digit = n % 10;
        totalSum += digit * digit;
        n /= 10;
    }
    return totalSum;
}

bool isHappy(int n) {
    std::unordered_set<int> seen;
    while (n != 1 && seen.find(n) == seen.end()) {
        seen.insert(n);
        n = getNext(n);
    }
    return n == 1;
}

int main() {
    int n = 19;
    std::cout << (isHappy(n) ? "true" : "false") << std::endl;

    n = 2;
    std::cout << (isHappy(n) ? "true" : "false") << std::endl;

    return 0;
}
```

## Complexity Analysis

### Time Complexity
- The time complexity of this solution is **O(log n)** for each iteration, where `n` is the number being processed. The number of digits in `n` determines the number of iterations needed to compute the sum of squares. In the worst case, the number of iterations is limited because the sequence will either reach 1 or enter a cycle.

### Space Complexity
- The space complexity is **O(k)**, where `k` is the number of unique numbers encountered during the process. In practice, this is limited since the number of unique sums of squares is finite.

## Key Tricks/Steps to Solve the Problem

1. **Sum of Squares Function**: Create a helper function to compute the sum of the squares of the digits of a number.

2. **Cycle Detection**: Use a hash set to keep track of numbers that have already been seen. If a number repeats, it indicates a cycle, and the number is not happy.

3. **Iterate Until Condition Met**: Continue the process until the number becomes 1 (happy) or a cycle is detected (not happy).

4. **Return Result**: Finally, return whether the number is happy based on the conditions checked.

By following these steps, you can efficiently determine if a number is a happy number.