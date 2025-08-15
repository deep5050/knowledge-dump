## Problem Description: LeetCode 643 - Maximum Average Subarray I

You are given an integer array `nums` consisting of `n` elements, and an integer `k`. You need to find the maximum average value of a contiguous subarray of length `k`.

### Example:
- Input: `nums = [1, 12, -5, -6, 50, 3], k = 4`
- Output: `12.75` (The maximum average is calculated from the subarray `[12, -5, -6, 50]`.)

- Input: `nums = [5], k = 1`
- Output: `5.0`

### Constraints:
- `1 <= k <= n <= 30,000`
- `-10^5 <= nums[i] <= 10^5`

## C++ Code Implementation

```cpp
#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate

using namespace std;

double findMaxAverage(vector<int>& nums, int k) {
    double maxAverage = 0.0;
    double currentSum = 0.0;

    // Calculate the sum of the first 'k' elements
    for (int i = 0; i < k; i++) {
        currentSum += nums[i];
    }

    maxAverage = currentSum / k; // Initial average

    // Slide the window over the rest of the array
    for (int i = k; i < nums.size(); i++) {
        currentSum += nums[i] - nums[i - k]; // Update the sum by adding the new element and removing the oldest
        maxAverage = max(maxAverage, currentSum / k); // Update max average if needed
    }

    return maxAverage;
}

int main() {
    vector<int> nums = {1, 12, -5, -6, 50, 3};
    int k = 4;
    double result = findMaxAverage(nums, k);

    cout << "Maximum average: " << result << endl;
    return 0;
}
```
## Alternative approach:
we can calculate the maxSum and at the time return, return `maxSum/k` only !!

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the length of the `nums` array. We traverse the array once to calculate the initial sum and then slide the window across the rest of the array.

### Space Complexity
- The space complexity is **O(1)**. We use a constant amount of extra space for the variables used to track the current sum and maximum average.

## Key Concepts and Tricks

1. **Sliding Window Technique**: This problem is efficiently solved using the sliding window technique. By maintaining a window of size `k`, we can calculate the sum of the subarray and update it as we move through the array.

2. **Initial Sum Calculation**: The sum of the first `k` elements is calculated first, which serves as the starting point for the average.

3. **Dynamic Sum Update**: As we slide the window, we update the sum by adding the new element and subtracting the element that is no longer in the window. This allows us to maintain the sum in constant time.

4. **Max Average Tracking**: We continuously check if the current average is greater than the maximum average found so far, ensuring that we capture the highest average.

This approach efficiently finds the maximum average of a contiguous subarray of length `k`, ensuring that we can determine the result in linear time with minimal space usage.
