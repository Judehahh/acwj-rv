#include "defs.h"
#include "decl.h"
#include <assert.h>

#define GEN(fmt, args...) fprintf(OutFile, fmt "\n", ##args)

static FILE *OutFile = NULL;
static int Depth = 0;

static void preAsm() {
    GEN("  .globl main");
    GEN("main:");
}

static void postAsm() {
    // return a0 as result
    GEN("  ret");
}

// Push the value in a0 into the stack.
static void push() {
    GEN("  addi sp, sp, -8");
    GEN("  sd a0, 0(sp)");
    Depth++;
}

// Pop the top value in the stack into the specified register.
static void pop(char *reg) {
    GEN("  ld %s, 0(sp)", reg);
    GEN("  addi sp, sp, 8");
    Depth--;
}

static void cgadd() {
    // a0 = a0 + a1
    GEN("  add a0, a0, a1");
}

static void cgsub() {
    // a0 = a0 - a1
    GEN("  sub a0, a0, a1");
}

static void cgmul() {
    // a0 = a0 * a1
    GEN("  mul a0, a0, a1");
}

static void cgdiv() {
    // a0 = a0 / a1
    GEN("  div a0, a0, a1");
}

static void cgload(int value) {
    // load a value into a0
    GEN("  li a0, %d", value);
}

static void genAST(struct ASTnode *n) {
    int lreg, rreg;

    if (n->rhs) {
        genAST(n->rhs);
        push();
    }
    if (n->lhs) {
        genAST(n->lhs);
        pop("a1");
    }

    switch (n->op) {
    case A_ADD:
        return cgadd();
    case A_SUBTRACT:
        return cgsub();
    case A_MULTIPLY:
        return cgmul();
    case A_DIVIDE:
        return cgdiv();
    case A_INTLIT:
        return cgload(n->value);
    default:
        fprintf(stderr, "Unknown AST operator %d\n", n->op);
        exit(1);
    }
}

void genCode(FILE *file, struct ASTnode *n) {
    OutFile = file;

    preAsm();
    genAST(n);
    assert(Depth == 0);
    postAsm();
}
