## Problem Description: LeetCode 128 - Longest Consecutive Sequence

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.

### Example:
- Input: `nums = [100, 4, 200, 1, 3, 2]`
- Output: `4` (The longest consecutive elements sequence is `[1, 2, 3, 4]`.)

- Input: `nums = [0, 0, 1, 1]`
- Output: `2` (The longest consecutive elements sequence is `[0, 1]`.)

### Constraints:
- `0 <= nums.length <= 10^4`
- `-10^9 <= nums[i] <= 10^9`

## C++ Code Implementation

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end()); // Store all numbers in a set
    int longestStreak = 0; // Variable to store the longest streak

    for (int num : numSet) {
        // Check if it's the start of a sequence
        if (numSet.find(num - 1) == numSet.end()) {
            int currentNum = num;
            int currentStreak = 1;

            // Count the length of the sequence
            while (numSet.find(currentNum + 1) != numSet.end()) {
                currentNum++;
                currentStreak++;
            }

            longestStreak = max(longestStreak, currentStreak); // Update the longest streak
        }
    }

    return longestStreak; // Return the longest streak found
}

int main() {
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    int result = longestConsecutive(nums);

    cout << "Length of longest consecutive sequence: " << result << endl;
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the number of elements in the `nums` array. Each element is processed at most twice (once when checking for the start of a sequence and once when counting the length of the sequence).

### Space Complexity
- The space complexity is **O(n)** due to the storage of elements in the unordered set.

## Key Concepts and Tricks

1. **Using a Set for Fast Lookups**: The unordered set allows for O(1) average time complexity for lookups, which is crucial for efficiently checking the existence of consecutive numbers.

2. **Identifying Sequence Starts**: By checking if `num - 1` is not in the set, we can determine if `num` is the start of a new sequence. This prevents counting the same sequence multiple times.

3. **Counting Consecutive Numbers**: Once a sequence start is identified, we can count how many consecutive numbers exist by incrementing the current number and checking for its presence in the set.

4. **Updating the Longest Streak**: We continuously update the longest streak found during the iteration, ensuring that we return the maximum length of consecutive sequences.

This approach efficiently finds the length of the longest consecutive sequence in the array, ensuring that we can determine the result in linear time with minimal space usage.
