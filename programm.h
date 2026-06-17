#ifndef OWNLANGUAGE_PROGRAMM_H
#define OWNLANGUAGE_PROGRAMM_H

typedef struct {
    char text[128];         // code in der Zeile
} Zeile;

extern Zeile Programm[1000]; // 1000 Zeilen max
extern int changes;
extern char FILENAME[128];

void programm_laden(char* dateiname);// Lädt das file und teilt in zeilennummer und code auf

void programm_speichern(char* dateiname);

void zeile_loeschen();

void zeile_einfuegen();

void zeichen_einfuegen(char c);

void zeichen_loeschen();

void init_Programm(void);

void dateiname_laden();

void dateiname_speichern();



#endif //OWNLANGUAGE_PROGRAMM_H
