

#ifndef OWNLANGUAGE_EDITOR_H
#define OWNLANGUAGE_EDITOR_H

extern int scroll_offset;
extern int running_printed_lines;
extern int previouse_scroll_offset;
extern bool redraw_all;
extern int exit_code;

void draw_editor(int offset);

void draw_editor_ambient(int offset);

void draw_editor_code(int offset);

void draw_editor_run();

void draw_editor_menu();

void print_in_console(int n);

int input_in_console();
#endif //OWNLANGUAGE_EDITOR_H
