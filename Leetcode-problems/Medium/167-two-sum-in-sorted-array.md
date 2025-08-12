## Problem Description: LeetCode 167 - Two Sum II - Input Array Is Sorted

Given a 1-indexed array of integers `numbers` that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. 

Return the indices of the two numbers (1-indexed) as an integer array `answer` of size 2, where `answer[0]` is the index of the first number and `answer[1]` is the index of the second number.

You may assume that each input would have exactly one solution and you may not use the same element twice.

### Example:
- Input: `numbers = [2, 7, 11, 15], target = 9`
- Output: `[1, 2]` (Because `numbers[0] + numbers[1] = 2 + 7 = 9`)

### Constraints:
- `2 <= numbers.length <= 3 * 10^4`
- `-1000 <= numbers[i] <= 1000`
- `numbers` is sorted in non-decreasing order.
- `-1000 <= target <= 1000`
- Only one valid answer exists.

## C++ Code Implementation

```cpp
#include <iostream>
#include <vector>

using namespace std;

vector<int> twoSum(vector<int>& numbers, int target) {
    int left = 0; // Start pointer
    int right = numbers.size() - 1; // End pointer

    while (left < right) {
        int currentSum = numbers[left] + numbers[right];
        if (currentSum == target) {
            return {left + 1, right + 1}; // Return 1-indexed positions
        } else if (currentSum < target) {
            left++; // Move left pointer to the right
        } else {
            right--; // Move right pointer to the left
        }
    }

    return {}; // Return an empty vector if no solution is found (should not happen as per problem statement)
}

int main() {
    vector<int> numbers = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = twoSum(numbers, target);

    cout << "Indices: [" << result[0] << ", " << result[1] << "]" << endl;
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the length of the `numbers` array. We traverse the array using two pointers, which results in a linear time complexity.

### Space Complexity
- The space complexity is **O(1)**. We use a constant amount of extra space for the two pointers and the result vector.

## Key Concepts and Tricks

1. **Two-Pointer Technique**: This problem is efficiently solved using the two-pointer technique. By maintaining one pointer at the start and another at the end of the array, we can quickly find the two numbers that sum to the target.

2. **Sorted Array**: The fact that the array is sorted allows us to make decisions based on the sum of the two pointers. If the sum is less than the target, we can safely move the left pointer to the right to increase the sum. If the sum is greater than the target, we move the right pointer to the left to decrease the sum.

3. **Guaranteed Solution**: The problem guarantees that there is exactly one solution, which simplifies the implementation since we do not need to handle cases where no solution exists.

This approach is optimal for solving the Two Sum II problem, ensuring that we can determine the result in linear time with minimal space usage.
