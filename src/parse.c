#include "defs.h"
#include "decl.h"

extern struct FileInfo FileInfo;

// Parse a primary factor and return an AST node representing it.
static struct ASTnode *primary(struct Token *t) {
    struct ASTnode *n;

    switch (t->token) {
    case T_INTLIT:
        n = mkleaf(A_INTLIT, t->value);
        scan(t);
        return n;
    default:
        fprintf(stderr, "Syntax error on line %d\n", FileInfo.line);
        exit(1);
    }

    return n;
}

// Get an AST operator by a token.
int getop(int tok) {
    switch (tok) {
    case T_PLUS:
        return A_ADD;
    case T_MINUS:
        return A_SUBTRACT;
    case T_STAR:
        return A_MULTIPLY;
    case T_SLASH:
        return A_DIVIDE;
    default:
        fprintf(stderr, "Unknown token to get an operation at line %d\n",
                FileInfo.line);
        exit(1);
    }
}

// Return an AST tree whose root is a binary operator.
struct ASTnode *parse(struct Token *t) {
    struct ASTnode *n, *lhs, *rhs;
    int nodetype;

    lhs = primary(t);

    if (t->token == T_EOF)
        return lhs;

    nodetype = getop(t->token); // get the operator of root node

    // Get the next token and parse it.
    scan(t);
    rhs = parse(t);

    n = mknode(nodetype, lhs, rhs, 0);
    return n;
}
