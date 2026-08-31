[<- prev](02-dll-create.md) ------------------------------------------------ [next ->](04-dll-print.md)

# 04) `dll_destroy`

## > Firma

```c
void dll_destroy(EddError *err, Dll *dll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

```c
void dll_destroy(EddError *err, Dll *dll) {
    if (dll->is_circular && dll->size != 0) {
        dll->head->prev = NULL;
        dll->tail->next = NULL;
    }

    DllNode *current_node = dll->head;
    DllNode *next_node = NULL;
    while (current_node != NULL) {
        next_node = current_node->next;
        dll_node_destroy(err, current_node);
        current_node = next_node;
    }

    free(dll);

    return;
}
```
