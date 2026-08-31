[<- prev](01-heap-destroy.md) ------------------------------------------------ [next ->](03-heap-peek.md)

# 03) `heap_print`

## > Firma

```c
void heap_print(EddError *err, Heap *heap, FILE *output_file);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EOOB`

## > Definición

```c
void heap_print(EddError *err, Heap *heap, FILE *output_file) {
    if (output_file == NULL) {
        output_file = stdout;
    }

    fprintf(output_file, "Heap\n");
    fprintf(output_file, "> is_min  : %s\n", (heap->is_min) ? "true" : "false");
    fprintf(output_file, "> size    : %zu\n", heap->size);
    fprintf(output_file, "> capacity: %zu\n", heap->capacity);
    fprintf(output_file, "> seq     : %zu\n", heap->seq);
    fprintf(output_file, "> log     : ");

    if (heap->size == 0) {
        fprintf(output_file, "(nil)\n");
        return;
    }

    char stack[64];
    for (size_t i = 0; i < 64; i++) {
        stack[i] = '\0';
    }
    const char *left_sep = "   ";
    const char *right_sep = "│  ";
    heap_rec_tree_print(err, heap, 0, stack, 0, 't', left_sep, right_sep, output_file);

    return;
}
```
