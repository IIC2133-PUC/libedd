[<- prev](04-heap-push.md) ------------------------------------------------ [next ->](index.md)

# 06) `heap_pop`

## > Firma

```c
int heap_pop(EddError *err, Heap* heap);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int heap_pop(EddError *err, Heap* heap) {
    int extracted_key = heap->array[0].data;
    heap->size--;
    heap->array[0] = heap->array[heap->size];
    heap->array[heap->size].data = 0;

    if (heap->size > 1) {
        heap_sift_down(err, heap, 0);
    }

    return extracted_key;
}
```
