#include <windows.h>
#include "console.h"
#include "editor.h"
#include "programm.h"
#include "run.h"
#include <stdio.h>

#define FILENAME_dev "Code.lu"

int main(void)
{
    strcpy(FILENAME, FILENAME_dev);
    initConsole();
    setCursorType(C_SMALL);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    init_Programm();
    programm_laden(FILENAME);
    draw_editor(scroll_offset);




    int x_cursor = 7;
    int y_cursor = 2;
    while (1)
    {
        gotoxy(x_cursor, y_cursor);
        setCursorType(C_SMALL);
        int taste = getch();
        int sondertaste = 0;

        if (taste == 0 || taste == 0xE0)
        {
            taste = getch();
            sondertaste = 1;
        }

        if (taste == 27) // ESC
        {
            draw_editor_menu();
        }
        else if (taste == 13) // Enter
        {
            zeile_einfuegen();
            changes = 2;

        }
        else if (taste == 8) // Löschen
        {
            if (x_cursor > 7)
            {
                gotoxy(x_cursor - 1, y_cursor);
                zeichen_loeschen();
                changes = 1;

            }
            else
            {
                zeile_loeschen();
                changes = 3;


            }
        }
        else if (sondertaste && taste == 72) // Pfeil hoch
        {
            if (y_cursor > 2) gotoxy(x_cursor, y_cursor - 1);
        }
        else if (sondertaste && taste == 80) // Pfeil runter
        {
            if (y_cursor < 24) gotoxy(x_cursor, y_cursor + 1);
        }
        else if (sondertaste && taste == 75) // Pfeil links
        {
            if (x_cursor > 7) gotoxy(x_cursor - 1, y_cursor);
        }
        else if (sondertaste && taste == 77) // Pfeil rechts
        {
            gotoxy(x_cursor + 1, y_cursor);
        }
        else if (taste == 9) // Tab -> ausführen
        {
            clrscr();
            programm_ausfuehren();
            getch();
            changes = 4;
        }
        else if (!sondertaste)
        {
            zeichen_einfuegen((char)taste);
            changes = 1;

        }

        getxy(&x_cursor, &y_cursor);
        draw_editor(scroll_offset);
    }

    return 0;
}