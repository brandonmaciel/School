// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab5.c
// SPECIFICATION:  Simple Calculator
// FOR:            CS 1412 Programming Principles II Section 502
// --------------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>

/* funciton prototypes */
void scan_data(char *operator, double *operand);
void do_next_op(char operator, double operand, double *accumulator);

int main(void){
    char operator;
    double operand,
        accumulator = 0;

    printf("\nSimple Calculator\n\n");

    /* do while loop to keep looping until 'q' or 'Q' have been scanned */
    do
    {
        scan_data(&operator, &operand);
        do_next_op(operator, operand, &accumulator);
    } while (operator != 'q' && operator != 'Q');
    
    return 0;
}

// NAME: scan_data
// PARAMETERS: operatorp, pointer to operator; operandp, pointer to operand
// OUTPUT: two output parameters that returns the operator and right operand scanned from a data line
// PURPOSE: this function scans the user operator and operand
void scan_data(char *operatorp, double *operandp){
    scanf(" %c %lf", operatorp, operandp);
}

// NAME: do_next_op
// PARAMETERS: operator, the operator; operand, the operand; accumulatorp, keeps track of the actions performed.
// OUTPUT: the output is the accumulatorp
// PURPOSE: this function identifies the operator and performs the computation with the given operand
void do_next_op(char operator, double operand, double *accumulatorp){
    switch (operator)
    {
    case '+':
        *accumulatorp += operand;
        printf("result so far is %.1lf\n\n", *accumulatorp);
        break;
    case '-':
        *accumulatorp -= operand;
        printf("result so far is %.1lf\n\n", *accumulatorp);
        break;
    case '*':
        *accumulatorp *= operand;
        printf("result so far is %.1lf\n\n", *accumulatorp);
        break;
    case '/':
        *accumulatorp /= operand;
        printf("result so far is %.1lf\n\n", *accumulatorp);
        break;
    case '^':
        *accumulatorp = pow(*accumulatorp, operand);
        printf("result so far is %.1lf\n\n", *accumulatorp);
        break;
    case 'Q':
    case 'q':
        printf("final result is %.1lf\n\n", *accumulatorp);
        break;
    
    default:
        printf("BAD DATA!\n");
        break;
    }

}