#include <stdio.h>
#include <stdlib.h>


int main() {
        int dat = 1;
        char *ptr = (char *) &dat;
        printf("MSB: %p -> %d\n",ptr, *ptr);
        printf("MSB: %p -> %d\n",ptr+1, *(ptr + 1));
        printf("MSB: %p -> %d\n", ptr+2,(int) ptr[2]);
        printf("MSB: %p -> %d\n",ptr+3, ptr[3]);
        return 0;
}
