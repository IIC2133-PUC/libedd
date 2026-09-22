#ifndef LIBEDD_BST_H
#define LIBEDD_BST_H

#include <string.h>

#include "libedd_err.h"
#include "libedd_cmd.h"

/* === General Definitions (structs, typedefs, etc) === */

typedef enum bst_variant {
    EDD_BST_MODE   ,
    EDD_AVL_MODE   ,
    EDD_RBT_MODE   ,
    EDD_CUSTOM_MODE,
} BstVariant;

typedef enum bst_operation {
    EDD_BST_INSERT,
    EDD_BST_REMOVE,
} BstOperation;

typedef enum bst_rbt_color: size_t {
    EDD_RBT_BLACK,
    EDD_RBT_RED  ,
} RbtColor;

typedef struct bst_node {
    int key;
    size_t variant_property;

    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
} BstNode;

typedef struct bst Bst;
typedef char (*MovementFunction)(BstNode *, int);
typedef void (*BalanceFunction)(EddError *, Bst *, BstNode *, BstOperation);

struct bst {
    BstNode *root;
    size_t size;
    MovementFunction move_to;

    BstVariant variant;
    size_t variant_property_default;
    BalanceFunction rebalance;
};

/* ============= */

/* === Function Declarations === */

BstNode *bst_node_create(int key, size_t variant_property);
int bst_node_destroy(EddError *err, BstNode *node);

Bst *bst_create(BstVariant variant, size_t variant_property_default, MovementFunction move_to, BalanceFunction rebalance);
void bst_destroy(EddError *err, Bst *bst);
void bst_print(EddError *err, Bst *bst, FILE *output_file);

void bst_rotate(EddError *err, BstNode *high_node, BstNode *low_node, bool left_rotation);
BstNode *bst_search(EddError *err, Bst *bst, int key);
void bst_insert(EddError *err, Bst *bst, int key);
int bst_remove(EddError *err, Bst *bst, int key);

void bst_cmd(EddError *err, Bst *bst, FILE *input_file, FILE *output_file, const char *cmd);

// Variant Balancing Functions
void bst_avl_rebalance(EddError *err, Bst *bst, BstNode *node, BstOperation operation);
void bst_rbt_rebalance(EddError *err, Bst *bst, BstNode *node, BstOperation operation);

/* ============= */

#endif
