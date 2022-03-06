// --------------------------------------------------------------------------------
// AUTHOR:         Brandon Maciel
// FILENAME:       Lab10.c
// SPECIFICATION:  health profile
// FOR:            CS 1412 Programming Principles II Section 502
// --------------------------------------------------------------------------------
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct {
    int month;
    int day;
    int year;
}Date_of_Birth;

typedef struct {
    char first_name[20];
    char last_name[20];
    char gender;
    Date_of_Birth DOB;
    double height_cm; /* height in centimeters */
    double weight_kg; /* weight in kilograms */
}HealthProfile;

void scan_health_profile(HealthProfile*);
void display_health_profile(HealthProfile);
int calculate_patient_age(HealthProfile );
void target_heart_rate(HealthProfile, int*, int*, int*);
double calculate_bmi(HealthProfile);

int main(void){
    HealthProfile user;
    int max_hr, min_target_hr, max_target_hr;
    /* test case */
    sscanf("Brandon Maciel M 04 27 2001 188 88", "%s%s %c%d%d%d%lf%lf", user.first_name, user.last_name, &user.gender, &user.DOB.month, &user.DOB.day, &user.DOB.year, &user.height_cm, &user.weight_kg);
    // scan_health_profile(&user);
    
    display_health_profile(user);
    target_heart_rate(user, &max_hr, &min_target_hr, &max_target_hr);
    printf("age: %d years\n", calculate_patient_age(user));
    printf("Body mass index: %.1lf\n", calculate_bmi(user));
    printf("Maximum heart rate (100%%): %d bpm\n", max_hr);
    printf("Target heart rate zone (50-85%%): %d - %d bpm\n", min_target_hr, max_target_hr);
    printf("\n------------BMI VALUES------------\n");
    printf("Underweight: less than 18.5\n");
    printf("Normal:      between 18.5 and 24.9\n");
    printf("Overweight:  between 25 and 29.9\n");
    printf("Obese:       30 or greater\n\n");
    return 0;
}

void scan_health_profile(HealthProfile *patient_profile){
    printf("Enter first and last name: ");
    scanf("%s%s", patient_profile->first_name, patient_profile->last_name);
    printf("Enter gender(M or F): ");
    scanf(" %c", &patient_profile->gender);
    printf("Enter date of brith(format: mm dd yyyy): ");
    scanf("%d%d%d", &patient_profile->DOB.month, &patient_profile->DOB.day, &patient_profile->DOB.year);
    printf("Enter height(in cm) and weight(in kg): ");
    scanf("%lf%lf", &patient_profile->height_cm, &patient_profile->weight_kg);
}

void display_health_profile(HealthProfile patient_profile){
    printf("\n-----------------Patient Profile-----------------\n");
    printf("Name: %s %s\n", patient_profile.first_name, patient_profile.last_name);
    printf("Gender(M or F): %c\n", patient_profile.gender);
    printf("Date of Birth: %d/%d/%d\n", patient_profile.DOB.month, patient_profile.DOB.day, patient_profile.DOB.year);
    printf("Height(in cm): %5.1lf cm   Weight(in kg): %5.1lf kg\n", patient_profile.height_cm, patient_profile.weight_kg);
    printf("-------------------------------------------------\n");
}

int calculate_patient_age(HealthProfile patient_profile){
    int age;
    /* gets system time */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if(((tm.tm_mon + 1) > patient_profile.DOB.month) 
        || ((patient_profile.DOB.month == (tm.tm_mon + 1)) && (tm.tm_mday > patient_profile.DOB.day))
        || ((patient_profile.DOB.month == (tm.tm_mon + 1)) && (tm.tm_mday == patient_profile.DOB.day))){
        printf("pass\n");
        age = (tm.tm_year + 1900) - patient_profile.DOB.year;
    }
    else{
        age = (tm.tm_year + 1900) - patient_profile.DOB.year - 1;
    }
    return age;
}

void target_heart_rate(HealthProfile patient_profile, int *max_heart_rate, int *min_target_heart_rate, int *max_target_heart_rate){
    int age;
    age = calculate_patient_age(patient_profile);
    *max_heart_rate = 220 - age;

    *min_target_heart_rate = round(*max_heart_rate * 0.5);
    *max_target_heart_rate = round(*max_heart_rate * 0.85);
}

double calculate_bmi(HealthProfile patient_profile){
    double bmi, height;
    height = patient_profile.height_cm / 100;
    bmi = patient_profile.weight_kg / (height * height);
    return bmi;
}