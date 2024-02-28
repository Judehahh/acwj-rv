#include "defs.h"
#include "decl.h"
#include <ctype.h>

extern int Line;
extern FILE *Infile;

static int Putback = 0;

static int next() {
    int c;

    if (Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if (c == '\n')
        Line++;

    return c;
}

static void putback(int c) {
    Putback = c;
}

static int skip() {
    int c;

    c = next();
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f') {
        c = next();
    }

    return c;
}

static int scanint(int c) {
    int val = 0;

    while (isdigit(c)) {
        val = val * 10 + (c - '0');
        c = next();
    }

    // Put the non-integer character back.
    putback(c);
    return val;
}

/**
 * Scan and return the next token found in the input.
 * @param t pointer to token
 * @return 1 if token valid, 0 if no tokens left
 */
int scan(struct token *t) {
    int c;

    // Skip whitespaces.
    c = skip();

    // Determine the token's type
    switch (c) {
    case EOF:
        return 0;
    case '+':
        t->token = T_PLUS;
        break;
    case '-':
        t->token = T_MINUS;
        break;
    case '*':
        t->token = T_STAR;
        break;
    case '/':
        t->token = T_SLASH;
        break;
    default:
        if (isdigit(c)) {
            t->token = T_INTLIT;
            t->value = scanint(c);
            break;
        }
        printf("Unrecognized token %c on line %d\n", c, Line);
    }

    // Found a token.
    return 1;
}
