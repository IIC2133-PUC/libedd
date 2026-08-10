#ifndef LIBEDD_HEAP_H
#define LIBEDD_HEAP_H

#include <string.h>

#include "libedd_err.h"

/* === General Definitions (structs, typedefs, etc) === */

typedef int (*PriorityFunction)(int);

typedef struct heap {
    int *array;
    size_t capacity;
    size_t size;
    bool is_min;
    PriorityFunction priority;
} Heap;

/* ============= */

/* === Function Declarations === */

Heap *heap_create(size_t capacity, bool is_min, PriorityFunction priority);
void heap_destroy(EddError *err, Heap *heap);
void heap_print(EddError *err, Heap *heap);

size_t heap_compare(EddError *err, Heap* heap, size_t index_a, size_t index_b);
void heap_sift_down(EddError *err, Heap* heap, size_t index);
void heap_sift_up(EddError *err, Heap* heap, size_t index);

int heap_peek(EddError *err, Heap *heap);
void heap_push(EddError *err, Heap* heap, int key);
int heap_pop(EddError *err, Heap* heap);

void heap_cmd(EddError *err, Heap *heap, FILE *input_file, const char *cmd);

/* ============= */

#endif
