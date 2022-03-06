#include <stdio.h>
#include <string.h>

#define MAX 100 /* max size of flight records */

typedef struct Date_time{
    char date[50];
    char time[50];
}date_time_t;


typedef struct Flight_Information
{
    char flight_number[10];
    char city_of_departure[50];
    char destination[50];
    date_time_t departure;
    date_time_t arrival;
    int fc_seats_available; /* number of first-class seats still available */
    int fc_seats_sold; /* number of first-class seats sold */
    int c_seats_available; /* number of coach seats still available */
    int c_seats_sold; /* number of coach seats sold */
}flight_information_t;

// NAME: create
// PARAMETERS: NA
// OUTPUT: struct Flight_Information
// PURPOSE: to scan a information into a struct Flight_Information variable
flight_information_t create(){
    flight_information_t new_flight_record;
    
    /* prompts for flight record info and scans to a new_flight_record */
    printf("\tEnter the flight number: ");
    scanf("%s", new_flight_record.flight_number);
    printf("\tEnter city of departure: ");
    scanf("%s", new_flight_record.city_of_departure);
    printf("\tEnter destination: ");
    scanf("%s", new_flight_record.destination);
    printf("\tEnter date (format mm/dd/yyyy) and time (format: hh:mm) of departure (ex. 07/04/1776 18:32): ");
    scanf("%s%s", new_flight_record.departure.date, new_flight_record.departure.time);
    printf("\tEnter date (format mm/dd/yyyy) and time (format: hh:mm) of arrival (ex. 07/04/1776 18:32): ");
    scanf("%s%s", new_flight_record.arrival.date, new_flight_record.arrival.time);
    printf("\tEnter the number of first class seats available: ");
    scanf("%d", &new_flight_record.fc_seats_available);
    printf("\tEnter the number of first class seats sold: ");
    scanf("%d", &new_flight_record.fc_seats_sold);
    printf("\tEnter the number of coach seats available: ");
    scanf("%d", &new_flight_record.c_seats_available);
    printf("\tEnter the number of coach seats sold: ");
    scanf("%d", &new_flight_record.c_seats_sold);
    /* returns a new flight record */
    return new_flight_record; 
}

// NAME: deletion
// PARAMETERS: *flight_records, a struct Flight_Information that has all the flight records: records, an int type that keeps track of the flight records
// OUTPUT: int type to determine if the flight record was successfully deleted
// PURPOSE: to delete a flight record
int deletion(flight_information_t *flight_records, int records){
    char flight_num_input[10];
    int flight_rec, i;
    /* prompts user for flight record and scans it to flight_num_input */
    printf("\tEnter the flight number for the flight record to be deleted: ");
    scanf("%s", flight_num_input);
    /* loops through all flight records */
    for(i = 0; i < records; i++){
        /* checks if flight_num_input matches a flight record */
        if(strcmp(flight_records[i].flight_number, flight_num_input) == 0){
            /* shifts flight record essentially deleting it */
            for(flight_rec = i; flight_rec < records; ++flight_rec){
                flight_records[flight_rec] = flight_records[flight_rec + 1];
            }
            /* return 1 to confirm deletion */
            return 1;
        }
    }
    /* return 0 means not deleted */
    return 0;
}

