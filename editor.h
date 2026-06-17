

#ifndef OWNLANGUAGE_EDITOR_H
#define OWNLANGUAGE_EDITOR_H

extern int scroll_offset;
extern int running_printed_lines;
extern int previouse_scroll_offset;
extern int exit_code;
extern int clearall;

void draw_editor(int offset);

void draw_editor_ambient(int offset);

void draw_editor_code(int offset);

void draw_editor_run();

void draw_editor_menu();

void print_in_console(int n);

int input_in_console();

void change_filename();

void draw_code_with_synax(int number);
#endif //OWNLANGUAGE_EDITOR_H
