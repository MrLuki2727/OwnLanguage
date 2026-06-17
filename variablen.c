#include "variablen.h"


int num_variable[26];
int num_variable_gesetzt[26];

void num_variable_setzen(char var, int value)
{
    if (var < 'A' || var > 'Z') return;

    num_variable[var - 'A'] = value;
    num_variable_gesetzt[var - 'A'] = 1;
}

int num_variable_lesen(char var)
{
    if (var < 'A' || var > 'Z') return -1;

    return num_variable[var - 'A'];
}