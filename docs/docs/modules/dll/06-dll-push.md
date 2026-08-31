[<- prev](05-dll-at.md) ------------------------------------------------ [next ->](07-dll-pushleft.md)

# 07) `dll_push`

## > Firma

```c
void dll_push(EddError *err, Dll *dll, int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EALLOC`

## > Definición

```c
void dll_push(EddError *err, Dll *dll, int data) {
    DllNode *new_node = dll_node_create(data);

    if (dll->size == 0) {
        dll->head = new_node;
        dll->tail = new_node;
    } else {
        new_node->prev = dll->tail;
        dll->tail->next = new_node;
        dll->tail = new_node;
    }
    dll->size++;

    dll_connect_ends(err, dll);

    return;
}
```
