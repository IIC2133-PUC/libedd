[<- prev](15-dll-remove-by-val.md) ------------------------------------------------ [next ->](index.md)

# 17) `dll_reverse`

## > Firma

```c
void dll_reverse(EddError *err, Dll *dll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

```c
void dll_reverse(EddError *err, Dll *dll) {
    if (dll->size < 2) return;

    DllNode *prev_node = NULL;
    DllNode *current_node = dll->tail;
    DllNode *next_node = NULL;
    for (size_t i = 0; i < dll->size; i++) {
        next_node = current_node->prev;
        current_node->prev = prev_node;
        current_node->next = next_node;
        prev_node = current_node;
        current_node = next_node;
    }

    DllNode *head = dll->head;
    dll->head = dll->tail;
    dll->tail = head;

    dll_connect_ends(err, dll);

    return;
}
```
