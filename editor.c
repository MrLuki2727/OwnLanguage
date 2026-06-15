#include "editor.h"
#include "console.h"
#include <stdio.h>
#include "programm.h"

int scroll_offset = 0;
int running_printed_lines = 0;
int previous_scroll_offset = 0;
bool redraw_all = true;
int exit_code = 1;

void draw_editor(int offset)
{
    setCursorType(C_INVISABLE);
    if (redraw_all == true)
    {
        clrscr();
        draw_editor_ambient(offset);
        draw_editor_code(offset);
        redraw_all = false;
    }
    else if (scroll_offset != previous_scroll_offset)
    {
        draw_editor_ambient(offset);
        draw_editor_code(offset);
    }
    else if (changes == true)
    {
        draw_editor_code(offset);
        changes = false;
    }
}

void draw_editor_ambient(int offset)
{
    setCursorType(C_INVISABLE);
    gotoxy(50, 0);
    printf("OwnLanguage: CODING");
    gotoxy(0, 1);
    printf("─────┬──────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    for (int i = 0; i < 23; i++)
    {
        printf(" %3d │\n", i + offset + 1);
    }
    gotoxy(0, 29);
    printf("─────┴──────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
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
    for (int i = 0; i < 23; i++)
    {
        gotoxy(7, 2 + i);
        printf("%-110s", Programm[i + offset].text);
    }
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
            redraw_all = true;
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
