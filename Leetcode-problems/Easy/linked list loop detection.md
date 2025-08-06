## Linked List Cycle with Position

Given a linked list, determine if it has a cycle in it. If a cycle exists, return the position (0-indexed) of the node where the cycle begins. If there is no cycle, return -1.

### Example:
- Input: `head = [3,2,0,-4]` (where the last node points back to the second node)
- Output: `1` (the cycle begins at the node with value 2)

- Input: `head = [1,2]` (where the second node points back to the first node)
- Output: `0` (the cycle begins at the node with value 1)

- Input: `head = [1]`
- Output: `-1` (there is no cycle)

### Constraints:
- The number of nodes in the linked list is in the range [0, 10^4].
- The values of the nodes are in the range of [-10^5, 10^5].

## C++ Code

Here is a C++ implementation to solve the problem using Floyd's Tortoise and Hare algorithm, with the added functionality to return the position of the cycle's starting node:

```cpp
// C++ program to return first node of loop.
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int x) {
        data = x;
        next = nullptr;
    }
};

// Function to detect a loop in the linked list and 
// return the node where the cycle starts using
// Floyd’s Cycle-Finding Algorithm
Node* findFirstNode(Node* head) {
  
    // Initialize two pointers, slow and fast
    Node* slow = head;
    Node* fast = head;
    
    // Traverse the list
    while (fast != nullptr && fast->next != nullptr) {
      
      	// Move slow pointer by one step
        slow = slow->next;          
      
      	// Move fast pointer by two steps
        fast = fast->next->next;    

        // Detect loop
        if (slow == fast) {
          
            // Move slow to head, keep fast at meeting point
            slow = head;
            
            // Move both one step at a time until they meet
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            
            // Return the meeting node, which
          	// is the start of the loop
            return slow;
        }
    }
    
    // No loop found
    return nullptr;
}

int main() {
  
    // Create a linked list: 10 -> 15 -> 4 -> 20
    Node* head = new Node(10);
    head->next = new Node(15);
    head->next->next = new Node(4);
    head->next->next->next = new Node(20);

    head->next->next->next->next = head;

    Node* loopNode = findFirstNode(head);

    if (loopNode)
        cout << loopNode->data;
    else
        cout << -1;

    return 0;
}
```

## Complexity Analysis

### Time Complexity
- The time complexity remains **O(n)**, where `n` is the number of nodes in the linked list. The algorithm may traverse the entire list in the worst case.

### Space Complexity
- The space complexity is still **O(1)** since we are using a constant amount of extra space regardless of the input size.

## Explanation of the Algorithm

1. **Two Pointers**: The algorithm uses two pointers, `slow` and `fast`, to detect a cycle. The `slow` pointer moves one step at a time, while the `fast` pointer moves two steps at a time.

2. **Cycle Detection**: If there is a cycle, the `fast` pointer will eventually meet the `slow` pointer. If there is no cycle, the `fast` pointer will reach the end of the list.

3. **Finding the Cycle Start Position**: Once a cycle is detected, a new pointer (`entry`) is initialized at the head of the list. Both `entry` and `slow` are moved one step at a time until they meet. The position where they meet is the starting point of the cycle.

4. **Edge Cases**: The algorithm handles edge cases such as an empty list or a list with only one node without a cycle.

This implementation efficiently detects cycles in a linked list and provides the position of the cycle's starting node.