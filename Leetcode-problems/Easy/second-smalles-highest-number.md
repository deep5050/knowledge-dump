## Problem statement

find the **second largest** and **second smallest** elements from an array of **unique non-negative** integers without using the `sort()` function:

```cpp
#include <iostream>
#include <vector>
#include <limits>

std::vector<int> findSecondLargestAndSmallest(int n, std::vector<int>& a) {
    int largest = std::numeric_limits<int>::min();
    int secondLargest = std::numeric_limits<int>::min();
    int smallest = std::numeric_limits<int>::max();
    int secondSmallest = std::numeric_limits<int>::max();

    for (int i = 0; i < n; ++i) {
        // Update largest and second largest
        if (a[i] > largest) {
            secondLargest = largest;
            largest = a[i];
        } else if (a[i] > secondLargest) {
            secondLargest = a[i];
        }

        // Update smallest and second smallest
        if (a[i] < smallest) {
            secondSmallest = smallest;
            smallest = a[i];
        } else if (a[i] < secondSmallest) {
            secondSmallest = a[i];
        }
    }

    return {secondLargest, secondSmallest};
}

int main() {
    int n = 5;
    std::vector<int> a = {1, 2, 3, 4, 5};

    std::vector<int> result = findSecondLargestAndSmallest(n, a);
    
    std::cout << "[" << result[0] << ", " << result[1] << "]" << std::endl; // Output: [4, 2]

    return 0;
}
```

### Explanation:
1. **Initialization**: 
   - `largest` and `secondLargest` are initialized to the smallest possible integer value.
   - `smallest` and `secondSmallest` are initialized to the largest possible integer value.

2. **Single Pass Through the Array**:
   - For each element in the array, we check if it is greater than the current largest. If it is, we update the second largest to be the current largest and then update the largest.
   - Similarly, we check for the smallest and second smallest elements.

3. **Returning the Result**: The function returns a vector containing the second largest and second smallest elements.

### Example Usage:
When you run the program with the provided input, it will output `[4, 2]`, which corresponds to the second largest and second smallest elements in the array.
