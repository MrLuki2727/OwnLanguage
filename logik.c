#include "logik.h"
#include "variablen.h"
#include <stdlib.h>
#include <ctype.h>

static void leerzeichen_ueberspringen(char **s)
{
    while (**s == ' ') (*s)++;
}

double operand_lesen(char **s)
{
    leerzeichen_ueberspringen(s);

    if (isalpha((unsigned char)**s))
    {
        char name = **s;
        (*s)++;
        return num_variable_lesen(name);
    }

    char *ende;
    double wert = strtod(*s, &ende);
    *s = ende;
    return wert;
}

double ausdruck_berechnen(char **s)
{
    double links = operand_lesen(s);

    leerzeichen_ueberspringen(s);

    char op = **s;
    if (op == '+' || op == '-' || op == '*' || op == '/')
    {
        (*s)++;
        double rechts = operand_lesen(s);

        switch (op)
        {
        case '+': return links + rechts;
        case '-': return links - rechts;
        case '*': return links * rechts;
        case '/': return links / rechts;
        }
    }

    return links;
}

int bedingung_auswerten(char **s)
{
    leerzeichen_ueberspringen(s);
    if (**s == '(') (*s)++;

    leerzeichen_ueberspringen(s);
    double links = operand_lesen(s);

    leerzeichen_ueberspringen(s);
    char op1 = **s;
    char op2 = *(*s + 1);

    int ergebnis = 0;
    double rechts;

    if (op1 == '=' && op2 == '=')      { *s += 2; rechts = operand_lesen(s); ergebnis = (links == rechts); }
    else if (op1 == '!' && op2 == '=') { *s += 2; rechts = operand_lesen(s); ergebnis = (links != rechts); }
    else if (op1 == '>' && op2 == '=') { *s += 2; rechts = operand_lesen(s); ergebnis = (links >= rechts); }
    else if (op1 == '<' && op2 == '=') { *s += 2; rechts = operand_lesen(s); ergebnis = (links <= rechts); }
    else if (op1 == '>')               { (*s)++;  rechts = operand_lesen(s); ergebnis = (links > rechts); }
    else if (op1 == '<')               { (*s)++;  rechts = operand_lesen(s); ergebnis = (links < rechts); }

    leerzeichen_ueberspringen(s);
    if (**s == ')') (*s)++;

    return ergebnis;
}