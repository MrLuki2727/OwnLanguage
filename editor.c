#include "editor.h"
#include "console.h"
#include <stdio.h>
#include "programm.h"


#define FARBE_KEYWORD 4
#define FARBE_VARIABLE 2
#define FARBE_ZAHL 14
#define FARBE_OPERATOR 1
#define FARBE_KLAMMER 6
#define FARBE_RESET 15

int scroll_offset = 0;
int running_printed_lines = 0;
int previous_scroll_offset = 0;
int exit_code = 1;
int clearall = 0;


static void leerzeichen_ueberspringen(char **s)
{
    while (**s == ' ') (*s)++;
}






void draw_editor(int offset) // 0 = keine changes 1 = Neues Zeichen 2 = Neue Zeile 3 = Zeile löschen 4 = redraw all
{
    setCursorType(C_INVISABLE);
    if (changes == 4)
    {
        draw_editor_code(offset);
        draw_editor_ambient(offset);

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
    textcolor(GREEN);
    printf("OwnLanguage: CODING ");
    textcolor(WHITE);
    gotoxy(0, 1);
    printf("─────┬──────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    gotoxy(0, 24);
    printf("\n─────┴──────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    if (exit_code == 0)
    {
        textcolor(GREEN);
        printf("RUN SUCESSFUL");
        textcolor(WHITE);
    }
    else if (exit_code == -1)
    {
        textcolor(RED);
        printf("RUN FAULT");
        textcolor(WHITE);
    }
}

void draw_editor_code(int offset)
{
    setCursorType(C_INVISABLE);

    if (changes == 4)
    {

        for (int i = 0; i < 23; i++)
        {
            gotoxy(0, i + 2);
            draw_code_with_synax(i + 1 + offset);

        }
    clearall = 0;
    }
    else if (changes == 1)
    {
        int y_cursor;
        int x_cursor;
        getxy(&x_cursor, &y_cursor);
        gotoxy(0, y_cursor);
        int nummer = y_cursor - 2 + 1 + offset;
        draw_code_with_synax(nummer);
        gotoxy(x_cursor, y_cursor); // Cursor zurück auf ursprüngliche Position
        clearall = 0;
    }
    else if (changes == 2 || changes == 3)
    {
        int y_cursor;
        int x_cursor;
        getxy(&x_cursor, &y_cursor);

        for (int i = y_cursor; i <= 24; i++)
        {
            gotoxy(0, i);
            int nummer = i - 2 + 1 + offset;
            draw_code_with_synax(nummer);
        }
        gotoxy(x_cursor, y_cursor); // Cursor zurück
        clearall = 0;
    }
    changes = 0;
}

void draw_code_with_synax(int number)
{
    textcolor(H_BLUE);
    printf(" %3d", number);
    textcolor(WHITE);
    printf(" │ ");

    char *s = Programm[number - 1].text;
    while (*s != '\0')
    {

        if (*s == ' ')
        {
            putchar(' ');
            s++;
        }
        else if (*s == '(' || *s == ')')
        {
            textcolor(FARBE_KLAMMER);
            printf("%c", *s);
            textcolor(FARBE_RESET);
            s++;
        }
        else if (*s == '+' || *s == '-' || *s == '*' || *s == '/' || *s == '=' || *s == '>' || *s == '<' || *s == '!')
        {
            textcolor(FARBE_OPERATOR);
            printf("%c", *s);
            textcolor(FARBE_RESET);
            s++;
        }
        else if (isdigit((unsigned char) *s))
        {
            textcolor(FARBE_ZAHL);
            putchar(*s);
            textcolor(FARBE_RESET);
            s++;
        }
        else if (isalpha((unsigned char) *s))
        {
            const char *keywords[] = {"LET", "PRINT", "GOTO", "IF", "ELSE", "WHILE", "ENDWHILE", "INPUT", "END","REM", NULL};
            int gefunden = 0;

            for (int i = 0; keywords[i] != NULL; i++)
            {
                int len = strlen(keywords[i]);
                if (strncmp(s, keywords[i], len) == 0 && !isalpha((unsigned char)s[len]))
                {
                    textcolor(FARBE_KEYWORD);
                    for (int j = 0; j < len; j++) putchar(s[j]);
                    textcolor(FARBE_RESET);
                    s += len;
                    gefunden = 1;
                    break;
                }
            }

            if (!gefunden && *s >= 'A' && *s <= 'Z')
            {


                    textcolor(FARBE_VARIABLE);
                    putchar(*s);
                    textcolor(FARBE_RESET);
                    s++;

            }
            else
            {
                textcolor(FARBE_RESET);
                putchar(*s); // alles andere einfach ausgeben
                s++;
            }
        }
        else
        {
            textcolor(FARBE_RESET);
            putchar(*s); // alles andere einfach ausgeben
            s++;
        }
    }

    // Rest der Zeile mit Leerzeichen auffüllen (damit alte Zeichen überschrieben werden)
    textcolor(FARBE_RESET);
    if (clearall == 1)
    {
        printf("%-*s", 120 - (int)(s - Programm[number-1].text), "");

    }
    else
    {
        int restbreite = 30 - (int)(s - Programm[number-1].text);
        if (restbreite > 0) printf("%-*s", restbreite, " ");
    }

}






void draw_editor_run()
{

    setCursorType(C_INVISABLE);
    gotoxy(50, 0);
    textcolor(GREEN);
    printf("OwnLanguage: RUNNING ");
    textcolor(WHITE);
    gotoxy(0, 1);
    printf("────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    gotoxy(0, 24);
    printf("\n────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    if (exit_code == 0)
    {
        textcolor(GREEN);
        printf("RUN SUCESSFUL");
        textcolor(WHITE);
    }
    else if (exit_code == -1)
    {
        textcolor(RED);
        printf("RUN FAULT   ");
        textcolor(WHITE);
    }
}

void draw_editor_menu()
{
    setCursorType(C_INVISABLE);
    gotoxy(50, 10);
    textcolor(BLUE);
    printf("──────────MENÜ──────────\n");
    textcolor(WHITE);
    gotoxy(50, 11);
    printf("     ─────SAVE─────     \n");
    gotoxy(50, 12);
    printf("     ─────EDIT─────     \n");
    gotoxy(50, 13);
    printf("     ─────EXIT─────     \n");
    gotoxy(50, 14);
    textcolor(BLUE);
    printf("────────────────────────\n");
    textcolor(WHITE);

    int pos = 0;
    while (1)
    {
        textcolor(GREEN);
        gotoxy(53,11+pos);
        printf("●");
        gotoxy(69,11+pos);
        printf(" ●");
        textcolor(WHITE);
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
            clearall = 1;
            return;
        }
        else if (taste == 13)
        {
            switch (pos)
            {
                case 0:
                    programm_speichern(FILENAME);
                    textcolor(BLUE);
                    gotoxy(50, 10);
                    printf("──────────MENÜ──────────\n");
                    textcolor(WHITE);
                    gotoxy(50, 11);
                    printf("                        \n");
                    gotoxy(50, 12);
                    textcolor(GREEN);
                    printf("✅ SUCESSFULLY SAVED ✅\n");
                    textcolor(WHITE);
                    gotoxy(50, 13);
                    printf("                        \n");
                    gotoxy(50, 14);
                    textcolor(BLUE);
                    printf("────────────────────────\n");
                    getch();
                    changes = 4;
                    draw_editor_menu();
                    return;
                case 1:
                change_filename();
                textcolor(BLUE);
                gotoxy(50, 10);
                printf("──────────MENÜ──────────\n");
                textcolor(WHITE);
                gotoxy(50, 11);
                printf("                        \n");
                gotoxy(50, 12);
                textcolor(GREEN);
                printf("✅ SUCESSFULLY RENAMED ✅\n");
                textcolor(WHITE);
                gotoxy(50, 13);
                printf("                        \n");
                gotoxy(50, 14);
                textcolor(BLUE);
                printf("────────────────────────\n");
                getch();
                changes = 4;
                draw_editor_menu();
                return;

                case 2:
                textcolor(BLUE);
                gotoxy(50, 10);
                printf("──────SAVE & QUIT?──────\n");
                textcolor(WHITE);
                gotoxy(50, 11);
                printf("          QUIT          \n");
                gotoxy(50, 12);
                printf("                        \n");
                gotoxy(50, 13);
                printf("         RETURN         \n");
                gotoxy(50, 14);
                textcolor(BLUE);
                printf("────────────────────────\n");
                int choice = 0;
                while (1)
                {
                    if (choice == 0 )
                    {
                        textcolor(GREEN);
                        gotoxy(58, 11);
                        printf("●");
                        gotoxy(65, 11);
                        printf("●");
                        textcolor(WHITE);
                        gotoxy(57, 13);
                        printf(" ");
                        gotoxy(66, 13);
                        printf(" ");
                    }
                    else if (choice == 1)
                    {
                        textcolor(GREEN);
                        gotoxy(57, 13);
                        printf("●");
                        gotoxy(66, 13);
                        printf("●");
                        textcolor(WHITE);
                        gotoxy(58, 11);
                        printf(" ");
                        gotoxy(65, 11);
                        printf(" ");
                    }
                    int input = getch();

                    if (input == 72 && choice != 0)
                    {
                        choice --;
                    }
                    else if (input == 80 && choice != 1)
                    {
                        choice ++;
                    }
                    if (input == 13)
                        if (choice == 0)
                        {
                            programm_speichern(FILENAME);
                            exit(0);
                        }
                        else if (choice == 1)
                        {
                            draw_editor_menu();
                            changes = 4;
                            clearall = 1;
                            return;
                        }
                }

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
    textcolor(BLUE);
    printf("────CHANGE FILENAME─────\n");
    textcolor(WHITE);
    gotoxy(50, 11);
    printf("                        \n");
    gotoxy(50, 12);
    printf("                        \n");
    gotoxy(50, 13);
    printf("                        \n");
    gotoxy(50, 14);
    textcolor(BLUE);
    printf("────────────────────────\n");
    textcolor(WHITE);
    gotoxy(50, 12);
    printf("ENTER:");
    setCursorType(C_SMALL);
    char filename[100];
    scanf("%s", filename);

    if (strstr(filename,".lu") == NULL) {change_filename();}
    setCursorType(C_INVISABLE);
    strcpy(FILENAME, filename);
    gotoxy(50, 10);
    textcolor(BLUE);
    printf("──────────MENÜ──────────\n");
    textcolor(WHITE);
    gotoxy(50, 11);
    printf("     ─────SAVE─────     \n");
    gotoxy(50, 12);
    printf("     ─────EDIT─────     \n");
    gotoxy(50, 13);
    printf("     ─────EXIT─────     \n");
    gotoxy(50, 14);
    textcolor(BLUE);
    printf("────────────────────────\n");
    textcolor(WHITE);
}


