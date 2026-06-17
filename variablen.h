#ifndef OWNLANGUAGE_VARIABLEN_H
#define OWNLANGUAGE_VARIABLEN_H

extern int num_variable[26];
extern int num_variable_gesetzt[26];

void num_variable_setzen(char var, int value);

int num_variable_lesen(char var);

#endif //OWNLANGUAGE_VARIABLEN_H
