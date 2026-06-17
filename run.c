#include "run.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "logik.h"
#include "variablen.h"
#include "editor.h"
#include "programm.h"
#include "console.h"

int current_line = 0;
int while_counter = 0;
int debugmode = 0;

static void leerzeichen_ueberspringen(char **s)
{
    while (**s == ' ') (*s)++;
}
void warte_auf_taste(void)
{
    int taste = getch();
    if (taste == 0 || taste == 0xE0)
    {
        getch(); // zweiten Wert wegwerfen
    }
}

int zeile_ausfuehren(char *text)
{
    char *s = text;

    if (strncmp(s, "LET", 3) == 0)
    {
        s += 3;
        leerzeichen_ueberspringen(&s);
        char variable = *s;
        if (variable < 'A' || variable > 'Z') return -3;
        s++;
        leerzeichen_ueberspringen(&s);
        if (*s != '=') return -3;
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
        if (*s == '\0') return -3; // nichts nach PRINT
        double wert = ausdruck_berechnen(&s);
        if (!debugmode) {print_in_console(wert);}
        return -1;
    }

    if (strncmp(s, "GOTO", 4) == 0)
    {
        s += 4;
        leerzeichen_ueberspringen(&s);
        if (*s == '\0') return -3; // keine Zeilennummer
        int nummer = atoi(s);
        if (nummer <= 0) return -3; // ungültige Zeilennummer
        return nummer - 1;
    }

    if (strncmp(s, "IF", 2) == 0)
    {
        s += 2;
        leerzeichen_ueberspringen(&s);
        if (*s != '(') return -3; // keine Klammer
        int ergebnis = bedingung_auswerten(&s);
        leerzeichen_ueberspringen(&s);
        if (*s == '\0') return -3; // kein Befehl nach IF
        if (ergebnis)
        {
            return zeile_ausfuehren(s);
        }
        if (strncmp(Programm[current_line + 1].text, "ELSE", 4) == 0)
        {
            char *else_s = Programm[current_line + 1].text + 4;
            leerzeichen_ueberspringen(&else_s);
            if (*else_s == '\0') return -3; // nichts nach ELSE
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
        int wert = input_in_console();
        num_variable_setzen(variable, wert);
        return -1;
    }

    if (strncmp(s, "WHILE", 5) == 0)
    {
        s += 5;
        leerzeichen_ueberspringen(&s);
        if (*s != '(') return -3; // keine Klammer
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
        if (tiefe != 0) return -3; // kein passendes ENDWHILE gefunden
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
        if (tiefe != 0) return -3; // kein passendes WHILE gefunden
        return current_line - i + 1;
    }

    if (strncmp(s, "END", 3) == 0)
    {
        return -2;
    }

    if (strncmp(s, "REM", 3) == 0)
    {
        return -1;
    }

    if (strncmp(s, "ELSE", 4) == 0)
    {
        return -1;
    }

    return -3; // unbekannter Befehl
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
int debug_programm_ausfuehren(void)
{
    debugmode = 1;
    int lastpos = 2;
    gotoxy(50, 0);
    setCursorType(C_INVISABLE);
    textcolor(MAGENTA);
    printf("OwnLanguage: DEBUG ");
    textcolor(WHITE);


    for (current_line = 0; current_line < 999; current_line++)
    {
        int output = zeile_ausfuehren(Programm[current_line].text);

        int variablen_printed = 0;
        gotoxy(58,lastpos-scroll_offset);
        textbackground(BLACK);
        changes = 1;
        clearall = 0;
        draw_editor(scroll_offset);
        gotoxy(58,current_line+2 - scroll_offset);
        textbackground(WHITE);
        changes = 1;
        clearall = 0;
        draw_editor(scroll_offset);
        textbackground(BLACK);
        textcolor(WHITE);
        lastpos = current_line+2-scroll_offset;


        for (int y = 0; y < 26; y++)
        {
            if (num_variable_gesetzt[y] == 1)
            {
                gotoxy(60,2+variablen_printed);
                char variable = 'A' + y;
                textcolor(YELLOW);
                printf("%c = %-3d", variable, num_variable[y]);
                textcolor(WHITE);
                variablen_printed++;
            }
        }


        if (output == -3)
        {
            gotoxy(5, 2+current_line);
            textbackground(RED);
            changes = 1;
            clearall = 0;
            draw_editor(scroll_offset);
            textbackground(BLACK);
            int taste = getch();
            if (taste == 0 || taste == 0xE0)
            {
                getch(); // zweiten Wert wegwerfen
            }
            changes = 4;
            clearall = 1;
            return -1;
        }
        else if (output == -2)
        {
            gotoxy(5, 2+current_line);
            textbackground(GREEN);
            changes = 1;
            clearall = 0;
            draw_editor(scroll_offset);
            textbackground(BLACK);
            int taste = getch();
            if (taste == 0 || taste == 0xE0)
            {
                getch(); // zweiten Wert wegwerfen
            }
            changes = 4;
            clearall = 1;
            return 0;
        }
        else if (output >= 0)
        {
            int taste = getch();
            if (taste == 0 || taste == 0xE0)
            {
                getch(); // zweiten Wert wegwerfen
            }
            current_line = output - 1;
        }
        else if (output == -1)
        {
            int taste = getch();
            if (taste == 0 || taste == 0xE0)
            {
                getch(); // zweiten Wert wegwerfen
            }

        }




    }

return -1;

}
