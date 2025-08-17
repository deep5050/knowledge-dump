To find a peak element in an array where some elements are in increasing order and others are in decreasing order, you can use a modified binary search approach. A peak element is defined as an element that is greater than or equal to its neighbors.

Here's a C++ program that implements this logic:

```cpp
#include <iostream>
#include <vector>

int findPeakElement(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        // Check if mid is greater than its next element
        if (nums[mid] > nums[mid + 1]) {
            // If mid is greater, then peak lies on the left side (including mid)
            right = mid;
        } else {
            // If mid is less, then peak lies on the right side (excluding mid)
            left = mid + 1;
        }
    }

    // At the end of the loop, left == right and points to the peak element
    return nums[left];
}

int main() {
    std::vector<int> arr = {1, 3, 20, 4, 1}; // Example array
    int peak = findPeakElement(arr);
    std::cout << "A peak element is: " << peak << std::endl;
    return 0;
}
```

### Explanation:
1. **Binary Search**: The program uses a binary search approach to efficiently find a peak element.
2. **Midpoint Comparison**: It compares the middle element with its next element:
   - If the middle element is greater than the next element, it means there is a peak on the left side (including the middle).
   - If the middle element is less than the next element, it means there is a peak on the right side (excluding the middle).
3. **Termination**: The loop continues until `left` equals `right`, at which point it points to a peak element.

### Example:
For the array `{1, 3, 20, 4, 1}`, the program will output `20` as a peak element. You can test it with different arrays to find other peak elements.
