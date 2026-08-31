[<- prev](12-dll-deq.md) ------------------------------------------------ [next ->](14-dll-remove-by-ptr.md)

# 14) `dll_remove`

## > Firma

```c
int dll_remove(EddError *err, Dll *dll, size_t index);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT, EDD_EOOB`

## > Definición

```c
int dll_remove(EddError *err, Dll *dll, size_t index) {
    if (index == 0) {
        return dll_deq(err, dll);
    } else if (index == (dll->size - 1)) {
        return dll_pop(err, dll);
    }

    DllNode *index_node = dll_at(err, dll, index);
    DllNode *prev_node = index_node->prev;
    DllNode *next_node = index_node->next;

    int removed_data = dll_node_destroy(err, index_node);

    prev_node->next = next_node;
    next_node->prev = prev_node;
    dll->size--;

    dll_connect_ends(err, dll);

    return removed_data;
}
```
