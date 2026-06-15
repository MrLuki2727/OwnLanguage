#include "run.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "logik.h"
#include "variablen.h"
#include "editor.h"
#include "programm.h"
int current_line = 0;
int while_counter = 0;

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
            return zeile_ausfuehren(s);
        }
        if (strncmp(Programm[current_line + 1].text, "ELSE", 4) == 0)
        {
            char *else_s = Programm[current_line + 1].text + 4;
            leerzeichen_ueberspringen(&else_s);
            zeile_ausfuehren(else_s);
            return current_line + 2;
        }
        return -1;
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
    if (strncmp(s, "WHILE", 5) == 0)
    {
        s += 5;
        leerzeichen_ueberspringen(&s);
        int ergebnis = bedingung_auswerten(&s);

        if (ergebnis) return -1;


        int tiefe = 1;
        int i = 1;
        while (tiefe > 0 && current_line + i < 999)
        {
            if (strncmp(Programm[current_line + i].text, "WHILE", 5) == 0) tiefe++;
            if (strncmp(Programm[current_line + i].text, "ENDWHILE", 8) == 0) tiefe--;
            i++;
        }
        return current_line + i;
    }
    if (strncmp(s, "ENDWHILE", 8) == 0)
    {

        int tiefe = 1;
        int i = 1;
        while (tiefe > 0 && current_line - i >= 0)
        {
            if (strncmp(Programm[current_line - i].text, "ENDWHILE", 8) == 0) tiefe++;
            if (strncmp(Programm[current_line - i].text, "WHILE", 5) == 0) tiefe--;
            i++;
        }
        return current_line - i + 1;
    }
    if (strncmp(s, "END", 3) == 0)
        {
            return -2;
        }
    return -1;
}

int programm_ausfuehren(void)
{
    running_printed_lines = 0;
    draw_editor_run();

    for (current_line = 0; current_line < 999; current_line++)
    {
        if (Programm[current_line].text[0] == '\0') break;

        int output = zeile_ausfuehren(Programm[current_line].text);

        if (output >= 0)
        {
            current_line = output - 1;
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
