// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab3.c
// SPECIFICATION:  Weekly Pay Calculator
// FOR:            CS 1412 Programming Principles II Section 002
// --------------------------------------------------------------------------------

#include <stdio.h>

/* used as a buffer to avoid infinite looping */
int clean_stdin()
{
    while (getchar()!='\n');
    return 1;
}

int main(void){
    int paycode,
        items_produced, // Pieceworker's number of items produced
        count_manager = 0,
        count_hourly_worker = 0,
        count_commission_worker = 0,
        count_pieceworker = 0;
    double salary, // Amount paid, weekly, hourly, percentages, or per item.
        hours_worked,
        weekly_pay;

    /* Do while loop to keep looping until -1 gets inputted */
    do
    {
        printf("Enter paycode ( -1 to end): ");
        scanf("%d", &paycode);

        /* Switch case to determine how the weekly pay is calculated */
        switch (paycode)
        {
            /* Manager Weekly Pay */
            case 1:
                printf("Manger selected.\n");

                printf("Enter weekly salary: ");
                scanf("%lf", &salary);

                /* calculates and displays weekly pay */
                weekly_pay = salary;
                printf("The manager's pay is $%.2lf\n\n", weekly_pay);

                /* keeps track of number of managers getting paid */
                count_manager ++;
                break;
            /* Hourly Worker Weekly Pay */
            case 2:
                printf("Hourly worker selected.\n");
                printf("Enter hourly wage: ");
                scanf("%lf", &salary);

                printf("Enter hours worked: ");
                scanf("%lf", &hours_worked);

                /* calculates weekly at the fixed hourly wage */
                if(hours_worked <= 40){
                    weekly_pay = salary * hours_worked;
                }
                /* calculates weekly pay with overtime at a rate of 1.5 times the hourly wage */
                else    
                {
                    weekly_pay = (40 * salary) + ((hours_worked - 40) * (salary * 1.5));
                }
                
                printf("The hourly worker's pay is $%.2lf\n\n", weekly_pay);

                /* keeps track of number of hourly workers getting paid */
                count_hourly_worker ++;
                break;
            /* Commission Worker Weekly Pay */
            case 3:
                printf("Commission worker selected.\n");
                printf("Enter gross weekly sales: ");
                scanf("%lf", &salary);
                
                /* calculates weekly pay: $250 + 5.7% of gross weekly sales */
                weekly_pay = 250 + (salary * 0.057);

                printf("The commission worker's pay is $%.2lf\n\n", weekly_pay);

                /* keeps track of number of managers getting paid */
                count_commission_worker ++;
                break;
            /* Pieceworker Weekly Pay */
            case 4:
                printf("Pieceworker selected.\n");
                printf("Enter number of items produced: ");
                scanf("%d", &items_produced);

                printf("Enter pay per item produced: ");
                scanf("%lf", &salary);

                /* calculates weekly pay by multiplying the fixed amount of money for
                each item produced by the number of items produced */
                weekly_pay = salary * items_produced;

                printf("The pieceworker's pay is $%.2lf\n\n", weekly_pay);
                
                /* keeps track of number of managers getting paid */
                count_pieceworker ++;
                break;
            /* ends program */
            case -1:
                printf("\n");
                break;
            /* invalid paycodes used */
            default:
                printf("Invalid pay code.\n\n");
                break;
        }
    } while ((paycode != -1) && clean_stdin());

    printf("Total number of managers paid           : %d\n", count_manager);
    printf("Total number of hourly workers paid     : %d\n", count_hourly_worker);
    printf("Total number of commission workers paid : %d\n", count_commission_worker);
    printf("Total number of pieceworkers paid       : %d\n\n", count_pieceworker);

    return 0;
}