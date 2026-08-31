# Módulo `sll`

## > Descripción

## > Definiciones

```c
#include "libedd_err.h"
#include "libedd_cmd.h"

typedef struct sll_node {
    int data;
    struct sll_node *next;
} SllNode;

typedef struct sll {
    SllNode *head;
    SllNode *tail;
    size_t size;
} Sll;
```

## > Funciones

## ~> Base de `SllNode`

- [01) sll_node_create](00-sll-node-create.md)
- [02) sll_node_destroy](01-sll-node-destroy.md)

## ~> Base de `Sll`

- [03) sll_create](02-sll-create.md)
- [04) sll_destroy](03-sll-destroy.md)
- [05) sll_print](04-sll-print.md)
- [06) sll_at](05-sll-at.md)

## ~> Inserción en `Sll`

- [07) sll_push](06-sll-push.md)
- [08) sll_pushleft](07-sll-pushleft.md)
- [09) sll_enq](08-sll-enq.md)
- [10) sll_enqleft](09-sll-enqleft.md)
- [11) sll_insert](10-sll-insert.md)

## ~> Eliminación en `Sll`

- [12) sll_pop](11-sll-pop.md)
- [13) sll_deq](12-sll-deq.md)
- [14) sll_remove](13-sll-remove.md)
- [15) sll_remove_by_ptr](14-sll-remove-by-ptr.md)
- [16) sll_remove_by_val](15-sll-remove-by-val.md)
