#include "run.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "logik.h"
#include "variablen.h"
#include "editor.h"
#include "programm.h"

static void leerzeichen_ueberspringen(char **s)
{
    while (**s == ' ') (*s)++;
}


int zeile_ausfuehren(char *text)
{
    char *s = text;

    if (strncmp(s, "LET", 3) == 0)
    {
        s += 3;
        leerzeichen_ueberspringen(&s);
        char variable = *s;
        if (variable < 'A' || variable > 'Z') return -3; //FEHLER
        s++;
        leerzeichen_ueberspringen(&s);
        if (*s != '=') return -3; // FEHLER
        s++;
        leerzeichen_ueberspringen(&s);
        double wert = ausdruck_berechnen(&s);
        num_variable_setzen(variable, wert);
        return -1;
    }

    if (strncmp(s, "PRINT", 5) == 0)
    {
        s += 5;
        leerzeichen_ueberspringen(&s);

        double wert = ausdruck_berechnen(&s);
        print_in_console(wert);

        return -1;
    }

    if (strncmp(s, "GOTO", 4) == 0)
    {
        s+=4;
        leerzeichen_ueberspringen(&s);
        int nummer = atoi(s);
        return nummer - 1;
    }

    if (strncmp(s, "IF", 2) == 0)
    {
        s += 2;
        leerzeichen_ueberspringen(&s);

        int ergebnis = bedingung_auswerten(&s);

        leerzeichen_ueberspringen(&s);
        if (ergebnis)
        {
            return zeile_ausfuehren(s); // einfach den Rest rekursiv ausführen
        }
        return -1;
    }

    if (strncmp(s, "END", 3) == 0)
    {
        return -2;
    }

    if (strncmp(s, "INPUT", 5) == 0)
    {
        s += 5;
        leerzeichen_ueberspringen(&s);

        char variable = *s;
        if (variable < 'A' || variable > 'Z') return -3;

        int wert;
        wert = input_in_console();

        num_variable_setzen(variable, wert);
        return -1;
    }

    return -1; // unbekannter Befehl, ignorieren
}

int programm_ausfuehren(void)
{
    running_printed_lines = 0;
    draw_editor_run();
    for (int i = 0; i < 999; i++)
    {
        int output = zeile_ausfuehren(Programm[i].text);
        if (output >= 0)
        {
            i = output - 1;
        }
        else if (output == -2)
        {
            exit_code = 0;
            draw_editor_run();
            return 0;
        }
        else if (output == -3)
        {

            exit_code = -1;
            draw_editor_run();
            return -1;
        }

    }

    exit_code = -1;
    draw_editor_run();
    return -1;
}
