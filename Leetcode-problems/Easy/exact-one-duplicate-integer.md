## Problem statement
https://www.naukri.com/code360/problems/duplicate-in-array_893397?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM

### Problem statement

You are given an array ‘ARR’ of size ‘N’ **containing each number between 1 and ‘N’ - 1 at least once**. There is a single integer value that is present in the array twice. 
Your task is to find the duplicate integer value present in the array.

For example:
```
Consider ARR = [1, 2, 3, 4, 4], the duplicate integer value present in the array is 4. Hence, the answer is 4 in this case.
Note :
A duplicate number is always present in the given array.
```
### code


```cpp
int findDuplicate(vector<int> &arr) 
{
   int start = 1, n = arr.size()-1;
   int sum = n * (n + 1) / 2;
   int actualSum = 0;
   for (int i=0;i<arr.size();i++)
   actualSum+=arr[i];

   return actualSum-sum;
	
}
```
## Complexity
Time Complexity id O(n) 
