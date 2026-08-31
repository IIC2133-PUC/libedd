# Módulo `dll`

## > Descripción

## > Definiciones

```c
#include "libedd_err.h"
#include "libedd_cmd.h"

typedef struct dll_node {
    int data;
    struct dll_node *prev;
    struct dll_node *next;
} DllNode;

typedef struct dll {
    DllNode *head;
    DllNode *tail;
    size_t size;

    bool is_circular;
} Dll;
```

Dentro del archivo `libedd_dll.c` existe una macro para simplificar la impresión de valores de tipo `bool`:

```c
#define bool_as_str(b) ((b) ? "true" : "false")
```

## > Funciones

## ~> Base de `DllNode`

- [01) dll_node_create](00-dll-node-create.md)
- [02) dll_node_destroy](01-dll-node-destroy.md)

## ~> Base de `Dll`

- [03) dll_create](02-dll-create.md)
- [04) dll_destroy](03-dll-destroy.md)
- [05) dll_print](04-dll-print.md)
- [06) dll_at](05-dll-at.md)

## ~> Inserción en `Dll`

- [07) dll_push](06-dll-push.md)
- [08) dll_pushleft](07-dll-pushleft.md)
- [09) dll_enq](08-dll-enq.md)
- [10) dll_enqleft](09-dll-enqleft.md)
- [11) dll_insert](10-dll-insert.md)

## ~> Eliminación en `Dll`

- [12) dll_pop](11-dll-pop.md)
- [13) dll_deq](12-dll-deq.md)
- [14) dll_remove](13-dll-remove.md)
- [15) dll_remove_by_ptr](14-dll-remove-by-ptr.md)
- [16) dll_remove_by_val](15-dll-remove-by-val.md)

## ~> Invertir una `Dll`

- [17) dll_reverse](16-dll-reverse.md)
