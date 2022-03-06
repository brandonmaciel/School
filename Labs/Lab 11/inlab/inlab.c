#include <stdio.h>
#include <string.h>

typedef struct {
    char first[10];
    char last[10];
}name_t;

typedef struct employee_report{
    name_t name;
    char social_security[11];
    double gross_pay;
    double taxes_deducted;
    double net_pay;
}report_t;



int main(void){
    FILE *empstat, *report;
    empstat = fopen("empstat.txt", "r");
    report = fopen("report.txt", "w");
    report_t report_s;    
    
    char line[1024];
    char ch = getc (empstat);
    int index = 0;
    fprintf(report, "        NAME          SOC.SEC.NUM      GROSS          TAXES          NET    \n");
    while (ch != EOF) {
        if (ch != '\n'){
            line[index++] = ch;
        }
        else{
            line[index] = '\0';
            index = 0;
            sscanf(line, "%s %s %s %lf %lf %lf", report_s.name.first, report_s.name.last, report_s.social_security, &report_s.gross_pay, &report_s.taxes_deducted, &report_s.net_pay);
            fprintf(report, "%10s %-10s %s      %-13.2lf  %-13.2lf  %.2lf\n\n\n", report_s.name.first, report_s.name.last, report_s. social_security, report_s.gross_pay, report_s.taxes_deducted, report_s.net_pay);
        }
        ch = getc (empstat);
    }
    
    fclose (empstat);
    return 0;
}