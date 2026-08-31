[<- prev](index.md) ------------------------------------------------ [next ->](01-heap-destroy.md)

# 01) `heap_create`

## > Firma

```c
Heap *heap_create(size_t capacity, bool is_min,
                  PriorityFunction priority);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_EALLOC`

## > Definición

```c
Heap *heap_create(size_t capacity, bool is_min,
                  PriorityFunction priority) {
    Heap *new_heap = malloc(sizeof(Heap));

    new_heap->seq = 0;
    size_t heap_capacity = (capacity > 0) ? capacity : 1;

    new_heap->array = calloc(heap_capacity, sizeof(HeapData));

    new_heap->capacity = heap_capacity;
    new_heap->size = 0;
    new_heap->is_min = is_min;
    new_heap->priority = (priority == NULL) ? heap_default_priority : priority;

    return new_heap;
}
```
