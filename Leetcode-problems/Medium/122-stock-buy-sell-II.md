## Problem Description: LeetCode 122 - Best Time to Buy and Sell Stock II

You are given an array where the `i-th` element is the price of a given stock on the `i-th` day. You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock. However, you can make as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).

### Example:
- Input: `prices = [7, 1, 5, 3, 6, 4]`
- Output: `7` (Buy on day 2 and sell on day 3, profit = 5 - 1 = 4. Then buy on day 4 and sell on day 5, profit = 6 - 3 = 3. Total profit = 4 + 3 = 7.)

### Constraints:
- `1 <= prices.length <= 3 * 10^4`
- `0 <= prices[i] <= 10^4`

## C Code Implementation

```c
#include <stdio.h>

int maxProfit(int* prices, int pricesSize) {
    int totalProfit = 0;

    for (int i = 1; i < pricesSize; i++) {
        // If the price today is greater than the price yesterday, we can make a profit
        if (prices[i] > prices[i - 1]) {
            totalProfit += prices[i] - prices[i - 1];
        }
    }

    return totalProfit;
}

int main() {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int pricesSize = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(prices, pricesSize);
    printf("Maximum Profit: %d\n", profit);
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- The time complexity of this algorithm is **O(n)**, where `n` is the number of days (or the length of the prices array). We traverse the array once to calculate the total profit.

### Space Complexity
- The space complexity is **O(1)**. We are using a constant amount of extra space for the `totalProfit` variable, regardless of the input size.

## Key Concepts and Tricks

1. **Greedy Approach**: The problem can be solved using a greedy strategy. Whenever the price increases from one day to the next, we consider that as a potential profit opportunity. By summing up all the positive differences between consecutive days, we can maximize our profit.

2. **Multiple Transactions**: Unlike the first stock problem where you can only buy and sell once, this problem allows multiple transactions. This means you can buy and sell on every upward trend, which is why we add profits whenever the price increases.

3. **No Need to Track Individual Transactions**: Instead of keeping track of individual buy and sell transactions, we focus on the overall profit. This simplifies the problem significantly.

4. **Edge Cases**: Consider edge cases such as when the prices array has only one element or when prices are always decreasing. In these cases, the maximum profit will be zero, which is handled naturally by the algorithm.

This approach is efficient and straightforward, making it a common solution for similar stock trading problems.
