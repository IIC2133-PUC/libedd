[<- prev](13-dll-remove.md) ------------------------------------------------ [next ->](15-dll-remove-by-val.md)

# 15) `dll_remove_by_ptr`

## > Firma

```c
int dll_remove_by_ptr(EddError *err, Dll *dll,
                      DllNode *target_node);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT`

## > Definición

```c
int dll_remove_by_ptr(EddError *err, Dll *dll,
                      DllNode *target_node) {
    if (target_node == dll->head) {
        return dll_deq(err, dll);
    } else if (target_node == dll->tail) {
        return dll_pop(err, dll);
    }

    bool found = false;
    DllNode *current_node = dll->head;
    DllNode *last_value = (dll->is_circular) ? dll->tail : NULL;
    while (current_node != last_value && !found) {
        if (current_node == target_node) {
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
