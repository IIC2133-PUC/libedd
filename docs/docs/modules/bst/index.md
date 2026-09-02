# Módulo `bst`

## > Descripción

## > Definiciones

```c
#include "libedd_err.h"
#include "libedd_cmd.h"

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
```

## > Funciones

## ~> Base de `BstNode`
- 01) bst_node_create
- 02) bst_node_destroy

## ~> Base de `Bst`
- 03) bst_create
- 04) bst_destroy
- 05) bst_print

## ~> Operaciones fundamentales de `Bst`
- 06) bst_search
- 07) bst_insert
- 08) bst_remove
