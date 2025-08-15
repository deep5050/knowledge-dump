## 155 - Min Stack : Problem statement

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.

 

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
 

Constraints:

-231 <= val <= 231 - 1
Methods pop, top and getMin operations will always be called on non-empty stacks.
At most 3 * 104 calls will be made to push, pop, top, and getMin.


```cpp
#include <iostream>
#include <vector>

using namespace std;

class MinStack
{
public:
    vector<int> list;
    vector<int> minList;
    MinStack()
    {
    }

    void push(int val)
    {
        list.insert(list.begin(), val);
        if (minList.empty())
        {
            minList.insert(minList.begin(), val);
        }
        else
        {
            minList.insert(minList.begin(), min(val, minList.at(0)));
        }
    }

    void pop()
    {
        list.erase(list.begin());
        minList.erase(minList.begin());
    }

    int top()
    {
        return list.at(0);
    }

    int getMin()
    {

        return minList[0];
    }
};

int main()

{
    MinStack *minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    cout << "MIN: " << minStack->getMin() << endl; // return -3
    minStack->pop();
    cout << "TOP: " << minStack->top() << endl;    // return 0
    cout << "MIN: " << minStack->getMin() << endl; // return -2

    return 0;
}
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

```

## key trick
**Implemet another stack that counts minimum val for each poisition, in this way we can get the min value at O(1) **
