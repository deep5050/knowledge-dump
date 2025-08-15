## Problem Description: LeetCode 219 - Contains Duplicate II

Given an integer array `nums` and an integer `k`, return `true` if there are two distinct indices `i` and `j` in the array such that `nums[i] == nums[j]` and `abs(i - j) <= k`.

### Example:
- Input: `nums = [1, 2, 3, 1], k = 3`
- Output: `true` (The elements at indices 0 and 3 are equal and their indices differ by 3.)

- Input: `nums = [1, 0, 1, 1], k = 1`
- Output: `true` (The elements at indices 1 and 2 are equal and their indices differ by 1.)

- Input: `nums = [1, 2, 3, 1, 2, 3], k = 2`
- Output: `false` (There are no indices that satisfy the condition.)

### Constraints:
- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`
- `0 <= k <= 10^5`

## C++ Code Implementation

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> numIndexMap; // Map to store the last index of each number

    for (int i = 0; i < nums.size(); i++) {
        // Check if the number exists in the map and if the index difference is within k
        if (numIndexMap.find(nums[i]) != numIndexMap.end() && (i - numIndexMap[nums[i]] <= k)) {
            return true; // Found a duplicate within the range
        }
        // Update the last index of the current number
        numIndexMap[nums[i]] = i;
    }

    return false; // No duplicates found within the range
}

int main() {
    vector<int> nums = {1, 2, 3, 1};
    int k = 3;
    bool result = containsNearbyDuplicate(nums, k);

    cout << (result ? "Contains duplicate within range." : "Does not contain duplicate within range.") << endl;
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the length of the `nums` array. We traverse the array once, and each lookup and insertion in the hash map is on average O(1).

### Space Complexity
- The space complexity is **O(min(n, k))**. In the worst case, we may store up to `k` elements in the hash map if `k` is less than `n`. If `k` is greater than `n`, we could store all `n` elements.

## Key Concepts and Tricks

1. **Hash Map for Index Tracking**: We use a hash map to keep track of the last index of each number encountered. This allows for quick lookups to check if a duplicate exists within the specified range.

2. **Efficient Index Comparison**: By checking the difference between the current index and the last recorded index of the number, we can efficiently determine if the condition `abs(i - j) <= k` is satisfied.

3. **Early Exit**: The algorithm returns `true` as soon as a valid pair is found, ensuring that we do not perform unnecessary checks after finding a solution.

4. **Handling Edge Cases**: The algorithm naturally handles cases where there are no duplicates or where `k` is zero, returning `false` when appropriate.

This approach efficiently checks for nearby duplicates in the array, ensuring that we can determine the result in linear time with minimal space usage.
