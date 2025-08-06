The "Best Time to Buy and Sell Stock" problem is a common algorithmic challenge where the goal is to determine the maximum profit you can achieve by buying and **selling a stock on different days**. **You can only complete one transaction (buy and then sell).**

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