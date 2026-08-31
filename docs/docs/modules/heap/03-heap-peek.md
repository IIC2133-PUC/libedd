[<- prev](02-heap-print.md) ------------------------------------------------ [next ->](04-heap-push.md)

# 04) `heap_peek`

## > Firma

```c
int heap_peek(EddError *err, Heap *heap);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int heap_peek(EddError *err, Heap *heap) {
    return heap->array[0].data;
}
```
