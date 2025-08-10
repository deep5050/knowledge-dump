## Problem Description: LeetCode 189 - Rotate Array

Given an array, rotate the array to the right by `k` steps, where `k` is non-negative. 

### Example:
- Input: `nums = [1, 2, 3, 4, 5, 6, 7]`, `k = 3`
- Output: `[5, 6, 7, 1, 2, 3, 4]`

### Constraints:
- The length of the array is in the range `[1, 10^5]`.
- `-2^31 <= nums[i] <= 2^31 - 1`
- `0 <= k <= 10^5`

## C Code Implementation

```c
#include <stdio.h>

void reverse(int* nums, int start, int end) {
    while (start < end) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

void rotate(int* nums, int numsSize, int k) {
    k = k % numsSize; // Handle cases where k is greater than numsSize
    if (k == 0) return; // No need to rotate if k is 0

    // Step 1: Reverse the entire array
    reverse(nums, 0, numsSize - 1);
    // Step 2: Reverse the first k elements
    reverse(nums, 0, k - 1);
    // Step 3: Reverse the remaining elements
    reverse(nums, k, numsSize - 1);
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    rotate(nums, numsSize, k);

    // Print the rotated array
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the number of elements in the array. This is because we are reversing the array three times, and each reversal takes linear time.

### Space Complexity
- The space complexity is **O(1)**. We are using a constant amount of extra space for the temporary variable used in the reversal function, regardless of the input size. The rotations are done in place.

This approach efficiently rotates the array without requiring additional space for another array, making it optimal for large inputs.
