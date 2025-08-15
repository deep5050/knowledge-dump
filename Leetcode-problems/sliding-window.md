## Sliding Window Problem Solving Approach
The sliding window technique is a popular algorithmic approach used to solve problems that involve arrays or lists, 
particularly when you need to find a subarray or a contiguous segment of elements that meet certain criteria.
This method is efficient and often reduces the time complexity **from O(n^2) to O(n)** by maintaining a window that expands and contracts as needed.

## How It Works
Initialization: Start with two pointers (or indices) that represent the boundaries of the window. Typically, one pointer marks the start of the window, and the other marks the end.
Expand the Window: Move the end pointer to include more elements in the window.
Contract the Window: Move the start pointer to exclude elements from the window when certain conditions are met.
Check Conditions: At each step, check if the current window meets the required conditions (e.g., sum, length, etc.).
Update Results: If the current window is valid, update the result accordingly.
Types of Sliding Window Problems

## When to Use Sliding Window

You can apply the sliding window technique when:

The problem involves a contiguous sequence (subarray or substring).
You need to find:
=> Maximum/Minimum sum in a fixed-size window.
=> Longest/Shortest subarray with certain conditions.
=> Count of distinct elements in a range.

## Types of Sliding Window Problems
### Fixed Size Sliding Window:
The window size is constant.
Example: Finding the maximum sum of any contiguous subarray of size k.

### Dynamic Size Sliding Window:
The window size can change based on certain conditions.
Example: Finding the longest substring without repeating characters.
