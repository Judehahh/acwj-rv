#ifndef __DECL_H__
#define __DECL_H__

#include "defs.h"

int scan(struct Token *t);

struct ASTnode *mknode(int op, struct ASTnode *lhs, struct ASTnode *rhs,
                       int value);
struct ASTnode *mkleaf(int op, int value);

struct ASTnode *parse(struct Token *t, int ptp);

int dumpAST(struct ASTnode *n);

#endif // __DECL_H__
