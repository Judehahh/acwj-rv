#include "defs.h"
#include "decl.h"
#include <ctype.h>

extern struct FileInfo FileInfo;

#define TEXTLEN 512
static char Text[TEXTLEN + 1];

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

// Scan an identifier and store it in buf[].
static int scanIdent(int c, char *buf, int lim) {
    int i = 0;

    while (isalpha(c) || isdigit(c) || c == '_') {
        if (i == lim - 1) {
            printf("Identifier is too long on line %d\n", FileInfo.line);
            exit(1);
        } else {
            buf[i++] = c;
        }
        c = next();
    }
    putBack(c);
    buf[i] = '\0';

    return i;
}

// Match a keyword.
static int keyword(char *s) {
    switch (s[0]) {
    case 'r':
        if (!strcmp(s, "return"))
            return T_RETURN;
        break;
    }
    return 0;
}

// Expect a token, otherwise throw an error.
void expectToken(struct Token *t, int expected, char *what) {
    if (t->token != expected) {
        printf("%s is expected on line %d\n", what, FileInfo.line);
        exit(1);
    }
    nextToken(t);
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
    case ';':
        t->token = T_SEMI;
        break;
    default:
        if (isdigit(c)) {
            t->token = T_INTLIT;
            t->value = scanInt(c);
            break;
        } else if (isalpha(c) || c == '_') {
            scanIdent(c, Text, TEXTLEN);

            int tokentype = keyword(Text);
            if (tokentype) {
                t->token = tokentype;
                break;
            }
            printf("Unrecognized symbol %s on line %d\n", Text, FileInfo.line);
            exit(1);
        }
        printf("Unrecognized character %c on line %d\n", c, FileInfo.line);
        exit(1);
    }

    // Found a token.
    return 1;
}
