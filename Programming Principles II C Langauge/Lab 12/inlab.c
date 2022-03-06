#include <stdio.h>
#include <math.h>
#define ABSDF(x, y) (fabs((x) - (y)))

int main(void){
    int a, b, c, lgdiff;
    // Before Expansion:  
    if (ABSDF(a + b, c) > ABSDF(b + c, a))
        lgdiff = ABSDF(a + b, c);  
    // After Expansion:
    if(fabs((a+b) - c) > fabs((b+c) - a)){
        lgdiff = fabs((a+b) - c);
    }
}