[<- prev](08-sll-enq.md) ------------------------------------------------ [next ->](10-sll-insert.md)

# 10) `sll_enqleft`

## > Firma

```c
void sll_enqleft(EddError *err, Sll *sll, int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EALLOC`

## > Definición

```c
void sll_enqleft(EddError *err, Sll *sll, int data) {
    sll_pushleft(err, sll, data);
}
```
