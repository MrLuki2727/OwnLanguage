#ifndef OWNLANGUAGE_RUN_H
#define OWNLANGUAGE_RUN_H

int zeile_ausfuehren(char *text); // -1 weiter , -2 programmende, >=0 goto


int programm_ausfuehren(void);

int debug_programm_ausfuehren(void);
extern int debugmode;

#endif //OWNLANGUAGE_RUN_H
