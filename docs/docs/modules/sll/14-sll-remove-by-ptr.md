[<- prev](13-sll-remove.md) ------------------------------------------------ [next ->](15-sll-remove-by-val.md)

# 15) `sll_remove_by_ptr`

## > Firma

```c
int sll_remove_by_ptr(EddError *err, Sll *sll,
                      SllNode *target_node);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int sll_remove_by_ptr(EddError *err, Sll *sll,
                      SllNode *target_node) {
    if (target_node == sll->head) {
        return sll_deq(err, sll);
    } else if (target_node == sll->tail) {
        return sll_pop(err, sll);
    }

    bool found = false;
    SllNode *prev_node = NULL;
    SllNode *current_node = sll->head;
    while (current_node != NULL && !found) {
        if (current_node == target_node) {
            found = true;
            continue;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (!found) {
        return 0;
    }

    SllNode *next_node = current_node->next;
    int removed_data = sll_node_destroy(err, current_node);

    prev_node->next = next_node;
    sll->size--;

    return removed_data;
}
```
