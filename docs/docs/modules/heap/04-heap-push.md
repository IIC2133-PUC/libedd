[<- prev](03-heap-peek.md) ------------------------------------------------ [next ->](05-heap-pop.md)

# 05) `heap_push`

## > Firma

```c
void heap_push(EddError *err, Heap* heap, int key);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_HEAP_EFULL`

## > Definición

```c
void heap_push(EddError *err, Heap* heap, int key) {
    if (heap->size >= heap->capacity) {
        return;
    }

    heap->array[heap->size].seq = heap->seq;
    heap->array[heap->size].data = key;
    heap->seq++;
    heap->size++;
    size_t new_index = heap->size - 1;

    heap_sift_up(err, heap, new_index);
}
```