// NAME: update
// PARAMETERS: *flight_records, a struct Flight_Information that has all the flight records: records, an int type that keeps track of the flight records
// OUTPUT: int type to determine if the flight record was successfully updated
// PURPOSE: to update an existing flight record
int update(flight_information_t *flight_records, int records){
    char flight_num_input[10],
        char_temp[50], /* temporary string variable to store previous flight_record member */
        char_temp_sec[50]; /* second temporary string variable to store previous flight_record member */
    int flight_rec,
        i,
        user_input,
        int_temp; /* temporary integer variable to store previous flight_record member */
    printf("\tEnter the flight number for the flight record to be updated: ");
    scanf("%s", flight_num_input);
    for(i = 0; i < records; i++){
        if(strcmp(flight_records[i].flight_number, flight_num_input) == 0){
            /* chose which to update options */
            printf("\n\t1: update flight number\n");
            printf("\t2: update city of departure\n");
            printf("\t3: update destination\n");
            printf("\t4: update date and time of departure\n");
            printf("\t5: update date and time of arrival\n");
            printf("\t6: update number of first-class seats still available\n");
            printf("\t7: update number of first-class seats sold\n");
            printf("\t8: update number of coach seats still available\n");
            printf("\t9: update number of coach seats sold\n");
            printf("\t10: quit\n\n");
            printf("\tEnter the action to be completed: ");
            scanf("%d", &user_input);
            do
            {
                switch (user_input)
                {   
                    /* update flight number */
                    case 1:
                        strcpy(char_temp, flight_records[i].flight_number);
                        /* prompts for update information */
                        printf("\tEnter updated flight number: ");
                        scanf("%s", flight_records[i].flight_number);
                        /* displays change old ---> new */
                        printf("\t%s ---> %s\n",char_temp, flight_records[i].flight_number);
                        break;
                    /* update city of departure */
                    case 2:
                        strcpy(char_temp, flight_records[i].city_of_departure);
                        /* prompts for update information */
                        printf("\tEnter updated city of departure: ");
                        scanf("%s", flight_records[i].city_of_departure);
                        /* displays change old ---> new */
                        printf("\t%s ---> %s\n",char_temp, flight_records[i].city_of_departure);
                        break;
                    /* update destination */
                    case 3:
                        strcpy(char_temp, flight_records[i].destination);
                        /* prompts for update information */
                        printf("\tEnter updated destination: ");
                        scanf("%s", flight_records[i].destination);
                        /* displays change old ---> new */
                        printf("\t%s ---> %s\n",char_temp, flight_records[i].destination);
                        break;
                    /* update date and time of departure */
                    case 4:
                        strcpy(char_temp, flight_records[i].departure.date);
                        strcpy(char_temp_sec, flight_records[i].departure.time);
                        /* prompts for update information */
                        printf("\tEnter updated date (format mm/dd/yyyy) and time (format: hh:mm) of departure (ex. 07/04/1776 18:32): ");
                        scanf("%s%s", flight_records[i].departure.date, flight_records[i].departure.time);
                        /* displays change old ---> new */
                        printf("\t%s %s ---> %s %s\n",char_temp, char_temp_sec, flight_records[i].departure.date, flight_records[i].departure.time);
                        break;
                    /* update date and time of arrival */
                    case 5:
                        strcpy(char_temp, flight_records[i].arrival.date);
                        strcpy(char_temp_sec, flight_records[i].arrival.time);
                        /* prompts for update information */
                        printf("\tEnter updated date (format mm/dd/yyyy) and time (format: hh:mm) of arrival (ex. 07/04/1776 18:32): ");
                        scanf("%s%s", flight_records[i].arrival.date, flight_records[i].arrival.time);
                        /* displays change old ---> new */
                        printf("\t%s %s ---> %s %s\n",char_temp, char_temp_sec, flight_records[i].arrival.date, flight_records[i].arrival.time);
                        break;
                    /* update the number of first-class seats available */
                    case 6:
                        int_temp = flight_records[i].fc_seats_available;
                        /* prompts for update information */
                        printf("\tEnter the updated number of first class seats available: ");
                        scanf("%d", &flight_records[i].fc_seats_available);
                        /* displays change old ---> new */
                        printf("\t%d ---> %d\n",int_temp, flight_records[i].fc_seats_available);
                        break;
                    /* update the nubmer of first-class seats sold */
                    case 7:
                        int_temp = flight_records[i].fc_seats_sold;
                        /* prompts for update information */
                        printf("\tEnter the updated number of first class seats sold: ");
                        scanf("%d", &flight_records[i].fc_seats_sold);
                        /* displays change old ---> new */
                        printf("\t%d ---> %d\n",int_temp, flight_records[i].fc_seats_sold);
                        break;
                    /* update the number of coach seats available */
                    case 8:
                        int_temp = flight_records[i].c_seats_available;
                        /* prompts for update information */
                        printf("\tEnter the updated number of coach seats available: ");
                        scanf("%d", &flight_records[i].c_seats_available);
                        /* displays change old ---> new */
                        printf("\t%d ---> %d\n",int_temp, flight_records[i].c_seats_available);
                        break;
                    /* update the nubmer of coach seats sold */
                    case 9:
                        int_temp = flight_records[i].c_seats_sold;
                        /* prompts for update information */
                        printf("\tEnter the updated number of coach seats sold: ");
                        scanf("%d", &flight_records[i].c_seats_sold);
                        /* displays change old ---> new */
                        printf("\t%d ---> %d\n",int_temp, flight_records[i].c_seats_sold);
                        break;
                    case 10:
                        break;
                    default:
                        printf("\tPlease enter a valid choice (1-10)\n");
                        break;
                }
                printf("\n\tEnter the action to be completed: ");
                scanf("%d", &user_input);
            } while (user_input != 10);
            return 1;
        }
    }
    return 0;
}

