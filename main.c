#include <windows.h>
#include "console.h"
#include "editor.h"
#include "programm.h"
#include "run.h"
#include <stdio.h>



int main(void)
{
    dateiname_laden();
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
        getxy(&x_cursor, &y_cursor);
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
            changes = 4;
        }
        else if (taste == 13) // Enter
        {
            zeile_einfuegen();
            y_cursor++;
            changes = 2;

        }
        else if (taste == 8) // Löschen
        {
            if (x_cursor > 7)
            {
                gotoxy(x_cursor - 1, y_cursor);
                zeichen_loeschen();
                x_cursor--;
                changes = 1;


            }
            else
            {
                zeile_loeschen();
                if (y_cursor >2)
                {
                   y_cursor--;
                }

                changes = 3;


            }
        }
        else if (sondertaste && taste == 72) // Pfeil hoch
        {
            if (scroll_offset > 0 && y_cursor == 2)
            {
                scroll_offset--;
                changes = 4;
            }
            else if (y_cursor > 2) y_cursor --;
        }
        else if (sondertaste && taste == 80) // Pfeil runter
        {
            if (y_cursor < 24) y_cursor++;
            else if (y_cursor == 24)
            {
                scroll_offset++;
                changes = 4;
            }
        }
        else if (sondertaste && taste == 75) // Pfeil links
        {
            if (x_cursor > 7) x_cursor--;
        }
        else if (sondertaste && taste == 77) // Pfeil rechts
        {
            x_cursor++;
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
            x_cursor++;
            changes = 1;

        }


        draw_editor(scroll_offset);
    }

    return 0;
}