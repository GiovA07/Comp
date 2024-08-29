#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#ifndef AST_H
#define AST_H

typedef struct AST {
    struct Tsymbol *symbol;
    struct AST *left;
    struct AST *right;
} AST;

struct AST* createTree(Tsymbol* symbol, struct AST *l, struct AST *r);

void showTree(AST* tree);

void print_tree(AST* ar, int level, int is_last);

#endif
