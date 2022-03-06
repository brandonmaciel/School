// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab2_1.c
// SPECIFICATION:  Music teacher’s discount policy receipt
// FOR:            CS 1412 Programming Principles II Section 002
#include <stdio.h>

int main(void) {
    
    double purchase_total, teacher_discount, discounted_total, sales_tax, total;
    char teacher; // holds y or n to determine if teacher or not
    int width = 40; // formatting to right align teacher's discount, discounted total, and sales tax
    FILE *receipt_txt; // initializes file to open

    /* Checks if file 'receipt.txt' exists, if not, it is created, else it overides old data */
    receipt_txt = fopen("receipt.txt","w");

    /* Enter the purchase total */
    printf("\nWhat is the purchase total? ");
    scanf("%lf", &purchase_total);

    /* Determine if teacher */
    printf("Are you a teacher, yes or no? ");
    scanf(" %c", &teacher);

    /* Displays the total purchase price right aligned on to the receipt.txt file */
    fprintf(receipt_txt, "Total Purchases                       $ %6.2lf\n", purchase_total);

    /* Switch case statement to determine if teacher or not */
    switch (teacher)
    {
        case 'Y':
        case 'y':
            /* If the purchase total is less than 100 then the teacher discount is 10 percent of the total before tax */
            if(purchase_total < 100)
            {
                teacher_discount = purchase_total * 0.10;
                discounted_total = purchase_total * 0.90;
                fprintf(receipt_txt, "Teacher's discount (10%%) %*.2lf\n", width-19 , teacher_discount);
            }
            /* If the purchase total is grater than or equal to 100 then the teacher discount is 12 percent of the total before tax */
            else
            {
                teacher_discount = purchase_total * 0.12;
                discounted_total = purchase_total * 0.88;
                fprintf(receipt_txt, "Teacher's discount (12%%) %*.2lf\n", width-19 , teacher_discount);
            }
            /* Displays the total with the teacher's discount applied on to the receipt.txt file */
            fprintf(receipt_txt, "Discounted total %*.2lf\n", width-11 , discounted_total);

            /* Calcualtes tax at 5 percent of the discounted total and displays it on to the receipt.txt file */
            sales_tax = discounted_total * 0.05;
            fprintf(receipt_txt, "Sales tax (5%%) %*.2lf\n", width-9 , sales_tax);
            total = discounted_total * 1.05;
            fprintf(receipt_txt, "Total                                 $ %6.2lf\n\n", total);
            break;
        case 'N':
        case 'n':
            /* Calculates the sales tax of the purchase total and displays it on to the receipt.txt file. Does not have teacher's discount */
            sales_tax = purchase_total * 0.05;
            fprintf(receipt_txt, "Sales tax (5%%) %*.2lf\n", width-9 , sales_tax);
            total = purchase_total * 1.05;
            fprintf(receipt_txt, "Total                                 $ %6.2lf\n\n", total);
            break;
    
        default:
            break;
    }
    /* closes the receipt.txt file */
    fclose(receipt_txt);
    printf("\nDone! Receipt created!\n\n");
    return 0;
}