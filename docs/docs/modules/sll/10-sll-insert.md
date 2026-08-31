[<- prev](09-sll-enqleft.md) ------------------------------------------------ [next ->](11-sll-pop.md)

# 11) `sll_insert`

## > Firma

```c
void sll_insert(EddError *err, Sll *sll, int data,
                size_t index);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_EOOB`, indirectamente `EDD_EALLOC`

## > Definición

```c
void sll_insert(EddError *err, Sll *sll, int data,
                size_t index) {
    if (index == 0) {
        sll_pushleft(err, sll, data);
        return;
    } else if (index == sll->size) {
        sll_push(err, sll, data);
        return;
    }

    SllNode *new_node = sll_node_create(data);
    SllNode *prev_node = NULL;
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < index; i++) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    prev_node->next = new_node;
    new_node->next = current_node;
    sll->size++;

    return;
}
```
