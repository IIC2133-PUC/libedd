[<- prev](14-sll-remove-by-ptr.md) ------------------------------------------------ [next ->](index.md)

# 16) `sll_remove_by_val`

## > Firma

```c
int sll_remove_by_val(EddError *err, Sll *sll, int target);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int sll_remove_by_val(EddError *err, Sll *sll, int target) {
    if (target == sll->head->data) {
        return sll_deq(err, sll);
    } else if (target == sll->tail->data) {
        return sll_pop(err, sll);
    }

    bool found = false;
    SllNode *prev_node = NULL;
    SllNode *current_node = sll->head;
    while (current_node != NULL && !found) {
        if (current_node->data == target) {
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
