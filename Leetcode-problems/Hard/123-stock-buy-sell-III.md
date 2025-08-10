## Problem Description: LeetCode 123 - Best Time to Buy and Sell Stock III

You are given an array where the `i-th` element is the price of a given stock on the `i-th` day. You want to maximize your profit by making at most two transactions. You can buy one and sell one share of the stock twice.

### Example:
- Input: `prices = [3, 2, 6, 5, 0, 3]`
- Output: `7` (Buy on day 2 and sell on day 3 for a profit of 4. Then buy on day 5 and sell on day 6 for a profit of 3. Total profit = 4 + 3 = 7.)

### Constraints:
- `1 <= prices.length <= 10^5`
- `0 <= prices[i] <= 10^4`

## C Code Implementation

```c
#include <stdio.h>
#include <limits.h>

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    int firstBuy = INT_MIN, firstSell = 0;
    int secondBuy = INT_MIN, secondSell = 0;

    for (int i = 0; i < pricesSize; i++) {
        firstBuy = fmax(firstBuy, -prices[i]); // Maximize first buy
        firstSell = fmax(firstSell, firstBuy + prices[i]); // Maximize first sell
        secondBuy = fmax(secondBuy, firstSell - prices[i]); // Maximize second buy
        secondSell = fmax(secondSell, secondBuy + prices[i]); // Maximize second sell
    }

    return secondSell; // The maximum profit after two transactions
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int pricesSize = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(prices, pricesSize);
    printf("Maximum Profit: %d\n", profit);
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the number of days (or the length of the prices array). We traverse the array once to calculate the maximum profit.

### Space Complexity
- The space complexity is **O(1)**. We are using a constant amount of extra space for the variables `firstBuy`, `firstSell`, `secondBuy`, and `secondSell`, regardless of the input size.

## Key Concepts and Tricks

1. **Dynamic Programming Approach**: This problem can be solved using a dynamic programming approach where we keep track of the maximum profit at different stages of buying and selling. We maintain four variables to represent the states of the transactions.

2. **State Representation**:
   - `firstBuy`: The maximum profit we can have after the first buy.
   - `firstSell`: The maximum profit we can have after the first sell.
   - `secondBuy`: The maximum profit we can have after the second buy.
   - `secondSell`: The maximum profit we can have after the second sell.

3. **Iterative Updates**: As we iterate through the prices, we update these states based on the current price. This allows us to efficiently calculate the maximum profit without needing to store all previous states.

4. **Handling Edge Cases**: The algorithm naturally handles edge cases, such as when the prices array is empty or when prices are always decreasing, resulting in zero profit.

5. **Optimal Substructure**: The problem exhibits optimal substructure, meaning that the optimal solution can be constructed from optimal solutions of its subproblems. This is a key characteristic of dynamic programming problems.

This approach is efficient and provides a clear way to maximize profit with limited transactions, making it a common solution for stock trading problems with constraints.
