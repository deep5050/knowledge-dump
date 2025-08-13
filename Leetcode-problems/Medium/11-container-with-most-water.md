## Problem Description: LeetCode 11 - Container With Most Water

You are given an integer array `height` where `height[i]` represents the height of a vertical line drawn at index `i`. The two endpoints of the container are at the lines represented by `height[i]` and `height[j]`, where `i < j`. The container can hold water up to the minimum of the two heights multiplied by the distance between the two lines.

Your task is to find the maximum amount of water that can be contained.

### Example:
- Input: `height = [1,8,6,2,5,4,8,3,7]`
- Output: `49` (The maximum area is formed between the lines at indices 1 and 8.)

### Constraints:
- `2 <= height.length <= 10^5`
- `0 <= height[i] <= 10^4`

## C++ Code Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxArea(vector<int>& height) {
    int left = 0; // Left pointer
    int right = height.size() - 1; // Right pointer
    int maxArea = 0; // Variable to store the maximum area

    while (left < right) {
        // Calculate the area with the current left and right pointers
        int currentHeight = min(height[left], height[right]);
        int currentWidth = right - left;
        int area = currentHeight * currentWidth;

        // Update the maximum area if the current area is larger
        maxArea = max(maxArea, area);

        // Move the pointer pointing to the shorter line
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return maxArea;
}

int main() {
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int result = maxArea(height);

    cout << "Maximum area: " << result << endl;
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the length of the `height` array. We traverse the array using two pointers, which results in a linear time complexity.

### Space Complexity
- The space complexity is **O(1)**. We use a constant amount of extra space for the pointers and the variable to store the maximum area.

## Key Concepts and Tricks

1. **Two-Pointer Technique**: This problem is efficiently solved using the two-pointer technique. By maintaining one pointer at the start and another at the end of the array, we can calculate the area and adjust the pointers based on the heights.

2. **Area Calculation**: The area is determined by the shorter of the two heights multiplied by the distance between the two pointers. This ensures that we are always considering the limiting factor (the shorter line).

3. **Pointer Adjustment**: To potentially find a larger area, we move the pointer that points to the shorter line. This is because moving the taller line would not increase the height, while moving the shorter line might lead to a taller line and a larger area.

4. **Single Pass Efficiency**: The algorithm efficiently checks all possible pairs of lines in a single pass, making it suitable for large inputs.

This approach is optimal for solving the Container With Most Water problem, ensuring that we can determine the maximum area in linear time with minimal space usage.
