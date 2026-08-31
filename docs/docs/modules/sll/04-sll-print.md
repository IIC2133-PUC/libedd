[<- prev](03-sll-destroy.md) ------------------------------------------------ [next ->](05-sll-at.md)

# 05) `sll_print`

## > Firma

```c
void sll_print(EddError *err, Sll *sll, FILE *output_file);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

```c
void sll_print(EddError *err, Sll *sll, FILE *output_file) {
    if (output_file == NULL) {
        output_file = stdout;
    }

    if (sll->size == 0) {
        fprintf(output_file, "Sll\n> size: %zu\n> head: %p\n> tail: %p\n> log : (nil)\n", sll->size, sll->head, sll->tail);
        return;
    }

    fprintf(output_file, "Sll\n> size: %zu\n> head: %d\n> tail: %d\n> log : ", sll->size, sll->head->data, sll->tail->data);
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < sll->size; i++) {
        fprintf(output_file, "[%d]->", current_node->data);
        current_node = current_node->next;
    }
    fprintf(output_file, "\n");

    return;
}
```
