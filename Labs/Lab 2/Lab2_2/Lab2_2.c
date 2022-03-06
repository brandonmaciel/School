// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab2_2.c
// SPECIFICATION:  Half life of Cobalt-60 calculator
// FOR:            CS 1412 Programming Principles II Section 002

#include <stdio.h>
#include <math.h>

int main(void){

    double remainder,
        initial_amount,
        constant,
        years_elapsed = 5,
        half_life = 5.272;
    int count; // used in for loop to count years
    
    /* C is the constant that is expressed as e^(-0.693) (2.71828) */
    constant = pow(2.71828,-0.693);

    /* Prompts user to enter the initial presence of the isotope in grams */
    printf("\nEnter the intial presence of the isotope: ");
    scanf("%lf", &initial_amount);
    printf("\nYears Elapsed      Cobalt-60 Remaining\n");

    /* for loop displays the amount remaining for each year that elapses */
    for(count = 0; count <= years_elapsed; count++){
        /* applies the formula given using the constant and variables provided */
        remainder = initial_amount * (pow(constant, (count/half_life)));
    
        /* Displays the amount remaining */
        printf("%7d %23.3lf g\n", count, remainder);
    }
    printf("\n");
    return 0;
    
}