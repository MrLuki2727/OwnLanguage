#include "programm.h"
#include <string.h>
#include <stdio.h>
#include "console.h"


Zeile Programm[1000];
extern int scroll_offset;
int changes = 4; // 0 = keine changes 1 = Neues Zeichen 2 = Neue Zeile 3 = Zeile löschen 4 = redraw all

char FILENAME[128];

void programm_laden(char *dateiname)
{
    int i = 0;

    FILE *fp = fopen(dateiname, "r");
    if (fp == NULL) return;

    while (fgets(Programm[i].text, sizeof(Programm[i].text), fp) != NULL)
    {

        Programm[i].text[strcspn(Programm[i].text, "\n")] = '\0';
        i++;
    }


    fclose(fp);
}


void programm_speichern(char* dateiname)
{
    dateiname_speichern();

    FILE* fp = fopen(dateiname, "w");
    if (fp == NULL) return;

    for (int i = 0; i < 1000; i++)
    {
        fprintf(fp, "%s\n", Programm[i].text);
    }

    fclose(fp);
}


#include "console.h"
#include <string.h>

extern int scroll_offset;

void zeichen_einfuegen(char c)
{
    int x, y;
    getxy(&x, &y);

    int spalte = x - 7; // KORREKTUR: Muss 7 sein, nicht 5!
    int zeile  = y - 2 + scroll_offset;

    char *text = Programm[zeile].text;
    int laenge = strlen(text);

    if (laenge >= 127) return;

    for (int i = laenge; i >= spalte; i--)
    {
        text[i + 1] = text[i];
    }

    text[spalte] = c;
    gotoxy(x + 1, y);
}

void zeichen_loeschen(void)
{
    int x, y;
    getxy(&x, &y);

    int spalte = x - 7;
    int zeile  = y - 2 + scroll_offset;

    char *text = Programm[zeile].text;
    int laenge = strlen(text);

    if (spalte >= laenge) return;

    for (int i = spalte; i < laenge; i++)
    {
        text[i] = text[i + 1];
    }

    gotoxy(x, y);
}

void zeile_einfuegen(void)
{
    int x, y;
    getxy(&x, &y);

    int zeile = y - 2 + scroll_offset;

    for (int i = 999; i > zeile; i--)
    {
        Programm[i] = Programm[i - 1];
    }

    Programm[zeile].text[0] = '\0';

    gotoxy(7, y);
}

void zeile_loeschen(void)
{
    int x, y;
    getxy(&x, &y);

    int zeile = y - 2 + scroll_offset;

    for (int i = zeile; i < 999; i++)
    {
        Programm[i] = Programm[i + 1];
    }

    Programm[999].text[0] = '\0';

    gotoxy(7, y);
}

void init_Programm()
{
    for (int i = 0; i < 1000; i++)
    {
        Programm[i].text[0] = '\0';
    }
}
void dateiname_laden()
{
    FILE *fp = fopen("config.txt", "r");
    if (fp == NULL) return;

    fgets(FILENAME, 128, fp);


    FILENAME[strcspn(FILENAME, "\n")] = '\0';

    fclose(fp);
}

void dateiname_speichern()
{
    FILE *fp = fopen("config.txt", "w");
    if (fp == NULL) return;

    fprintf(fp, "%s", FILENAME); // %s verwenden, nicht direkt FILENAME

    fclose(fp);
}
