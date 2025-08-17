##  LeetCode 1 : Two Sum problem

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 
```
Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 

Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.
```


## 📝 C++ Solution

```cpp
#include <vector>
#include <unordered_map>
#include <iostream>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap; // To store the number and its index
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i]; // Calculate the complement
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i}; // Return the indices if found
        }
        numMap[nums[i]] = i; // Store the number and its index
    }
    return {}; // Return an empty vector if no solution is found
}

int main() {
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> result = twoSum(nums, target);
    
    std::cout << "Indices: " << result[0] << ", " << result[1] << std::endl;
    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Hash Map**: Use an unordered map to store each number and its index as you iterate through the array.
2. **Complement Calculation**: For each number, calculate its complement (the number needed to reach the target).
3. **Check for Complement**: Check if the complement exists in the map. If it does, return the indices of the current number and its complement.
4. **Store Number**: If the complement is not found, store the current number and its index in the map for future reference.

### 📊 Complexity:
- **Time Complexity**: O(n), where n is the number of elements in the array, since we traverse the list once.
- **Space Complexity**: O(n), for storing the elements in the hash map.

This solution efficiently finds the two indices of the numbers that add up to the target value.
