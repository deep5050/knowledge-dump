```cpp
#include <iostream>
#include <vector>

int BS(std::vector<int> &arr, int target) {
    int left = 0;
    int right = arr.size() - 1; // Set right to the last index

    while (left <= right) { // Use <= to include the rightmost element
        int mid = left + (right - left) / 2; // Calculate mid

        if (target == arr[mid]) {
            return mid; // Target found
        }
        if (target > arr[mid]) {
            left = mid + 1; // Move left up
        } else {
            right = mid - 1; // Move right down
        }
    }
    return -1; // Target not found
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 7;
    int result = BS(arr, target);

    if (result != -1) {
        std::cout << "Element found at index: " << result << std::endl;
    } else {
        std::cout << "Element not found." << std::endl;
    }

    return 0;
}

```
