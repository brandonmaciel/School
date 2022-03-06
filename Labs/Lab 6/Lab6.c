// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab6.c
// SPECIFICATION:  UPC Scanner
// FOR:            CS 1412 Programming Principles II Section 502
// --------------------------------------------------------------------------------

#include <stdio.h>
/* macro for array size */
#define MAX 12

void UPC_input(int UPC_array[]);
int odd_postition_sum(int UPC_array[]);
int even_position_sum(int UPC_array[]);
int calculate_check_digit(int odd_even_sum);

int main(void){
    int UPC[MAX], odd_sum_3, odd_even_sum, check_digit;

    /* calls the function UPC_input */
    UPC_input(UPC);

    /* step 1 - calls the function odd_position_sum and multiplies the value times three, assigns it to odd_sum_3 */
    odd_sum_3 = odd_postition_sum(UPC) * 3;

    /* step 2 - calls the even_position_sum function and adds it to the value from step one, assigns it to odd_even_sum */
    odd_even_sum = even_position_sum(UPC) + odd_sum_3;

    /* calls calculate_check_digit to calculate the check digit */
    check_digit = calculate_check_digit(odd_even_sum);

    /* if statement to determine if UPC barcode is valid */
    if(check_digit == UPC[MAX - 1]){
        printf("Validated!\n");
    }
    else{
        printf("Error in barcode!\n");
    }

    /* Displays the steps involved to determining if UPC code is valid */
    printf("\nStep(1)\nSum of the digits in the odd-numbered positions times 3: %d\n\nStep(2)\nSum of the digits in the even-numbered positions plus the value of Step(1): %d\n\nCheck digit = %d\n\n", odd_sum_3, odd_even_sum, check_digit);

    return 0;
}

// NAME: UPC_input
// PARAMETERS: UPC_array[], a pointer to the UPC array
// OUTPUT: no output
// PURPOSE: this function prompts user for UPC code and stores it in an array
void UPC_input(int UPC_array[]){
    printf("Enter the 12 digit barcode separated by spaces: ");
    scanf("%d%d%d%d%d%d%d%d%d%d%d%d", &UPC_array[0], &UPC_array[1], &UPC_array[2], &UPC_array[3], &UPC_array[4], &UPC_array[5], &UPC_array[6], &UPC_array[7], &UPC_array[8], &UPC_array[9], &UPC_array[10], &UPC_array[11]);
}

// NAME: odd_position_sum
// PARAMETERS: UPC_array[], a pointer to the UPC array
// OUTPUT: returns the sum of the values in the odd position of the array
// PURPOSE: to find the sum of the odd position values
int odd_postition_sum(int UPC_array[]){
    int sum = 0;

    for (int i = 0; i < MAX; i++)
    {
        if((i % 2) == 0){
            sum += UPC_array[i];
        }
    }
    return sum;
}

// NAME: even_position_sum
// PARAMETERS: UPC_array[], a pointer to the UPC array
// OUTPUT: returns the sum of the values in the even position of the array
// PURPOSE: to find the sum of the even position values
int even_position_sum(int UPC_array[]){
    int sum = 0;

    for (int i = 0; i < MAX-1; i++)
    {
        if((i % 2) == 1){
            sum += UPC_array[i];
        }
    }
    return sum;
}

// NAME: calculate_check_digit
// PARAMETERS: step2_value, the value calculated in step 2
// OUTPUT: returns the check digit
// PURPOSE: to calculate the check digit
int calculate_check_digit(int step2_value){
    int check_digit;
    if((step2_value % 10) == 0){
        check_digit = 0;
    }
    else{
        check_digit = 10 - (step2_value % 10);
    }
    return check_digit;
}