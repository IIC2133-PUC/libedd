[<- prev](01-sll-node-destroy.md) ------------------------------------------------ [next ->](03-sll-destroy.md)

# 03) `sll_create`

## > Firma

```c
Sll *sll_create();
```

## > Descripción

## > Posibles Errores

Listado: `EDD_EALLOC`

## > Definición

```c
Sll *sll_create() {
    Sll *new_sll = malloc(sizeof(Sll));

    new_sll->head = NULL;
    new_sll->tail = NULL;
    new_sll->size = 0;

    return new_sll;
}
```
