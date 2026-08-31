[<- prev](10-sll-insert.md) ------------------------------------------------ [next ->](12-sll-deq.md)

# 12) `sll_pop`

## > Firma

```c
int sll_pop(EddError *err, Sll *sll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int sll_pop(EddError *err, Sll *sll) {
    int popped_data = sll_node_destroy(err, sll->tail);

    if (sll->size == 1) {
        sll->head = NULL;
        sll->tail = NULL;
    } else {
        SllNode *prev_to_tail_node = sll->head;
        for (size_t i = 0; i < sll->size - 2; i++) {
            prev_to_tail_node = prev_to_tail_node->next;
        }

        sll->tail = prev_to_tail_node;
        sll->tail->next = NULL;
    }

    sll->size--;

    return popped_data;
}
```
