[<- prev](11-dll-pop.md) ------------------------------------------------ [next ->](13-dll-remove.md)

# 13) `dll_deq`

## > Firma

```c
int dll_deq(EddError *err, Dll *dll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int dll_deq(EddError *err, Dll *dll) {
    DllNode *new_head = dll->head->next;
    int popped_data = dll_node_destroy(err, dll->head);

    if (dll->size == 1) {
        dll->head = NULL;
        dll->tail = NULL;
    } else {
        dll->head = new_head;
        new_head->prev = NULL;
    }
    dll->size--;

    dll_connect_ends(err, dll);

    return popped_data;
}
```
