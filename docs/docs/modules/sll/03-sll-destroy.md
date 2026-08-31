[<- prev](02-sll-create.md) ------------------------------------------------ [next ->](04-sll-print.md)

# 04) `sll_destroy`

## > Firma

```c
void sll_destroy(EddError *err, Sll *sll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

```c
void sll_destroy(EddError *err, Sll *sll) {
    SllNode *current_node = sll->head;
    SllNode *next_node = NULL;

    while (current_node != NULL) {
        next_node = current_node->next;
        sll_node_destroy(err, current_node);
        current_node = next_node;
    }

    free(sll);

    return;
}
```
