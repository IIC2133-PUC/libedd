[<- prev](03-dll-destroy.md) ------------------------------------------------ [next ->](05-dll-at.md)

# 05) `dll_print`

## > Firma

```c
void dll_print(EddError *err, Dll *dll, FILE *output_file);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

```c
void dll_print(EddError *err, Dll *dll, FILE *output_file) {
    if (output_file == NULL) {
        output_file = stdout;
    }

    if (dll->size == 0) {
        fprintf(output_file, "Dll\n> size        : %zu\n> head        : %p\n> tail        : %p\n",
               dll->size, dll->head, dll->tail);
        fprintf(output_file, "> is_circular : %s\n> log forward : (nil)\n> log backward: (nil)\n",
               bool_as_str(dll->is_circular));
        return;
    }

    fprintf(output_file, "Dll\n> size        : %zu\n> head        : %d\n> tail        : %d\n",
           dll->size, dll->head->data, dll->tail->data);
    fprintf(output_file, "> is_circular : %s\n> log forward : ",
           bool_as_str(dll->is_circular));

    DllNode *current_node = dll->head;
    if (dll->is_circular) {
        fprintf(output_file, "(%d)", current_node->prev->data);
    }
    fprintf(output_file, "<-[%d]", current_node->data);
    current_node = current_node->next;
    for (size_t i = 1; i < (dll->size - 1); i++) {
        fprintf(output_file, "-[%d]", current_node->data);
        current_node = current_node->next;
    }
    if (dll->size == 1) {
        fprintf(output_file, "->");
    } else {
        fprintf(output_file, "-[%d]->", current_node->data);
    }
    if (dll->is_circular) {
        fprintf(output_file, "(%d)", current_node->next->data);
    }

    fprintf(output_file, "\n> log backward: ");

    current_node = dll->tail;
    if (dll->is_circular) {
        fprintf(output_file, "(%d)", current_node->next->data);
    }
    fprintf(output_file, "<-[%d]", current_node->data);
    current_node = current_node->prev;
    for (size_t i = 1; i < (dll->size - 1); i++) {
        fprintf(output_file, "-[%d]", current_node->data);
        current_node = current_node->prev;
    }
    if (dll->size == 1) {
        fprintf(output_file, "->");
    } else {
        fprintf(output_file, "-[%d]->", current_node->data);
    }
    if (dll->is_circular) {
        fprintf(output_file, "(%d)", current_node->prev->data);
    }
    fprintf(output_file, "\n");

    return;
}
```
