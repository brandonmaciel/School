// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab7.c
// SPECIFICATION:  Name and age list
// FOR:            CS 1412 Programming Principles II Section 502
// --------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

/* macro for how many people's name in list */
#define PEOPLE 6

int average_age(int *age_array);
void youngest(char *names_array[], int age_array[]);

int main(void){
    char *names[PEOPLE] = {"Ryan, Elizabeth", "McIntyre, Osborne", "DuMond, Kristin", "Larson, Lois", "Thorpe, Trinity", "Ruiz, Pedro"},
        alphabetized_names[PEOPLE][100],
        update_name[100];

    int ages[PEOPLE] = {62, 84, 18, 42, 15, 35},
        update_age,
        /* i - index for for loop */
        i,
        alphabetized_age[PEOPLE];
    
    /* copies original name and age lists to new lists */
    for(i = 0; i < PEOPLE; ++i){
        strcpy(alphabetized_names[i], names[i]);
        alphabetized_age[i] = ages[i];
    }

    /* displays the original name and age lists */
    printf("\nOriginal list\n");
    printf("-----------------------------\n");
    for(int index = 0; index < PEOPLE; ++index){
        printf("    %-17s    %d\n", alphabetized_names[index], alphabetized_age[index]);
    }

    /* alphabetizes the list of names and its respective age */
    printf("\n\nAlphabetized list\n");
    printf("-----------------------------\n");
    /* number of times it goes through the sorting process */
    for(i = 1; i <= (int)(PEOPLE/2); ++i){
        /* for loop for the name in name and age array */
        for(int name = 0; name < PEOPLE; ++name){
            /* for loop for character y of x name in name array */
            for(int character = 0; character < ((int)strlen(alphabetized_names[name]) - 1); ++character){
                /* if statement for if the position is less that the array size */
                if((name + 1) < PEOPLE){
                    /* if the first character of the first name is greater that the character of the next name, it switches the position of names and the respective age */
                    if(alphabetized_names[name][character] > alphabetized_names[name + 1][character]){
                        strcpy(update_name, alphabetized_names[name]);
                        strcpy(alphabetized_names[name], alphabetized_names[name + 1]);
                        strcpy(alphabetized_names[name + 1], update_name);

                        update_age = alphabetized_age[name];
                        alphabetized_age[name] = alphabetized_age[name + 1];
                        alphabetized_age[name + 1] = update_age;
                        /* breaks out of for loop */
                        break;
                    }
                    /* else if it is the same character then it goes through for loop again(does not break out of for loop) */
                    else if (alphabetized_names[name][character] == alphabetized_names[name + 1][character]){
                        /* do nothing */
                        name = name;
                    }
                    else{
                        break;
                    }
                } 
            }
            /* prints the alphabetized list on the last sorting process */
            if(i == (int)(PEOPLE/2))
                printf("    %-17s    %d\n", alphabetized_names[name], alphabetized_age[name]);
        }
    }
    printf("\n");

    youngest(names, ages);
    int avg_age = average_age(ages);
    
    return 0;
}

// NAME: average_age
// PARAMETERS: *age_array, the array with age values
// OUTPUT: returns the average age
// PURPOSE: to calculate the average age
int average_age(int *age_array){
    double avg_age;

    /* adds all the ages in array */
    for(int index = 0; index < PEOPLE; ++index){
        avg_age += age_array[index];
    }

    /* divides by the number of ages in array */
    avg_age = avg_age/PEOPLE;

    /* displays the average age */
    printf("Age Average: %.2f\n\n", avg_age);

    return avg_age;
}

// NAME: youngest
// PARAMETERS: *names_array[], the string array with names; age_array[], the int array with ages
// OUTPUT: void
// PURPOSE: to find and display the youngest
void youngest(char *names_array[], int age_array[]){
    int min, youngest;
    for(int i = 0; i < PEOPLE; ++i){
        if(min > age_array[i]){
            min = age_array[i];
            youngest = i;
        }
    }
    printf("Youngest: %s %d\n", names_array[youngest], min);
}

/* 
DuMond, Kristin:    18
Larson, Lois:       42
McIntyre, Osborne:  84
Ruiz, Pedro:        35
Ryan, Elizabeth:    62
Thorpe, Trinity:    15
*/