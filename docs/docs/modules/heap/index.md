# Módulo `heap`

## > Descripción

## > Definiciones

```c
#include "libedd_err.h"
#include "libedd_cmd.h"

typedef int (*PriorityFunction)(int);

typedef struct heap_data {
    size_t seq;
    int data;
} HeapData;

typedef struct heap {
    size_t seq;
    HeapData *array;
    size_t capacity;
    size_t size;
    bool is_min;
    PriorityFunction priority;
} Heap;
```

## > Funciones

- [01) heap_create](00-heap-create.md)
- [02) heap_destroy](01-heap-destroy.md)
- [03) heap_print](02-heap-print.md)
- [04) heap_peek](03-heap-peek.md)
- [05) heap_push](04-heap-pushmd)
- [06) heap_pop](05-heap-pop.md)
