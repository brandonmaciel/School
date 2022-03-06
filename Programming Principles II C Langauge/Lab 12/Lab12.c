// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab12.c
// SPECIFICATION:  Engineering Systems
// FOR:            CS 1412 Programming Principles II Section 502
// --------------------------------------------------------------------------------

#include <stdio.h>

#define MAX_MAINTENANCE 20
#define MAX_CREW 10

typedef struct Crew_Data{
    int crew_number;
    int skill_level;
    int crew_cost; /* cost of crew per hour */
    int scheduled_hours; /* scheduled hours as program goes */
}crew_data_t;

typedef struct Maintenance_Data{
    int aircraft_ID;
    int maintenance_level;
    int hours;
    int start_hour; /* start of schedule */
    int end_hour; /* end of schedule */
    int crew_number; /* crew number performing maintenance */
}maintenance_data_t;

// NAME: scan_crew_data
// PARAMETERS: none
// OUTPUT: new crew_data struct
// PURPOSE: to scan crew data to a new struct
crew_data_t scan_crew_data(){
    crew_data_t crew;

    printf("\tEnter crew number: ");
    scanf("%d", &crew.crew_number);
    printf("\tEnter crew skill lever: ");
    scanf("%d", &crew.skill_level);
    printf("\tEnter crew cost per hour: ");
    scanf("%d", &crew.crew_cost);
    crew.scheduled_hours = 0;
    return crew;
}

// NAME: scan_maintenance_data
// PARAMETERS: none
// OUTPUT: new maintenance_data struct
// PURPOSE: to scan maintenance data to a new struct
maintenance_data_t scan_maintenance_data(){
    maintenance_data_t maintenance;

    printf("\tEnter aircraft ID: ");
    scanf("%d", &maintenance.aircraft_ID);
    printf("\tEnter maintenance level of aircraft: ");
    scanf("%d", &maintenance.maintenance_level);
    printf("\tEnter hours of maintenance for aircraft: ");
    scanf("%d", &maintenance.hours);
    return maintenance;
}

// NAME: lowest_cost
// PARAMETERS: *crew, all of the instances of crew_data_t; *maintenance, all of the instances of maintenance_data_t; crew_index, keep track of crew_data instances
// OUTPUT: crew number with the minimum requirement to perform maintanance
// PURPOSE: check maintenance level required against the crew abilities and return the number of the lowest-cost crew that can perform the maintenance.
int lowest_cost(crew_data_t *crew, maintenance_data_t *maintenance, int crew_index){
    int qualified_crew, i;
    for(i = 0; i < crew_index; i++){
        if(maintenance->maintenance_level == crew[i].skill_level){
            qualified_crew = crew[i].crew_number;
            break;
        }
        else{
            qualified_crew = -1;
        }
    }
    return qualified_crew;
}

// NAME: fastest_time
// PARAMETERS: *crew, all of the instances of crew_data_t; *maintenance, all of the instances of maintenance_data_t; crew_index, keep track of crew_data instances; maintenance_index, keep track of maintenance_data instances
// OUTPUT: crew number with the fastest scheduling to perform maintanance
// PURPOSE: check maintenance level required against the crew abilities and return the number of the lowest-cost crew that can perform the maintenance.
int fastest_time(crew_data_t *crew, maintenance_data_t *maintenance, int crew_index, int maintenance_index){
    int qualified_crew, i;
    for(i = 0; i < crew_index; i++){
        if(maintenance[maintenance_index].maintenance_level == crew[i].skill_level){
            qualified_crew = crew[i].crew_number;
            if(crew[maintenance[maintenance_index].crew_number].scheduled_hours == 0){
                maintenance[maintenance_index].start_hour = 0;
                maintenance[maintenance_index].end_hour = maintenance[maintenance_index].hours;
                crew[maintenance[maintenance_index].crew_number].scheduled_hours = maintenance[maintenance_index].hours;
            }
            else{
                maintenance[maintenance_index].start_hour = crew[maintenance[maintenance_index].crew_number].scheduled_hours;
                maintenance[maintenance_index].end_hour = maintenance[maintenance_index].start_hour + maintenance[maintenance_index].hours;
                crew[maintenance[maintenance_index].crew_number].scheduled_hours = maintenance[maintenance_index].end_hour;
            }
            break;
        }
        else{
            qualified_crew = -1;
        }
    }
    return qualified_crew;
}

