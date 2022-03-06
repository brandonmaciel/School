#include <stdio.h>
#include <math.h>

int monthly_payment(double p, double i, double y){
    int payment;
    payment = (i * p) / (1 - pow((i + 1), (-12 * y)));
    payment = ceil(payment);
    return payment;
}

double max_principal(double m, double i, double y){
    double principal;
    principal = m * i * (1 - pow((i + 1), (-12 * y)));
    return principal;
}

double max_interest_rate(double m, double p, double y){
    double rate;
    rate = ((m * 12 * y) - p) / (p);
    return rate;
}