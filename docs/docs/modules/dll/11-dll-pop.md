[<- prev](10-dll-insert.md) ------------------------------------------------ [next ->](12-dll-deq.md)

# 12) `dll_pop`

## > Firma

```c
int dll_pop(EddError *err, Dll *dll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int dll_pop(EddError *err, Dll *dll) {
    DllNode *new_tail = dll->tail->prev;
    int popped_data = dll_node_destroy(err, dll->tail);

    if (dll->size == 1) {
        dll->head = NULL;
        dll->tail = NULL;
    } else {
        dll->tail = new_tail;
        new_tail->next = NULL;
    }
    dll->size--;

    dll_connect_ends(err, dll);

    return popped_data;
}
```
