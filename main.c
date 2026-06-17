#include <windows.h>
#include "console.h"
#include "editor.h"
#include "programm.h"
#include "run.h"
#include <stdio.h>

int x_cursor = 7;
int y_cursor = 2;

void cursor_bewegen(int neue_zeile, int neue_spalte)
{
    int index = neue_zeile - 2 + scroll_offset;

    if (index < 0 || index >= 999) return;

    int laenge = strlen(Programm[index].text);

    int max_x = 7 + laenge;

    if (neue_spalte > max_x) {
        neue_spalte = max_x;
    }
    if (neue_spalte < 7) {
        neue_spalte = 7;
    }

    x_cursor = neue_spalte;
    y_cursor = neue_zeile;
}



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

        else if (sondertaste && taste == 72) // hoch
        {

            if (y_cursor == 2)
            {
                if (scroll_offset > 0)
                {
                    scroll_offset--;
                    changes = 4; // Redraw triggern

                    cursor_bewegen(y_cursor, x_cursor);
                }
            }
            else if (y_cursor > 2)
            {
                // Normales Bewegen nach oben, solange wir nicht am Rand sind
                cursor_bewegen(y_cursor - 1, x_cursor);
            }
        }


        else if (sondertaste && taste == 80)// RUNTER
        {

            if (y_cursor == 24)
            {
                int naechster_index = 22 + scroll_offset;

                if (naechster_index < 999)
                {
                    scroll_offset++;
                    changes = 4;

                    cursor_bewegen(y_cursor, x_cursor);
                }
            }
            else if (y_cursor < 24)
            {
                cursor_bewegen(y_cursor + 1, x_cursor);
            }
        }
        else if (sondertaste && taste == 75) // links
        {
            if (x_cursor > 7)
            {
             x_cursor --;
            }

        }
        else if (sondertaste && taste == 77) // rechts
        {
            int index = y_cursor - 2 + scroll_offset;

            if (index < 0 || index >= 999) break;

            int max_x = 7 + strlen(Programm[index].text);

            if (x_cursor < max_x)
            {
                x_cursor++;

            }
        }
        else if (taste == 9) // Tab -> ausführen
        {
            clrscr();
            programm_ausfuehren();
            getch();
            changes = 4;
        }
        else if (sondertaste && taste == 59)
        {
            debug_programm_ausfuehren();
            gotoxy(x_cursor, y_cursor);
            debugmode = 0;
            changes = 4;
            clearall = 1;
            draw_editor(scroll_offset);
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