// NAME: make_reservation
// PARAMETERS: *flight_records, a struct Flight_Information that has all the flight records: records, an int type that keeps track of the flight records
// OUTPUT: int type to determine if a reservation was successfully created
// PURPOSE: to make a reservation
int make_reservation(flight_information_t *flight_records, int records){
    char airline_code[10];
    int flight_rec, i, user_input, loop, reservation;
    printf("\tEnter the flight number to make a seat reservation: ");
    scanf("%s", airline_code);
    for(i = 0; i < records; i++){
        if(strcmp(flight_records[i].flight_number, airline_code) == 0){
            loop = 1;
            do{
                printf("\tFor first class enter 1, for coach enter 2: ");
                scanf("%d", &user_input);
                switch(user_input){
                    case 1:
                        if(flight_records[i].fc_seats_available > 0){
                            printf("\tFirst class reserved!\n");
                            flight_records[i].fc_seats_sold++;
                            flight_records[i].fc_seats_available--;
                            reservation = 1;
                        }
                        else{
                            printf("\tFirst class seats sold out!\n");
                            reservation = 2;
                            loop = 1;
                        }
                        break;
                    case 2:
                        if(flight_records[i].c_seats_available > 0){
                            printf("\tCoach reserved!\n");
                            flight_records[i].c_seats_sold++;
                            flight_records[i].c_seats_available--;
                            reservation = 1;
                        }
                        else{
                            printf("\tCoach seats sold out!\n");
                            reservation = 2;
                            loop = 1;
                        }
                        break;
                    default:
                        printf("\tInvalid selection. Please select a valid selection (1-2).");
                        break;
                }
                printf("\n\tWould you like to make another reservation? 0: no, 1: yes:: ");
                scanf("%d", &loop);
            }while (loop != 0);
            return reservation;
        }
    }
    return 0;
}

