  To find the elements with the maximum counts in an array, you can use a hash map to count the occurrences of each element and then determine which elements have the highest count. Here’s a C++ solution to achieve this.

## 📝 C++ Solution

```cpp
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

std::vector<int> findMaxCountElements(const std::vector<int>& nums) {
    std::unordered_map<int, int> countMap; // To store the count of each element
    int maxCount = 0; // Variable to track the maximum count

    // Count occurrences of each element
    for (int num : nums) {
        countMap[num]++;
        maxCount = std::max(maxCount, countMap[num]); // Update maxCount
    }

    // Collect elements with the maximum count
    std::vector<int> result;
    for (const auto& pair : countMap) {
        if (pair.second == maxCount) {
            result.push_back(pair.first);
        }
    }

    return result; // Return the elements with the maximum count
}

int main() {
    std::vector<int> nums = {1, 3, 2, 3, 4, 1, 3, 2, 2};
    std::vector<int> maxCountElements = findMaxCountElements(nums);
    
    std::cout << "Elements with maximum count: ";
    for (int elem : maxCountElements) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Count Occurrences**: Use an unordered map to count how many times each element appears in the array.
2. **Track Maximum Count**: As you count, keep track of the maximum count encountered.
3. **Collect Results**: After counting, iterate through the map to collect all elements that have the maximum count.

### 📊 Complexity:
- **Time Complexity**: O(n), where n is the number of elements in the array, since we traverse the list once to count and once to collect results.
- **Space Complexity**: O(k), where k is the number of unique elements in the array, for storing the counts in the hash map.

This solution efficiently identifies the elements that appear most frequently in the given array.