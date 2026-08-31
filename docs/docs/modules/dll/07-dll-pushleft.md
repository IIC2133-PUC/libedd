[<- prev](06-dll-push.md) ------------------------------------------------ [next ->](08-dll-enq.md)

# 08) `dll_pushleft`

## > Firma

```c
void dll_pushleft(EddError *err, Dll *dll, int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EALLOC`

## > Definición

```c
void dll_pushleft(EddError *err, Dll *dll, int data) {
    DllNode *new_node = dll_node_create(data);

    if (dll->size == 0) {
        dll->head = new_node;
        dll->tail = new_node;
    } else {
        new_node->next = dll->head;
        dll->head->prev = new_node;
        dll->head = new_node;
    }
    dll->size++;

    dll_connect_ends(err, dll);

    return;
}
```
