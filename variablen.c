#include "variablen.h"


double num_variable[26];

void num_variable_setzen(char var, double value)
{
    if (var < 'A' || var > 'Z') return;

    num_variable[var - 'A'] = value;
}

double num_variable_lesen(char var)
{
    if (var < 'A' || var > 'Z') return -1;

    return num_variable[var - 'A'];
}