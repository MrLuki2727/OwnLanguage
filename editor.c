#include "editor.h"
#include "console.h"
#include <stdio.h>
#include "programm.h"

int scroll_offset = 0;
int running_printed_lines = 0;
int previous_scroll_offset = 0;
int exit_code = 1;

void draw_editor(int offset) // 0 = keine changes 1 = Neues Zeichen 2 = Neue Zeile 3 = Zeile löschen 4 = redraw all
{
    setCursorType(C_INVISABLE);
    if (changes == 4)
    {
        draw_editor_ambient(offset);
        draw_editor_code(offset);
    }
    else
    {
        draw_editor_code(offset);
    }
}

void draw_editor_ambient(int offset)
{
    setCursorType(C_INVISABLE);
    gotoxy(50, 0);
    printf("OwnLanguage: CODING");
    gotoxy(0, 1);
    printf("─────┬──────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    gotoxy(0, 24);
    printf("\n─────┴──────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    if (exit_code == 0)
    {
        printf("RUN SUCESSFUL");
    }
    else if (exit_code == -1)
    {
        printf("RUN FAULT");
    }
}

void draw_editor_code(int offset)
{
    setCursorType(C_INVISABLE);

    if (changes == 4)
    {
        // alles neu zeichnen
        for (int i = 0; i < 23; i++)
        {
            gotoxy(0, i + 2);
            draw_code_with_synax(i + 1 + offset);
        }

    }
    else if (changes == 1)
    {
       int y_cursor;
        int x_cursor;
        getxy(&x_cursor, &y_cursor);
        gotoxy(0, y_cursor);
        int nummer = y_cursor - 2 + 1 + offset; // Bildschirmzeile → Programm-Index
        draw_code_with_synax(nummer);
    }
    else if (changes == 2 || changes == 3)
    {
        int y_cursor;
        int x_cursor;
        getxy(&x_cursor, &y_cursor);
        // aktuelle Zeile und alles darunter neu zeichnen
        for (int i = y_cursor; i <= 24; i++)
        {
            gotoxy(0, i);
            int nummer = i - 2 + 1 + offset;
            draw_code_with_synax(nummer);
        }
    }
    changes = 0;
}

void draw_code_with_synax(int number)
{
    printf(" %3d │ %-110s", number, Programm[number-1].text);
}

void draw_editor_run()
{

    setCursorType(C_INVISABLE);
    gotoxy(50, 0);
    printf("OwnLanguage: RUNNING");
    gotoxy(0, 1);
    printf("────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    gotoxy(0, 24);
    printf("\n────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    if (exit_code == 0)
    {
        printf("RUN SUCESSFUL");
    }
    else if (exit_code == -1)
    {
        printf("RUN FAULT   ");
    }
}

void draw_editor_menu()
{
    setCursorType(C_INVISABLE);
    gotoxy(50, 10);
    printf("──────────MENÜ──────────\n");
    gotoxy(55, 11);
    printf("─────SAVE─────\n");
    gotoxy(55, 12);
    printf("─────EDIT─────\n");
    gotoxy(55, 13);
    printf("─────EXIT─────\n");
    gotoxy(50, 14);
    printf("────────────────────────\n");

    int pos = 0;
    while (1)
    {
        gotoxy(53,11+pos);
        printf("[]");
        gotoxy(69,11+pos);
        printf("[]");
        if (pos == 0)
        {
            gotoxy(53,12);
            printf("  ");
            gotoxy(69,12);
            printf("  ");
        }
        else if (pos == 1)
        {
            gotoxy(53,11);
            printf("  ");
            gotoxy(69,11);
            printf("  ");
            gotoxy(53,13);
            printf("  ");
            gotoxy(69,13);
            printf("  ");
        }
        else if (pos == 2)
        {
            gotoxy(53,12);
            printf("  ");
            gotoxy(69,12);
            printf("  ");
        }
        int taste = getch();

        if (taste == 72)//Hoch
        {
            if (pos > 0) pos --;

        }
        else if (taste == 80)//Runter
        {
            if (pos < 2) pos ++;
        }
        else if (taste == 27)
        {
            changes = 4;
            return;
        }
        else if (taste == 13)
        {
            switch (pos)
            {
                case 0:
                    programm_speichern(FILENAME);
                    break;
                case 1:
                change_filename();
                    break;
                case 2:
                    exit(0);
                    break;
                default:
            }
        }
    }
}

void print_in_console(int n)
{
    setCursorType(C_INVISABLE);
    gotoxy(0, 2 + running_printed_lines);
    printf("<PRINT> %d", n);
    running_printed_lines ++;
}
int input_in_console()
{
    int n;
    setCursorType(C_SMALL);
    gotoxy(0, 2 + running_printed_lines);
    printf("<INPUT> ");
    scanf("%d", &n);
    running_printed_lines ++;
    return n;
}
void change_filename()
{
    setCursorType(C_INVISABLE);
    gotoxy(50, 10);
    printf("────CHANGE FILENAME─────\n");
    gotoxy(50, 11);
    printf("                        \n");
    gotoxy(50, 12);
    printf("                        \n");
    gotoxy(50, 13);
    printf("                        \n");
    gotoxy(50, 14);
    printf("────────────────────────\n");
    gotoxy(55, 12);
    printf("ENTER:");
    setCursorType(C_SMALL);
    char filename[100];
    scanf("%s", filename);

    if (strstr(filename,".lu") == NULL) {change_filename();}
    setCursorType(C_INVISABLE);
    strcpy(FILENAME, filename);
    gotoxy(50, 10);
    printf("──────────MENÜ──────────\n");
    gotoxy(50, 11);
    printf("     ─────SAVE─────     \n");
    gotoxy(50, 12);
    printf("     ─────EDIT─────     \n");
    gotoxy(50, 13);
    printf("     ─────EXIT─────     \n");
    gotoxy(50, 14);
    printf("────────────────────────\n");
}
