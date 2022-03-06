// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab9.c
// SPECIFICATION:  Product Categories
// FOR:            CS 1412 Programming Principles II Section 502
// --------------------------------------------------------------------------------

#include <stdio.h>

/* structure defined */
typedef struct ProductCategory{
    char item[20];
    int unit_cost;
    char product_category;

    /* meats */
    char meat_type;
    int date_packaged_day;
    int date_packaged_month;
    int date_packaged_year;
    int expiration_date_day;
    int expiration_date_month;
    int expiration_date_year;

    /* produce */
    char produce_type;
    int date_received_day;
    int date_received_month;
    int date_received_year;

    /* dairy 
        expiration date in meats
    */
    
    /* canned goods */
    int aisle_number;
    char aisle_side;
    /* non-foods */
    char indicating_category;
    
}productCategory; /* alias to ProductCategory */

void scan_product_info(productCategory*);
void output_product_info(productCategory);

int main(void){
    productCategory pc;

    scan_product_info(&pc);
    output_product_info(pc);

    return 0;
}

// NAME: scan_product_info
// PARAMETERS: *pcp, the structure to be filled with scanned data
// OUTPUT: no output, it is scanned and modified using a pointer
// PURPOSE: to scan information into the structure pcp
void scan_product_info(productCategory *pcp){
	printf("Enter prodcut info in a single line: ");
	scanf(" %s %d %c", pcp->item, &pcp->unit_cost, &pcp->product_category);
	printf("\n");

    /* switch statment determines general category of item/product */
    switch (pcp->product_category)
    {   /* meats */
        case 'M':
            /* meat type, date of packaging (format: mm/dd/yy), expiration date (format: mm/dd/yy) */
            scanf(" %c%d%d%d%d%d%d", &pcp->meat_type, &pcp->date_packaged_month, &pcp->date_packaged_day, &pcp->date_packaged_year, &pcp->expiration_date_month, &pcp->expiration_date_day, &pcp->expiration_date_year);
            break;
        /* produce */
        case 'P':
            /* produce type ('F' for fruit or 'V' for vegetable), date received (format: mm/dd/yy) */
            scanf(" %c%d%d%d", &pcp->produce_type, &pcp->date_received_month, &pcp->date_received_day, &pcp->date_received_year);
            break;
        /* dairy */
        case 'D':
            /* expiration (format: mm/dd/yy) */
            scanf("%d%d%d", &pcp->expiration_date_month, &pcp->expiration_date_day, &pcp->expiration_date_year);
            break;
        /* canned goods */
        case 'C':
            /* expiration date (format: mm/yy), aisle number, aisle side */
            scanf("%d%d%d %c", &pcp->expiration_date_month, &pcp->expiration_date_year, &pcp->aisle_number, &pcp->aisle_side);
            break;
        /* nonfoods */
        case 'N':
            /* indicating category, aisle number, aisle side */
            scanf(" %c%d %c", &pcp->indicating_category, &pcp->aisle_number, &pcp->aisle_side);
        default:
            printf("Unknown category.\n");
            break;
    }
}

// NAME: output_product_info
// PARAMETERS: pc, the structure to be displayed/output
// OUTPUT: no output, it is displayed
// PURPOSE: to display the information in structure pc
void output_product_info(productCategory pc){
    char month[12][20] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    printf("The %s costs %d cents, ", pc.item, pc.unit_cost);
    
    /* switch type to determine general category */
    switch (pc.product_category)
    {   
        /* meats */
        case 'M':
            /* switch statement to determine meat type (sub-category) */
            switch (pc.meat_type)
            {   
                /* red meats */
                case 'R':
                    printf("is red meat, ");
                    break;
                /* poultry */
                case 'P':
                    printf("is poultry, ");
                    break;
                /* fish */
                case 'F':
                    printf("is fish, ");
                    break;
                default:
                    printf("type of meat not specified, ");
                    break;
            }
            printf("was packaged on %s %d, %d, and expires on %s %d, %d.\n", month[pc.date_packaged_month - 1], pc.date_packaged_day, pc.date_packaged_year, month[pc.expiration_date_month - 1], pc.expiration_date_day, pc.expiration_date_year);
            break;
        /* produce */
        case 'P':
            /* determines produce type (sub-category) */
            switch (pc.produce_type)
            {
                /* fruit */
                case 'F':
                    printf("is a fruit, ");
                    break;
                /* vegetable */
                case 'V':
                    printf("is a vegetable, ");
                    break;
                default:
                    printf("type of produce not specified, ");
                    break;
            }
            printf("and was recieved on %s %d, %d.\n", month[pc.date_received_month - 1], pc.date_received_day, pc.date_received_year);
            break;
        /* dairy */
        case 'D':
            printf("and expires on %s %d, %d.\n", month[pc.expiration_date_month - 1], pc.expiration_date_day, pc.expiration_date_year);
            break;
        /* canned goods */
        case 'C':
            printf("and expires in %s of %d, and is displayed in aisle %d", month[pc.expiration_date_month - 1], pc.expiration_date_year, pc.aisle_number);
            /* determines if aisle side is valid */
            switch (pc.aisle_side)
            {
                case 'A':
                    printf("A.\n");
                    break;
                case 'B':
                    printf("B.\n");
                    break;
                default:
                    printf(" aisle side not specified or not valid.\n");
                    break;
            }
            break;
        /* nonfoods */
        case 'N':
            /* determines sub-category for nonfoods */
            switch (pc.indicating_category)
            {   
                /* cleaning */
                case 'C':
                    printf("is a cleaning product, ");
                    break;
                /* pharmacy */
                case 'P':
                    printf("is a pharmacy product, ");
                    break;
                /* other */
                case 'O':
                    printf("is other category, ");
                    break;
                default:
                    printf("category not indicated, ");
                    break;
            }
            printf("and is displayed on aisle %d", pc.aisle_number);
            /* determines if ailse side is valid */
            switch (pc.aisle_side)
            {
                case 'A':
                    printf("A.\n");
                    break;
                case 'B':
                    printf("B.\n");
                    break;
                default:
                    printf(" aisle side not specified or not valid.\n");
                    break;
            }
            break;
        default:
            break;
    }
    printf("\n");
}