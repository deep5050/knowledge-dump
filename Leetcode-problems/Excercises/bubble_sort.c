#include <stdio.h>
#include <stdlib.h>

void bubble(int *arr, int size)
{
        int flag =1, count =0;
        while(flag) {
                count = 0;
                for (int i = 1; i< size; i++) {
                        if (arr[i] < arr[i-1])
                        {
                                int tmp = arr[i-1];
                                arr[i-1] = arr[i];
                                arr[i] = tmp;
                                count++;
                        }
                }
                if (count == 0 ) flag = 0;
        }
}

int main() {
        int arr[5]  = {3,9,4,7,3};
        bubble(arr, 5);

        for (int i =0 ;i < 5; i++) {
                printf("%d ", arr[i]);
        }
        return 0;
}
