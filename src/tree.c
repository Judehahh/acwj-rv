#include "defs.h"
#include "decl.h"

// Make a new AST node.
struct ASTnode *mknode(int op, struct ASTnode *lhs, struct ASTnode *rhs,
                       int value) {
    struct ASTnode *n;

    n = (struct ASTnode *)malloc(sizeof(struct ASTnode));
    if (n == NULL) {
        fprintf(stderr, "Malloc new ASTnode failed\n");
        exit(1);
    }

    n->op = op;
    n->lhs = lhs;
    n->rhs = rhs;
    n->value = value;

    return n;
}

// Make a new AST leaf.
struct ASTnode *mkleaf(int op, int value) {
    return mknode(op, NULL, NULL, value);
}

// Characters used to dump AST.
static char *ASTop[] = {"+", "-", "*", "/"};

// Dump the AST nodes and return the result.
int dumpAST(struct ASTnode *n) {
    int lval, rval;

    if (n->lhs)
        lval = dumpAST(n->lhs);
    if (n->rhs)
        rval = dumpAST(n->rhs);

    if (n->op == A_INTLIT)
        printf("int %d\n", n->value);
    else
        printf("%d %s %d\n", lval, ASTop[n->op], rval);

    switch (n->op) {
    case A_ADD:
        return lval + rval;
    case A_SUBTRACT:
        return lval - rval;
    case A_MULTIPLY:
        return lval * rval;
    case A_DIVIDE:
        return lval / rval;
    case A_INTLIT:
        return n->value;
    default:
        fprintf(stderr, "Unknown AST operator %d\n", n->op);
        exit(1);
    }
}
