[<- prev](14-dll-remove-by-ptr.md) ------------------------------------------------ [next ->](16-dll-reverse.md)

# 16) `dll_remove_by_val`

## > Firma

```c
int dll_remove_by_val(EddError *err, Dll *dll, int target);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int dll_remove_by_val(EddError *err, Dll *dll, int target) {
    if (target == dll->head->data) {
        return dll_deq(err, dll);
    } else if (target == dll->tail->data) {
        return dll_pop(err, dll);
    }

    bool found = false;
    DllNode *current_node = dll->head;
    DllNode *last_value = (dll->is_circular) ? dll->tail : NULL;
    while (current_node != last_value && !found) {
        if (current_node->data == target) {
            found = true;
            continue;
        }
        current_node = current_node->next;
    }

    if (!found) {
        return 0;
    }

    DllNode *prev_node = current_node->prev;
    DllNode *next_node = current_node->next;
    int removed_data = dll_node_destroy(err, current_node);

    prev_node->next = next_node;
    next_node->prev = prev_node;
    dll->size--;

    dll_connect_ends(err, dll);

    return removed_data;
}
```
