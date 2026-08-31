[<- prev](11-sll-pop.md) ------------------------------------------------ [next ->](13-sll-remove.md)

# 13) `sll_deq`

## > Firma

```c
int sll_deq(EddError *err, Sll *sll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int sll_deq(EddError *err, Sll *sll) {
    SllNode *new_head = sll->head->next;
    int deq_data = sll_node_destroy(err, sll->head);

    sll->head = new_head;
    if (sll->size == 1) {
        sll->tail = new_head;
    }
    sll->size--;

    return deq_data;
}
```
