
## Problem statement : Sort 0s, 1s, 2s in an array in single pass (Dutch national flag problem, sort colors)

You have been given an integer array/list(ARR) of size 'N'. It only contains 0s, 1s and 2s. Write a solution to sort this array/list.

> Note :

Try to solve the problem in 'Single Scan'. ' Single Scan' refers to iterating over the array/list just once or to put it in other words, you will be visiting each element in the array/list just once.

## code

```cpp
#include <iostream>
#include <vector>

void sort012(std::vector<int>& arr) {
    int low = 0;        // Pointer for the next position of 0
    int mid = 0;        // Pointer for the current element
    int high = arr.size() - 1; // Pointer for the next position of 2

    while (mid <= high) {
        switch (arr[mid]) {
            case 0:
                std::swap(arr[low++], arr[mid++]);
                break;
            case 1:
                mid++;
                break;
            case 2:
                std::swap(arr[mid], arr[high--]);
                break;
        }
    }
}

int main() {
    std::vector<int> arr = {0, 1, 2, 0, 1, 2, 1, 0, 2};
    
    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    sort012(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

> Time complexity is : O(n)

## Tricks

low holds the last position of a zero, mid holds 1, and as 2 suppose to be at the end of the array high points to first occerence of 2 from last.

using this three pointer approach we can effectively solve this in single pass !
