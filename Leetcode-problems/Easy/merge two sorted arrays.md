To merge two sorted arrays `nums1` and `nums2` into `nums1` in-place, you can use a two-pointer approach starting from the end of both arrays. This method allows you to fill `nums1` from the back, ensuring that you do not overwrite any of the elements that have not yet been merged.

## 📝 C++ Solution

Here’s a C++ solution to merge `nums1` and `nums2`:

```cpp
#include <vector>
#include <iostream>

void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    // Pointers for nums1 and nums2
    int i = m - 1; // Last element in nums1's initial part
    int j = n - 1; // Last element in nums2
    int k = m + n - 1; // Last position in nums1

    // Merge in reverse order
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i] ; // Place larger element at the end
            i--;
        } else {
            nums1[k] = nums2[j]; // Place larger element at the end
            j--;
        }
        k--;
    }

    // If there are remaining elements in nums2, copy them
    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }

    // No need to copy remaining elements from nums1, they are already in place
}

int main() {
    std::vector<int> nums1 = {1, 2, 3, 0, 0, 0}; // nums1 has extra space for nums2
    std::vector<int> nums2 = {2, 5, 6};
    int m = 3; // Number of elements in nums1
    int n = 3; // Number of elements in nums2

    merge(nums1, m, nums2, n);
    
    std::cout << "Merged array: ";
    for (int num : nums1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Initialize Pointers**: 
   - `i` points to the last element of the initial part of `nums1` (index `m - 1`).
   - `j` points to the last element of `nums2` (index `n - 1`).
   - `k` points to the last position in `nums1` (index `m + n - 1`).

2. **Merge in Reverse Order**: 
   - Use a while loop to compare elements from the end of both arrays:
     - If the current element in `nums1` is greater than the current element in `nums2`, place it at the position `k` in `nums1` and decrement `i`.
     - Otherwise, place the current element from `nums2` at position `k` and decrement `j`.
     - Always decrement `k` after placing an element.

3. **Copy Remaining Elements**: 
   - If there are any remaining elements in `nums2`, copy them to `nums1`. No need to copy remaining elements from `nums1` since they are already in place.

### 📊 Complexity:
- **Time Complexity**: O(m + n), where m is the number of elements in `nums1` and n is the number of elements in `nums2`, since we traverse both arrays once.
- **Space Complexity**: O(1), as we are merging in place without using additional space.

This solution efficiently merges the two sorted arrays into `nums1` while maintaining the sorted order.