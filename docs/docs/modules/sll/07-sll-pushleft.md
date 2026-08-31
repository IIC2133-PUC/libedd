[<- prev](06-sll-push.md) ------------------------------------------------ [next ->](08-sll-enq.md)

# 08) `sll_pushleft`

## > Firma

```c
void sll_pushleft(EddError *err, Sll *sll, int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EALLOC`

## > Definición

```c
void sll_pushleft(EddError *err, Sll *sll, int data) {
    SllNode *new_node = sll_node_create(data);

    if (sll->size == 0) {
        sll->head = new_node;
        sll->tail = new_node;
        sll->size++;
        return;
    }

    new_node->next = sll->head;
    sll->head = new_node;
    sll->size++;

    return;
}
```
