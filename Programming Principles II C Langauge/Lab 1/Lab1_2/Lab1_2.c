// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab1.c
// SPECIFICATION:  Mileage reimburssement calculator
// FOR:            CS 1412 Programming Principles II Section 002

#include <stdio.h>
#include <math.h>

int main(void)
{
    double car_price;
    double down_payment;
    double annual_interest_rate;
    int num_of_payments;
    double payment;

    printf("\nMontlhy payment calculator\n");

    printf("Enter the car's purchase price: ");
    scanf("%lf", &car_price);

    printf("Enter the down payment on the car: ");
    scanf("%lf", &down_payment);

    printf("Enter the annual interest rate: ");
    scanf("%lf", &annual_interest_rate);

    printf("Enter the total number of payments: ");
    scanf("%d", &num_of_payments);

    /* Calculate the monthly interest rate to by dividing the annual interst rate by 12 and divide by 100 to remove percent */
    double monthly_interest = ( annual_interest_rate / 12.0 )*(1.0/100.0);

    /* Calculate the monthly payment using the provided formula and inputed user variables */
    payment = ( monthly_interest * ( car_price-down_payment ) ) / ( 1 - pow( (1+monthly_interest), -num_of_payments ) );

    /* Displays the amount borrowed(purchase price minus down payment), and the cost of each monthly payment */
    printf("The amount borrowed is $%.2lf, and the montlhy payment is $%.2lf.\n\n", (car_price-down_payment), payment);

    return(0);

}