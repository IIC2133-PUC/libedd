[<- prev](12-sll-deq.md) ------------------------------------------------ [next ->](14-sll-remove-by-ptr.md)

# 14) `sll_remove`

## > Firma

```c
int sll_remove(EddError *err, Sll *sll, size_t index);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT, EDD_EOOB`

## > Definición

```c
int sll_remove(EddError *err, Sll *sll, size_t index) {
    if (index == 0) {
        return sll_deq(err, sll);
    } else if (index == (sll->size - 1)) {
        return sll_pop(err, sll);
    }

    SllNode *prev_node = NULL;
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < index; i++) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    prev_node->next = current_node->next;
    int removed_data = sll_node_destroy(err, current_node);
    sll->size--;

    return removed_data;
}
```
