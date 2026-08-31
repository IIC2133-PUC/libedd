[<- prev](04-sll-print.md) ------------------------------------------------ [next ->](06-sll-push.md)

# 06) `sll_at`

## > Firma

```c
SllNode *sll_at(EddError *err, Sll *sll, size_t index);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT, EDD_EOOB`

## > Definición

```c
SllNode *sll_at(EddError *err, Sll *sll, size_t index) {
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node;
}
```
