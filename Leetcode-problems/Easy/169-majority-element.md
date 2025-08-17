## Leetcode 169 : Find majority elemt in an array
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 
```
Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109
 ```

## 📝 C++ Solution using Boyer-Moore Voting Algorithm

```cpp
#include <vector>
#include <iostream>

int majorityElement(const std::vector<int>& nums) {
    int candidate = nums[0], count = 1;

    // Find the candidate for majority element
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] == candidate) {
            count++;
        } else {
            count--;
            if (count == 0) {
                candidate = nums[i];
                count = 1;
            }
        }
    }

    // Return the candidate (assuming the input guarantees a majority element)
    return candidate;
}

int main() {
    std::vector<int> nums = {3, 2, 3};
    int majority = majorityElement(nums);
    
    std::cout << "Majority element: " << majority << std::endl;
    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Initialization**: Start with the first element as the `candidate` and set the `count` to 1.
2. **Iterate Through the Array**:
   - If the current number matches the `candidate`, increment the `count`.
   - If it doesn't match, decrement the `count`. If `count` reaches 0, update the `candidate` to the current number and reset `count` to 1.
3. **Return the Candidate**: The candidate is returned as the majority element, assuming the input guarantees its existence.

### 📊 Complexity:
- **Time Complexity**: O(n), where n is the number of elements in the array.
- **Space Complexity**: O(1), as we are using a constant amount of space.

This simplified version retains the essential logic while making the code more straightforward and easier to understand.
