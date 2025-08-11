## Problem Description: LeetCode 55 - Jump Game

You are given an array of non-negative integers `nums`. Each element in the array represents your maximum jump length at that position. Your goal is to determine if you can reach the last index starting from the first index.

### Example:
- Input: `nums = [2, 3, 1, 1, 4]`
- Output: `true` (You can jump to index 1, then to index 4.)

- Input: `nums = [3, 2, 1, 0, 4]`
- Output: `false` (You will always arrive at index 3, which is a dead end.)

### Constraints:
- `1 <= nums.length <= 10^4`
- `0 <= nums[i] <= 10^5`

## C++ Code Implementation

```c
#include <stdio.h>
#include <stdbool.h>

bool canJump(int* nums, int size) {
    int size = size - 1; // calculate the last index
    int goal = size;
    for (int i = size - 1; i >= 0; i--) {
        if (i + nums[i] >= goal) {
            goal = i;
        }
    }
    return goal == 0;
}

int main() {
    int nums[] = {2, 3, 1, 1, 4};
    int size = sizeof(nums)/sizeof(int);
    bool result = canJump(nums,size);
    if (result) printf("OK\n");
    else printf("NOT OK\n");
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the length of the `nums` array. We traverse the array once to determine if we can reach the last index.

### Space Complexity
- The space complexity is **O(1)**. We use a constant amount of extra space for the `maxReach` variable, regardless of the input size.

## Key Concepts and Tricks
 - The idea is to if we can always reach the last index from its previous index we are good. We make the last element as a goalpost and then decrement the counter by one
   and check if we can reach the goalpost from previous one. if yes then make the previous index the new goalpose
4. **Single Pass**: The algorithm only requires a single pass through the array, making it efficient for large inputs.

This approach is optimal for solving the Jump Game problem, ensuring that we can determine the result in linear time with minimal space usage.
