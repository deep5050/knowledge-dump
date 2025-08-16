## Problem Description: LeetCode 53 - Maximum Subarray

Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

### Example:
- Input: `nums = [-2,1,-3,4,-1,2,1,-5,4]`
- Output: `6` (The contiguous subarray `[4,-1,2,1]` has the largest sum of `6`.)

- Input: `nums = [1]`
- Output: `1`

- Input: `nums = [5,4,-1,7,8]`
- Output: `23`

### Constraints:
- `1 <= nums.length <= 3 * 10^4`
- `-10^4 <= nums[i] <= 10^4`

## C++ Code Implementation

```cpp
#include <iostream>
#include <vector>

using namespace std;

int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0]; // Initialize maxSum with the first element
    int currentSum = nums[0]; // Initialize currentSum with the first element

    for (int i = 1; i < nums.size(); i++) {
        // Update currentSum to include the current element or start a new subarray
        currentSum = max(nums[i], currentSum + nums[i]);
        // Update maxSum if currentSum is greater
        maxSum = max(maxSum, currentSum);
    }

    return maxSum; // Return the maximum sum found
}

int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int result = maxSubArray(nums);

    cout << "Maximum subarray sum: " << result << endl;
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the length of the `nums` array. We traverse the array once to calculate the maximum subarray sum.

### Space Complexity
- The space complexity is **O(1)**. We use a constant amount of extra space for the variables `maxSum` and `currentSum`.

## Key Concepts and Tricks

1. **Kadane's Algorithm**: This problem can be efficiently solved using Kadane's algorithm, which is designed to find the maximum sum of a contiguous subarray in linear time.

2. **Dynamic Sum Calculation**: As we iterate through the array, we maintain a running sum (`currentSum`). If adding the current element to `currentSum` results in a smaller sum than starting a new subarray with the current element, we reset `currentSum` to the current element.

3. **Updating Maximum Sum**: We continuously update the maximum sum found (`maxSum`) whenever `currentSum` exceeds it.

4. **Handling Edge Cases**: The algorithm naturally handles cases where all elements are negative, as it will return the largest single element in such cases.

This approach efficiently finds the maximum subarray sum, ensuring that we can determine the result in linear time with minimal space usage.
