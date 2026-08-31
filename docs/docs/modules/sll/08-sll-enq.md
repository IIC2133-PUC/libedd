[<- prev](07-sll-pushleft.md) ------------------------------------------------ [next ->](09-sll-enqleft.md)

# 09) `sll_enq`

## > Firma

```c
void sll_enq(EddError *err, Sll *sll, int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EALLOC`

## > Definición

```c
void sll_enq(EddError *err, Sll *sll, int data) {
    sll_push(err, sll, data);
}
```
