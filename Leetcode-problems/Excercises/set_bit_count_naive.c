#include <stdio.h>
#include <stdlib.h>



int main() {
        for (int s = 0; s< 100; s++) {
        int count = 0;
        for (int i = 1; i<= 32; i++) {
                int flag = s & (1<<i);
                if (flag) count++;
        }
        printf("count: %d\n", count);
        }
return 0;
}
