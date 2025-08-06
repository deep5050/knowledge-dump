You are given an integer array `prices` where `prices[i]` is the price of a given stock on the `ith` day.

On each day, you may decide to buy and/or sell the stock. You can only hold **at most one** share of the stock at any time.
However, you can buy it then immediately sell it on the **same day**.

Find and return _the **maximum** profit you can achieve_.

The "Best Time to Buy and Sell Stock II" problem allows you to buy and sell stocks multiple times. 
The goal is to maximize your profit by making as **many transactions as you like, but you must buy before you sell.**

## 📝 C++ Solution

Here’s a C++ solution that calculates the maximum profit by summing up all the positive differences between consecutive days:

```cpp
#include <vector>
#include <iostream>

int maxProfit(const std::vector<int>& prices) {
    int totalProfit = 0;

    // Iterate through the prices
    for (size_t i = 1; i < prices.size(); i++) {
        // If the current price is greater than the previous price, add the profit
        if (prices[i] > prices[i - 1]) {
            totalProfit += prices[i] - prices[i - 1];
        }
    }

    return totalProfit; // Return the total profit
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
1. **Initialize Total Profit**: Start with a variable `totalProfit` set to 0.
2. **Iterate Through Prices**: Loop through the prices starting from the second day:
   - If the price on the current day is greater than the price on the previous day, calculate the profit and add it to `totalProfit`.
3. **Return Total Profit**: After processing all prices, return the total profit.

### 📊 Complexity:
- **Time Complexity**: O(n), where n is the number of days (length of the prices array), since we traverse the list once.
- **Space Complexity**: O(1), as we are using a constant amount of space for variables.

This solution efficiently calculates the maximum profit by taking advantage of all upward price movements, allowing for multiple transactions.


------------------------
The "Best Time to Buy and Sell Stock" problem and the "Best Time to Buy and Sell Stock II" problem differ primarily in the number of transactions allowed and the conditions for making a profit. Here’s a detailed comparison:

## 📝 Comparison Table

| Feature                          | Best Time to Buy and Sell Stock | Best Time to Buy and Sell Stock II |
|----------------------------------|----------------------------------|-------------------------------------|
| **Transactions Allowed**         | At most one transaction (one buy and one sell) | Unlimited transactions (multiple buys and sells) |
| **Profit Calculation**           | Profit is calculated from a single buy and sell | Profit is calculated from multiple transactions |
| **Goal**                         | Maximize profit from one transaction | Maximize total profit from multiple transactions |
| **Approach**                     | Find the lowest price before the highest price | Sum all positive price differences between consecutive days |
| **Complexity**                   | O(n) for finding the max profit | O(n) for summing profits from multiple transactions |

## 🚀 Key Differences Explained

### 1. **Transactions Allowed**:
- **Single Transaction**: In the original problem, you can only buy once and sell once. This means you need to find the best day to buy and the best day to sell after that.
- **Multiple Transactions**: In the second problem, you can buy and sell as many times as you want. This allows you to take advantage of every price increase.

### 2. **Profit Calculation**:
- **Single Transaction**: You calculate profit by finding the maximum difference between a buy price and a sell price, ensuring that the sell day comes after the buy day.
- **Multiple Transactions**: You calculate profit by summing all the profits from every upward price movement. If the price increases from one day to the next, you consider that profit.

### 3. **Approach**:
- **Single Transaction**: The approach typically involves finding the minimum price up to each day and calculating the maximum profit based on that.
- **Multiple Transactions**: The approach involves iterating through the price list and adding up all the positive differences between consecutive days.

### 4. **Complexity**:
- Both problems have a time complexity of O(n), but the logic and calculations differ significantly due to the constraints on transactions.

In summary, the main difference lies in the number of transactions allowed and how profits are calculated, leading to different strategies for maximizing profit.