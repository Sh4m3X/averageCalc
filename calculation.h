#ifndef CALCULATION_H
#define CALCULATION_H
#include "list.h"

double weighted_average(const int *votes, const int *credits, int n);
double arithmetic_average(const int *votes, const int *credits, int n);
double institute_average(const int *votes, const int *credits, int n);

#endif

#define MAX_VOTE 30