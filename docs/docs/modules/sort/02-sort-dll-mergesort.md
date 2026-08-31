[<- prev](01-sort-sll-mergesort.md) ------------------------------------------------ [next ->](index.md)

# 03) `sort_dll_mergesort`

## > Firma

```c
void sort_dll_mergesort(EddError *err, Dll *dll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

Debido a la naturaleza de MergeSort, se incluye además la definición de `sort_dll_rec_mergesort` debido a que
es la función que realmente contiene la lógica del algoritmo:

```c
static DllNode *sort_dll_rec_mergesort(EddError *err,
                                       DllNode *head,
                                       size_t size) {
    if (size < 2) {
        return head;
    }

    size_t mid = size / 2;
    DllNode *mid_node = head;
    for (size_t i = 0; i < mid; i++) {
        mid_node = mid_node->next;
    }

    DllNode *prev_mid_node = mid_node->prev;
    prev_mid_node->next = NULL;
    mid_node->prev = NULL;

    DllNode* first_half = sort_dll_rec_mergesort(err, head, mid);
    DllNode* second_half = sort_dll_rec_mergesort(err, mid_node, mid + (size % 2));
    return sort_dll_merge(err, first_half, second_half);
}

void sort_dll_mergesort(EddError *err, Dll *dll) {
    if (dll->size == 0) return;

    if (dll->is_circular) {
        dll->head->prev = NULL;
        dll->tail->next = NULL;
    }

    DllNode *new_head = sort_dll_rec_mergesort(err, dll->head, dll->size);

    dll->head = new_head;
    DllNode *new_tail = new_head;
    for (size_t i = 0; i < (dll->size - 1); i++) {
        new_tail = new_tail->next;
    }

    if (new_tail == NULL) {
        dll->tail = new_head;
    } else {
        dll->tail = new_tail;
    }

    dll_connect_ends(err, dll);
}
```
