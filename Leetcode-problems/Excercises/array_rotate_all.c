#include <stdio.h>
#include <stdlib.h>

#define len 10
#define k 3

void reverse(int *arr, int start, int end)
{
        while(start < end) {
                int tmp = arr[start];
                arr[start] = arr[end];
                arr[end] = tmp;
                start ++; end--;
        }
}

void print(int * arr)
{
        for (int i = 0 ; i< 10; i++) {
                printf("%d, " , arr[i]);
        }
        printf("\n");
}

void RR(int *arr){
        // example: rotate 3 times, 8,9,10,1,2,3,4,5,6,7
        reverse(arr, 0, len -1);
        reverse(arr, 0, k-1);
        reverse(arr, k, len-1);
}

void LR(int *arr)
{
        reverse(arr, 0, k-1);
        reverse(arr, k, len-1);
        reverse(arr, 0, len -1);
}

int main() {

        int arr1[len] = {1,2,3,4,5,6,7,8,9,10};
        int arr2[len] = {1,2,3,4,5,6,7,8,9,10};


        printf("ORIGINAL     :");
        print(arr1);

        LR(arr1);
        printf("LEFT ROTATE  :");
        print(arr1);


        RR(arr2);
        printf("RIGHT ROTATE :");
        print(arr2);

        return 0;

}