// NAME: cancel_reservation
// PARAMETERS: *flight_records, a struct Flight_Information that has all the flight records: records, an int type that keeps track of the flight records
// OUTPUT: int type to determine if a reservation was successfully cancelled
// PURPOSE: to cancel a reservation
int cancel_reservation(flight_information_t *flight_records, int records){
    char airline_code[10];
    int flight_rec, i, loop, user_input, reservation;
    printf("\tEnter the flight number for the flight record to be deleted: ");
    scanf("%s", airline_code);
    for(i = 0; i < records; i++){
        if(strcmp(flight_records[i].flight_number, airline_code) == 0){
            loop = 1;
            do{
                printf("\tFor first class enter 1, for coach enter 2: ");
                scanf("%d", &user_input);
                switch(user_input){
                    case 1:
                        if(flight_records[i].fc_seats_sold > 0){
                            printf("\tFirst class seat cancelled!\n");
                            flight_records[i].fc_seats_sold--;
                            flight_records[i].fc_seats_available++;
                            reservation = 1;
                        }
                        else{
                            printf("\tNo first class seats reserved!\n");
                            reservation = 2;
                            loop = 1;
                        }
                        break;
                    case 2:
                        if(flight_records[i].c_seats_sold > 0){
                            printf("\tCoach seat cancelled!\n");
                            flight_records[i].c_seats_sold--;
                            flight_records[i].c_seats_available++;
                            reservation = 1;
                        }
                        else{
                            printf("\tNo coach seats reserved!\n");
                            reservation = 2;
                            loop = 1;
                        }
                        break;
                    default:
                        printf("\tInvalid selection. Please select a valid selection (1-2).\n");
                        break;
                }
                printf("\n\tWould you like to make another cancellation? 0: no, 1: yes:: ");
                scanf("%d", &loop);
            }while (loop != 0);
            return reservation;
        }
    }
    return 0;
}

int main(void){
    flight_information_t flight_records[MAX];
    int index, user_input, check, count, i;
    FILE *database;
    index = 0;
    database = fopen("flight_records.txt", "r");
    if(database != NULL){
        while (fread(&flight_records[index], sizeof(struct Flight_Information), 1, database)){
            index++;
        }
    }
    fclose(database);
    do
    {
        printf("\n1: create new flight record\n");
        printf("2: delete existing flight record\n");
        printf("3: update of existing flight record\n");
        printf("4: make a reservation\n");
        printf("5: cancel a reservation\n");
        printf("6: quit\n\n");
        printf("Enter the action to be completed: ");
        scanf("%d", &user_input);
        switch (user_input)
        {
            case 1:
                printf("\n\t---------------------------------------Create new flight record chosen!---------------------------------------\n");
                flight_records[index] = create();
                index++;
                printf("\n\tFlight record successfully created!\n");
                break;
            case 2:
                printf("\n\t-------------------------------------Delete existing flight record chosen!------------------------------------\n");
                check = deletion(flight_records, index);

                if(check == 1){
                    printf("\n\tFlight record successfully deleted!\n");
                    index--;
                }
                else{
                    printf("\n\tFlight record specified not found.\n");
                }
                break;
            case 3:
                printf("\n\t-----------------------------------Update of existing flight record chosen!-----------------------------------\n");
                check = update(flight_records, index);

                if(check == 1){
                    printf("\n\tFlight record successfully updated!\n");
                }
                else{
                    printf("\n\tFlight record specified not found. Flight record not updated.\n");
                }
                break;
            case 4:
                printf("\n\t------------------------------------------Make a reservation chosen!------------------------------------------\n");
                check = make_reservation(flight_records, index);

                if(check == 1){
                    printf("\n\tReservation successfully made!\n");
                }
                else if (check == 2){
                    printf("\n\tReservation not made.\n");
                }
                else{
                    printf("\n\tFlight record specified not found.\n");
                }
                break;
            case 5:
                printf("\n\t------------------------------------------Make a cancellation chosen!-----------------------------------------\n");
                check = cancel_reservation(flight_records, index);

                if(check == 1){
                    printf("\n\tSuccessfully cancelled reservation!\n");
                }
                else if (check == 2){
                    printf("\n\tCancellation not made.\n");
                }
                else{
                    printf("\n\tFlight record specified not found.\n");
                }
                break;
            case 6:
                printf("quit!\n\n");
                break;
            default:
                printf("Please enter a valid choice (1-5)\n");
                break;
        }
    }while (user_input != 6);

    database = fopen("flight_records.txt", "w");
    do{
        for(i = 0; i < index; i++){
            fwrite(&flight_records[i], sizeof(struct Flight_Information), 1, database);
        }
    } while (i < index);
    fclose(database);
    return 0;
}