// NAME: display_crew
// PARAMETERS: *crew, all of the instances of crew_data_t
// OUTPUT: none
// PURPOSE: display a crew struct
void display_crew(crew_data_t crew){
    printf("\t%d\t\t%d\t\t$%d\n", crew.crew_number, crew.skill_level, crew.crew_cost);
}

// NAME: display_maintenance
// PARAMETERS: *maintenance, all of the instances of maintenance_data_t
// OUTPUT: none
// PURPOSE: display a maintenance struct
void display_maintenance(maintenance_data_t maintenance){
    printf("\t%d\t\t%d\t\t\t%d\n", maintenance.aircraft_ID, maintenance.maintenance_level, maintenance.hours);
}

int main(void){
    crew_data_t crew[MAX_CREW];
    maintenance_data_t maintenance[MAX_MAINTENANCE];
    FILE *crew_database, *maintenance_database;
    int cheapest_schedule[MAX_MAINTENANCE];
    int crew_index = 0,
        maintenance_index = 0,
        user_input, i, lowest_cost_crew;

    crew_database = fopen("crew_database.txt", "r");
    if(crew_database != NULL){
        while (fread(&crew[crew_index], sizeof(struct Crew_Data), 1, crew_database)){
            crew_index++;
        }
    }
    fclose(crew_database);
    maintenance_database = fopen("maintenance_database.txt", "r");
    if(maintenance_database != NULL){
        while (fread(&maintenance[maintenance_index], sizeof(struct Maintenance_Data), 1, maintenance_database)){
            /* comment line 144 to use manual input of maintenance data */
            // maintenance_index++;
        }
    }
    fclose(maintenance_database);
    /* manually set inputs instead of using scan_maintenance_data, if used comment out maintenance++ (line 144) */
    if(1 == 1){
        maintenance[0].aircraft_ID = 7899;
        maintenance[0].maintenance_level = 1;
        maintenance[0].hours = 8;
        maintenance_index++;
        maintenance[1].aircraft_ID = 3119;
        maintenance[1].maintenance_level = 1;
        maintenance[1].hours = 6;
        maintenance_index++;
        maintenance[2].aircraft_ID = 7668;
        maintenance[2].maintenance_level = 1;
        maintenance[2].hours = 4;
        maintenance_index++;
        maintenance[3].aircraft_ID = 2324;
        maintenance[3].maintenance_level = 2;
        maintenance[3].hours = 4;
        maintenance_index++;
        maintenance[4].aircraft_ID = 1123;
        maintenance[4].maintenance_level = 2;
        maintenance[4].hours = 8;
        maintenance_index++;
        maintenance[5].aircraft_ID = 7555;
        maintenance[5].maintenance_level = 2;
        maintenance[5].hours = 4;
        maintenance_index++;
        maintenance[6].aircraft_ID = 6789;
        maintenance[6].maintenance_level = 3;
        maintenance[6].hours = 2;
        maintenance_index++;
        maintenance[7].aircraft_ID = 7888;
        maintenance[7].maintenance_level = 3;
        maintenance[7].hours = 10;
        maintenance_index++;
    }
    do
    {
        printf("1: Create crew data.\n");
        printf("2: Create maintenace data.\n");
        printf("3: Return lowest cost crew to perform maintenance.\n");
        printf("4: Return the fastest schedule.\n");
        printf("5: Display crew data.\n");
        printf("6: Display maintenance data.\n");
        printf("7: Quit.\n");
        printf("\nEnter the number for action to be performed: ");
        scanf("%d", &user_input);
        for(i = 0; i < crew_index; i++){
            crew[i].scheduled_hours = 0;
        }
        switch (user_input){
            case 1:
                printf("\n\t---------------Create Crew Data---------------\n");
                crew[crew_index] = scan_crew_data();
                crew_index++;
                printf("\n\tCrew data successfully created!\n");
                break;
            case 2:
                printf("\n\t------------Create Maintenace Data------------\n");
                maintenance[maintenance_index] = scan_maintenance_data();
                maintenance_index++;
                printf("\n\tMaintenance data successfully created!\n");
                break;
            case 3:
                printf("\n\t----Return Lowest Cost Crew for Maintenance----");
                printf("\n\tAircraft ID\tLevel of Maintenace\tHours\tCrew\n");
                for (i = 0; i < maintenance_index; i++)
                {
                    maintenance[i].crew_number = lowest_cost(crew, &maintenance[i], crew_index);
                    if (lowest_cost_crew == -1)
                    {
                        printf("\t%d\t\t%d\t\t\t%d\t\tn/a\n", maintenance[i].aircraft_ID, maintenance[i].maintenance_level, maintenance[i].hours);
                    }
                    else
                    {
                        printf("\t%d\t\t%d\t\t\t%d\t%d\n", maintenance[i].aircraft_ID, maintenance[i].maintenance_level, maintenance[i].hours, maintenance[i].crew_number);
                    }
                }
                break;
            case 4:
                printf("\n\t------Return Fastest Crew for Maintenance------");
                printf("\n\tAircraft ID\tLevel of Maintenace\tHours\tCrew\tStart\tEnd\n");
                for (i = 0; i < maintenance_index; i++)
                {
                    maintenance[i].start_hour = 0;
                    maintenance[i].end_hour = 0;
                    maintenance[i].crew_number = fastest_time(crew, maintenance, crew_index, i);
                    if (lowest_cost_crew == -1)
                    {
                        printf("\t%d\t\t%d\t\t\t%d\t\tn/a\n", maintenance[i].aircraft_ID, maintenance[i].maintenance_level, maintenance[i].hours);
                    }
                    else
                    {
                        printf("\t%d\t\t%d\t\t\t%d\t%d\t%d\t%d\n", maintenance[i].aircraft_ID, maintenance[i].maintenance_level, maintenance[i].hours, maintenance[i].crew_number, maintenance[i].start_hour, maintenance[i].end_hour);
                    }
                }
                break;
            case 5:
                if(crew_index != 0){
                    printf("\n\tCrew Number\tSkill Level\tCost of Crew Per Hour\n");
                    for (i = 0; i < crew_index; i++){
                        display_crew(crew[i]);
                    }
                }
                else{
                    printf("\n\tNo crew data available. Use option 1 to create crew data!\n");
                }
                break;
            case 6:
                if(maintenance_index != 0){
                    printf("\n\tAircraft ID\tLevel of Maintenace\tNumber of Hours\n");
                    for (i = 0; i < maintenance_index; i++){
                        display_maintenance(maintenance[i]);
                    }
                }
                else{
                    printf("\n\tNo maintenance data available. Use option 2 to create maintenance data!\n");
                }
                break;
            case 7:
                printf("quit!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    } while (user_input != 7);

    crew_database = fopen("crew_database.txt", "w");
    do{
        for(i = 0; i < crew_index; i++){
            fwrite(&crew[i], sizeof(struct Crew_Data), 1, crew_database);
        }
    } while (i < crew_index);
    fclose(crew_database);

    maintenance_database = fopen("maintenance_database.txt", "w");
    do{
        for(i = 0; i < maintenance_index; i++){
            fwrite(&maintenance[i], sizeof(struct Maintenance_Data), 1, maintenance_database);
        }
    } while (i < maintenance_index);
    fclose(maintenance_database);

    return 0;
}