#ifndef LIBEDD_BST_H
#define LIBEDD_BST_H

#include <string.h>

#include "libedd_err.h"
#include "libedd_cmd.h"

/* === General Definitions (structs, typedefs, etc) === */

typedef struct bst_node {
    int key;
    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
} BstNode;

typedef char (*MovementFunction)(BstNode *, int);

typedef struct bst {
    BstNode *root;
    size_t size;
    MovementFunction move_to;
} Bst;

/* ============= */

/* === Function Declarations === */

BstNode *bst_node_create(int key);
int bst_node_destroy(EddError *err, BstNode *node);

Bst *bst_create(MovementFunction move_to);
void bst_destroy(EddError *err, Bst *bst);
void bst_print(EddError *err, Bst *bst, FILE *output_file);

BstNode *bst_search(EddError *err, Bst *bst, int key);
void bst_insert(EddError *err, Bst *bst, int key);
int bst_remove(EddError *err, Bst *bst, int key);

void bst_cmd(EddError *err, Bst *bst, FILE *input_file, FILE *output_file, const char *cmd);

/* ============= */

#endif
