// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab4.c
// SPECIFICATION:  Calculation of Intravenous Rates
// FOR:            CS 1412 Programming Principles II Section 502
// --------------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>

int get_problem(void);
void get_rate_drop_factor(double *rate_ml_hr, double *drop_factor);
void get_hours_liter(double *rate_hour_liter);
void get_kg_rate_conc(double *rate_mg_kg_hr, double *weight, double *conc_mg_ml);
void get_units_conc(double *rate_units_hr, double *conc_units_ml);
int fig_drops_min(double rate, double drop_factor);
int fig_ml_hr(double num_hours);
int by_weight(double rate_mg_kg_hr, double weight_kg, double conc_mg_ml);
int by_units(double rate_units_hr, double conc_units_ml);

/* used as a buffer to avoid infinite looping */
int clean_stdin()
{
    while (getchar()!='\n');
    return 1;
}

int main(void){
    int problem, /* problem code */
        drops_min, 
        ml_hr; /* milliliters per hour */
    double rate,
        drop_factor,
        weight, /* weight in kg */
        concentration;

    printf("INTRAVENOUS RATE ASSISTANT\n\n");
    /* assigns the return function value from get_problem() to problem */
    problem = get_problem();
    
    /* sentinel controlled loop to loop until quit code is inputted */
    while((problem != 5) && clean_stdin()){
        /* switch case for different medical codes */
        switch (problem)
        {   
            /* calculates and displays drop rate per minute given millilters per hour and tubing drop factor */
            case 1:
                get_rate_drop_factor(&rate, &drop_factor);
                drops_min = fig_drops_min(rate, drop_factor);
                printf("The drop rate per minute is %d.\n\n", drops_min);
                break;
            /* calculates and displays milliliters per hour given hours per liter */
            case 2:
                get_hours_liter(&rate);
                ml_hr = fig_ml_hr(rate);
                printf("The rate in milliliters per hour is %d.\n\n", ml_hr);
                break;
            /* calculates and displays milliliters per hour given (mg/kg)/hr and concentration in mg per milliliter */
            case 3:
                get_kg_rate_conc(&rate, &weight, &concentration);
                ml_hr = by_weight(rate, weight, concentration);
                printf("The rate in milliliters per hour is %d.\n\n", ml_hr);
                break;
            /* calculates and displays milliliters per hour given units per hour and concentration in units per milliliter*/
            case 4:
                get_units_conc(&rate, &concentration);
                ml_hr = by_units(rate, concentration);
                printf("The rate in milliliters per hour is %d.\n\n", ml_hr);
                break;
            /* wrong data type or wrong problem code */
            default:
                printf("BAD INPUT!\n");
                break;
        }
        problem = get_problem();
    }
}

// NAME: get_problem
// INPUT PARAMETERS: 
// OUTPUT: an int number, the problem code inputted by user
// PURPOSE: the function displays the user menu and prompts the user to enter the problem code.
int get_problem(){
    int problem_out;

    printf("Enter the number of the problem you wish to solve.\n");
    printf("%4cGIVEN A MEDICAL ORDER IN %15cCALCULATE RATE IN\n", ' ', ' ');

    printf("(1) ml/hr & tubing drop factor %12c drops / min\n", ' ');
    printf("(2) 1 L for n hr %26c ml / hr\n", ' ');
    printf("(3) mg/kg/hr & concentration in mg/ml %5c ml / hr\n", ' ');
    printf("(4) units/hr & concentration in units/ml %2c ml / hr\n", ' ');
    printf("(5) QUIT\n\n");

    printf("Problem> ");
    scanf("%d", &problem_out);
    return problem_out;
}

// NAME: get_rate_drop_factor
// INPUT PARAMETERS: rate_ml_hr, drop_factor
// OUTPUT: user inputted data
// PURPOSE: the function prompts the user to enter date required for problem 1 and returns it to the calling module using output parameters
void get_rate_drop_factor(double *rate_ml_hr, double *drop_factor){
    printf("Enter rate in ml/hr=> ");
    scanf("%lf", rate_ml_hr);

    printf("Enter tubing's drop factor(drops/ml)=> ");
    scanf("%lf", drop_factor);

}

// NAME: get_hours_liter
// INPUT PARAMETERS: rate_hours_liter
// OUTPUT: user inputted data
// PURPOSE: the function prompts the user to enter date required for problem 2 and returns it to the calling module using output parameters
void get_hours_liter(double *rate_hour_liter){
    printf("Enter number of hours=> ");
    scanf("%lf", rate_hour_liter);
}

// NAME: get_kg_rate_conc
// INPUT PARAMETERS: rate_mg_kg_hr, weight, conc_mg_ml
// OUTPUT: user inputted data
// PURPOSE: the function prompts the user to enter date required for problem 3 and returns it to the calling module using output parameters
void get_kg_rate_conc(double *rate_mg_kg_hr, double *weight, double *conc_mg_ml){
    printf("Enter rate in mg/kg/hr=> ");
    scanf("%lf", rate_mg_kg_hr);

    printf("Enter patient weight in kg=> ");
    scanf("%lf", weight);

    printf("Enter concentration in mg/ml=> ");
    scanf("%lf", conc_mg_ml);

}

// NAME: get_units_conc
// INPUT PARAMETERS: rate_units_hr, conc_units_ml
// OUTPUT: user inputted data
// PURPOSE: the function prompts the user to enter date required for problem 4 and returns it to the calling module using output parameters
void get_units_conc(double *rate_units_hr, double *conc_units_ml){
    printf("Enter rate in units/hr=> ");
    scanf("%lf", rate_units_hr);

    printf("Enter concentration in units/ml=> ");
    scanf("%lf", conc_units_ml);
    
}

// NAME: fig_drops_min
// INPUT PARAMETERS: rate_mg_kg_hr, weight, conc_mg_ml
// OUTPUT: user inputted data
// PURPOSE: the function prompts the user to enter date required for problem 3 and returns it to the calling module using output parameters
int fig_drops_min(double rate, double drop_factor){
    int drops_min;

    drops_min = round((drop_factor * rate) / 60.0);
    return drops_min;
}

/* problem 2 calculations */
int fig_ml_hr(double num_hours){
    int ml_hr;

    ml_hr = round(1000.0 / num_hours);
    return ml_hr;
}

/* problem 3 calculations */
int by_weight(double rate_mg_kg_hr, double weight_kg, double conc_mg_ml){
    int ml_hr;

    ml_hr = round((rate_mg_kg_hr / conc_mg_ml) * weight_kg);
    return ml_hr;
}

/* problem 4 calculations */
int by_units(double rate_units_hr, double conc_units_ml){
    int ml_hr;

    ml_hr = round(rate_units_hr / conc_units_ml);
    return ml_hr;
}