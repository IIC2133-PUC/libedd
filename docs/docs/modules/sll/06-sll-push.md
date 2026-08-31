[<- prev](05-sll-at.md) ------------------------------------------------ [next ->](07-sll-pushleft.md)

# 07) `sll_push`

## > Firma

```c
void sll_push(EddError *err, Sll *sll, int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EALLOC`

## > Definición

```c
void sll_push(EddError *err, Sll *sll, int data) {
    SllNode *new_node = sll_node_create(data);

    if (sll->size == 0) {
        sll->head = new_node;
        sll->tail = new_node;
        sll->size++;
        return;
    }

    sll->tail->next = new_node;
    sll->tail = new_node;
    sll->size++;

    return;
}
```
