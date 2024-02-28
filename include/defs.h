#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// Token types
enum {
    T_PLUS,   // '+'
    T_MINUS,  // '-'
    T_STAR,   // '*'
    T_SLASH,  // '/'
    T_INTLIT, // integer literal
};

// Token struct
struct token {
    int token;
    int value;
};
