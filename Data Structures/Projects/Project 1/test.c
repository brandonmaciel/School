#include <stdio.h>

typedef struct test{
    int a;
    int b;
}tst;

int main(void){
    tst a;

    __asm__("movl %edx, %eax\n\t"
            "addl $2, %eax\n\t");
    
    
    return 0;
}

