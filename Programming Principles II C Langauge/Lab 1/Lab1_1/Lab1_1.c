// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab1.c
// SPECIFICATION:  Mileage reimburssement calculator
// FOR:            CS 1412 Programming Principles II Section 002

#include <stdio.h>

int main(void)
{
       double odometer_start;
       double odometer_end;
       double miles_traveled;
       double reimbursement;

       /* Enter the beginning reading of the odometer */
       printf("\nMILEAGE REIMBURSEMENT CALCULATOR\n");
       printf("Enter beginning odometer reading => ");
       scanf("%lf", &odometer_start);

       /* Enter the end reading of the odometer */
       printf("Enter ending odometer reading => ");
       scanf("%lf", &odometer_end);

       /* Calculate and display traveled miles and reimbursement */
       miles_traveled = odometer_end - odometer_start;
       reimbursement = miles_traveled * 0.35;
       printf("You traveled %.1lf. At $0.35 per mile, your reimbursement is $ %.2lf.\n\n", miles_traveled, reimbursement);

       return (0);
}
