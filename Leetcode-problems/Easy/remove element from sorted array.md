To remove an element from a sorted array in C++, you can **use a two-pointer approach**. 
This method allows you to efficiently shift elements and maintain the sorted order without using extra space.

## 📝 C++ Solution

Here’s a C++ solution to remove an element from a sorted array:

```cpp
#include <vector>
#include <iostream>

int removeElement(std::vector<int>& nums, int val) {
    int index = 0; // Pointer for the position to place the next non-val element

    // Iterate through the array
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != val) {
            nums[index] = nums[i]; // Place the non-val element at the current index
            index++; // Move to the next position
        }
    }

    return index; // Return the new length of the array
}

int main() {
    std::vector<int> nums = {1, 2, 2, 3, 4, 4, 5};
    int val = 4;
    int newLength = removeElement(nums, val);
    
    std::cout << "New length: " << newLength << std::endl;
    std::cout << "Modified array: ";
    for (int i = 0; i < newLength; i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Initialize Pointer**: Start with an `index` pointer set to 0, which will track the position to place the next non-`val` element.
2. **Iterate Through the Array**: Loop through each element in the array:
   - If the current element is not equal to `val`, place it at the `index` position and increment `index`.
3. **Return New Length**: After processing all elements, return the `index`, which represents the new length of the modified array.

### 📊 Complexity:
- **Time Complexity**: O(n), where n is the number of elements in the array, since we traverse the list once.
- **Space Complexity**: O(1), as we are modifying the array in place without using additional space.

This solution effectively removes the specified element from the sorted array while maintaining the order of the remaining elements.