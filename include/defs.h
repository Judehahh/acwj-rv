#ifndef __DEFS_H__
#define __DEFS_H__

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Source file infomation
struct FileInfo {
    int line;
    FILE *file;
};

// Token types
enum {
    T_PLUS,   // '+'
    T_MINUS,  // '-'
    T_STAR,   // '*'
    T_SLASH,  // '/'
    T_INTLIT, // integer literal

    T_EOF, // end of file
};

// Token struct
struct Token {
    int token;
    int value;
};

// AST node type
enum {
    A_ADD,
    A_SUBTRACT,
    A_MULTIPLY,
    A_DIVIDE,
    A_INTLIT,
};

// AST node struct
struct ASTnode {
    int op;              // operation
    struct ASTnode *lhs; // left child trees
    struct ASTnode *rhs; // right child trees
    int value;
};

#endif // __DEFS_H__
