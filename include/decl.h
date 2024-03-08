#ifndef __DECL_H__
#define __DECL_H__

#include "defs.h"

int nextToken(struct Token *t);

struct ASTnode *mkNode(int op, struct ASTnode *lhs, struct ASTnode *rhs,
                       int value);
struct ASTnode *mkLeaf(int op, int value);

struct ASTnode *parse(struct Token *t, int ptp);
int dumpAST(struct ASTnode *n);

void genCode(FILE *file, struct ASTnode *n);

#endif // __DECL_H__
