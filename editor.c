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
        //printf("%s\n", Programm[i + offset].text);
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
