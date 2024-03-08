#include "defs.h"
#include "decl.h"

extern struct FileInfo FileInfo;

// Parse a primary factor and return an AST node representing it.
static struct ASTnode *primary(struct Token *t) {
    struct ASTnode *n;

    switch (t->token) {
    case T_INTLIT:
        n = mkLeaf(A_INTLIT, t->value);
        nextToken(t);
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

// Return the priority of operators.
static int getOpPriority(int tokentype) {
    switch (tokentype) {
    case T_PLUS:
    case T_MINUS:
        return 10;
    case T_STAR:
    case T_SLASH:
        return 20;
    default:
        fprintf(stderr, "syntax error on line %d, token %d\n", FileInfo.line,
                tokentype);
        exit(1);
    }
}

// Return an AST tree whose root is a binary operator.
// prp: previous token's priotiry
struct ASTnode *parse(struct Token *t, int ptp) {
    struct ASTnode *lhs, *rhs;
    int nodetype;
    int tokentype;

    lhs = primary(t);

    tokentype = t->token;
    if (tokentype == T_EOF)
        return lhs;

    while (getOpPriority(tokentype) > ptp) {
        nextToken(t);
        rhs = parse(t, getOpPriority(tokentype));
        lhs = mkNode(getop(tokentype), lhs, rhs, 0);

        tokentype = t->token;
        if (tokentype == T_EOF)
            return lhs;
    }

    return lhs;
}
