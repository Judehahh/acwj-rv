#include "defs.h"
#include "decl.h"
#include <ctype.h>

extern struct FileInfo FileInfo;

static int pb = '\n'; // The character need to put back

static int next() {
    int c;

    if (pb) {
        c = pb;
        pb = 0;
        return c;
    }

    c = fgetc(FileInfo.file);
    if (c == '\n')
        FileInfo.line++;

    return c;
}

static void putBack(int c) { pb = c; }

static int skip() {
    int c;

    c = next();
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f') {
        c = next();
    }

    return c;
}

static int scanInt(int c) {
    int val = 0;

    while (isdigit(c)) {
        val = val * 10 + (c - '0');
        c = next();
    }

    // Put the non-integer character back.
    putBack(c);
    return val;
}

/**
 * Scan and return the next token found in the input.
 * @param t pointer to token
 * @return 1 if token valid, 0 if no tokens left
 */
int nextToken(struct Token *t) {
    int c;

    // Skip whitespaces.
    c = skip();

    // Determine the token's type
    switch (c) {
    case EOF:
        t->token = T_EOF;
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
            t->value = scanInt(c);
            break;
        }
        printf("Unrecognized token %c on line %d\n", c, FileInfo.line);
        exit(1);
    }

    // Found a token.
    return 1;
}
