[<- prev](00-heap-create.md) ------------------------------------------------ [next ->](02-heap-print.md)

# 02) `heap_destroy`

## > Firma

```c
void heap_destroy(EddError *err, Heap *heap);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

```c
void heap_destroy(EddError *err, Heap *heap) {
    free(heap->array);
    free(heap);

    return;
}
```
