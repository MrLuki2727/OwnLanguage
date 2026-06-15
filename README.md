# OwnLanguage

A minimal BASIC-inspired programming language with a built-in terminal editor. Written entirely in C, runs in the Windows console.

Built from scratch — custom lexer, interpreter, and editor. No libraries, no frameworks, just C and a terminal.

---

## Editor

The editor opens directly in the terminal. Line numbers are shown automatically on the left — you don't type them.

| Key | Action |
|-----|--------|
| Arrow keys | Move cursor |
| Any character | Insert at cursor position |
| Backspace | Delete character left of cursor |
| Delete | Delete character right of cursor |
| Tab | Run the program |
| ESC | Open menu |

The editor only redraws the line that was changed — not the entire screen. Syntax highlighting is built in.

---

## Language Reference

Variables are single uppercase letters `A` to `Z`. There are no types — everything is a number (`double`).

### Commands

**LET** — assign a value to a variable
```
LET A = 5
LET A = A + 1
LET B = A * 2
```
One operation per assignment. No chained expressions.

**PRINT** — print a value to the output
```
PRINT A
PRINT 42
PRINT A + 3
```

**INPUT** — read a number from the user into a variable
```
INPUT A
```

**IF** — conditional execution, runs any command if condition is true
```
IF (A < 10) PRINT A
IF (A == 3) LET B = 0
IF (A > 5) GOTO 8
```

**ELSE** — must be on the line directly after an IF
```
IF (A < 5) PRINT A
ELSE PRINT 99
```

**WHILE / ENDWHILE** — loop while condition is true
```
WHILE (A < 10)
LET A = A + 1
PRINT A
ENDWHILE
```
Supports nesting.

**GOTO** — jump to a line number
```
GOTO 3
```

**END** — stop execution
```
END
```

### Operators

| Type | Symbols |
|------|---------|
| Arithmetic | `+` `-` `*` `/` |
| Comparison | `==` `!=` `<` `>` `<=` `>=` |

### Example Program

```
LET A = 0
WHILE (A < 10)
LET A = A + 1
PRINT A
ENDWHILE
PRINT 99
END
```

Output: `1 2 3 4 5 6 7 8 9 10 99`

---

## Building

Requires CLion with MinGW. Windows only (`windows.h` for console control).

```bash
cmake --build cmake-build-debug --target OwnLanguage
```

Or just hit the build button in CLion.

The program opens `Code.lu` on startup. If it doesn't exist, it starts with an empty file.

---

## File Format

Programs are saved as `.lu` files. Plain text, one command per line, no line numbers in the file (those are handled by the editor).

---

## Roadmap

- [ ] String variables and `PRINT "text"`
- [ ] `FOR` loops
- [ ] Subroutines / `GOSUB`
- [ ] Multiple operations per line
- [ ] Open any `.lu` file from the menu
- [ ] Copy / paste in the editor

---

## Project Structure

```
main.c          — entry point, keyboard loop
editor.c/.h     — terminal editor, drawing, input handling
programm.c/.h   — program storage (array of lines)
run.c/.h        — interpreter, execution loop
logik.c/.h      — expression parser, condition evaluator
variablen.c/.h  — variable storage (A-Z)
console.c/.h    — low-level console functions (gotoxy, getxy, colors)
```

---
