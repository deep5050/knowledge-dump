Here’s a solution for the LeetCode problem "Remove Duplicates from Sorted Array II" in C++. The goal is to modify the input array in place such that each element appears at most twice and return the new length of the array.

## 📝 C++ Solution

```cpp
#include <vector>
#include <iostream>

int removeDuplicates(std::vector<int>& nums) {
    if (nums.size() <= 2) return nums.size(); // If the size is 2 or less, return the size

    int index = 2; // Start from the third position
    for (int i = 2; i < nums.size(); i++) {
        // Check if the current number is different from the number at index - 2
        if (nums[i] != nums[index - 2]) {
            nums[index] = nums[i]; // Place the number at the current index
            index++; // Move to the next position
        }
    }
    return index; // Return the new length
}

int main() {
    std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    int newLength = removeDuplicates(nums);
    
    std::cout << "New length: " << newLength << std::endl;
    std::cout << "Modified array: ";
    for (int i = 0; i < newLength; i++) {
        std::cout << nums[i] << " ";
    }
    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Initial Check**: If the size of the array is less than or equal to 2, return the size since no duplicates can exist beyond that.
2. **Index Tracking**: Start from the third position (index 2) and use a variable `index` to track where to place the next valid number.
3. **Comparison**: For each number starting from the third, check if it is different from the number at `index - 2`. If it is, place it at the current `index` and increment `index`.
4. **Return Length**: Finally, return the new length of the modified array.

### 📊 Complexity:
- **Time Complexity**: O(n), where n is the number of elements in the array.
- **Space Complexity**: O(1), since we are modifying the array in place.

This solution efficiently removes duplicates while maintaining the order and allows each element to appear at most twice.