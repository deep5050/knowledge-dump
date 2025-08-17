## Prolem statement : LeetCode 121 : Best time buy & sell stock

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

 
```
Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
 

Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 104
```


## 📝 C++ Solution

Here’s a C++ solution that efficiently finds the maximum profit:

```cpp
#include <vector>
#include <iostream>

int maxProfit(const std::vector<int>& prices) {
    if (prices.empty()) return 0; // Return 0 if the prices array is empty

    int minPrice = prices[0]; // Initialize minPrice to the first price
    int maxProfit = 0; // Initialize maxProfit to 0

    // Iterate through the prices
    for (int price : prices) {
        // Update minPrice if the current price is lower
        if (price < minPrice) {
            minPrice = price;
        } else {
            // Calculate profit if selling at the current price
            int profit = price - minPrice;
            // Update maxProfit if the current profit is greater
            if (profit > maxProfit) {
                maxProfit = profit;
            }
        }
    }

    return maxProfit; // Return the maximum profit
}

int main() {
    std::vector<int> prices = {7, 1, 5, 3, 6, 4};
    int profit = maxProfit(prices);
    
    std::cout << "Maximum profit: " << profit << std::endl;
    return 0;
}
```

## 🚀 Explanation

### 🛠️ Key Steps:
1. **Initialize Variables**: Start with `minPrice` set to the first price and `maxProfit` set to 0.
2. **Iterate Through Prices**: Loop through each price in the array:
   - If the current price is lower than `minPrice`, update `minPrice`.
   - If the current price is higher than `minPrice`, calculate the potential profit by subtracting `minPrice` from the current price.
   - If this profit is greater than `maxProfit`, update `maxProfit`.
3. **Return Result**: After iterating through all prices, return the maximum profit.

### 📊 Complexity:
- **Time Complexity**: O(n), where n is the number of days (length of the prices array), since we traverse the list once.
- **Space Complexity**: O(1), as we are using a constant amount of space for variables.

This solution efficiently determines the best time to buy and sell stock to maximize profit.
