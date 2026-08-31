[<- prev](09-dll-enqleft.md) ------------------------------------------------ [next ->](11-dll-pop.md)

# 11) `dll_insert`

## > Firma

```c
void dll_insert(EddError *err, Dll *dll, int data,
                size_t index);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_EOOB`, indirectamente `EDD_EALLOC`

## > Definición

```c
void dll_insert(EddError *err, Dll *dll, int data,
                size_t index) {
    if (index == 0) {
        dll_pushleft(err, dll, data);
        return;
    } else if (index == dll->size) {
        dll_push(err, dll, data);
        return;
    }

    DllNode *index_node = dll_at(err, dll, index);
    DllNode *prev_node = index_node->prev;
    DllNode *new_node = dll_node_create(data);

    prev_node->next = new_node;
    new_node->prev = prev_node;
    new_node->next = index_node;
    index_node->prev = new_node;
    dll->size++;

    dll_connect_ends(err, dll);

    return;
}
```
