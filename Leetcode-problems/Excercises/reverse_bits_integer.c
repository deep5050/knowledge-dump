#include <stdio.h>
#include <stdlib.h>



int main()
{
        unsigned int x = 3;
        unsigned out = 0;
        unsigned int *ptr = &out;
        size_t numbits = sizeof(unsigned int) * 8;
        // need to reverse
        for (int i = 0 ; i< numbits ; i++) {
                unsigned int bit = x & (1U<<i);
                if (bit)
                        out = out | (1<<(numbits-i-1));
        }
        printf("After rev: %u \n",out);
        return 0;
}
