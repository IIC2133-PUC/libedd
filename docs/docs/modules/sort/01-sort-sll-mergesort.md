[<- prev](00-sort-arr-mergesort.md) ------------------------------------------------ [next ->](02-sort-dll-mergesort.md)

# 02) `sort_sll_mergesort`

## > Firma

```c
void sort_sll_mergesort(EddError *err, Sll *sll);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

Debido a la naturaleza de MergeSort, se incluye además la definición de `sort_sll_rec_mergesort` debido a que
es la función que realmente contiene la lógica del algoritmo:

```c
static SllNode *sort_sll_rec_mergesort(EddError *err,
                                       SllNode *head,
                                       size_t size) {
    if (size < 2) {
        return head;
    }

    size_t mid = size / 2;
    SllNode *prev_mid_node = NULL;
    SllNode *mid_node = head;
    for (size_t i = 0; i < mid; i++) {
        prev_mid_node = mid_node;
        mid_node = mid_node->next;
    }

    prev_mid_node->next = NULL;

    SllNode* first_half = sort_sll_rec_mergesort(err, head, mid);
    SllNode* second_half = sort_sll_rec_mergesort(err, mid_node, mid + (size % 2));
    return sort_sll_merge(err, first_half, second_half);
}

void sort_sll_mergesort(EddError *err, Sll *sll) {
    if (sll->size == 0) return;

    SllNode *new_head = sort_sll_rec_mergesort(err, sll->head, sll->size);

    sll->head = new_head;
    SllNode *new_tail = new_head;
    for (size_t i = 0; i < (sll->size - 1); i++) {
        new_tail = new_tail->next;
    }

    if (new_tail == NULL) {
        sll->tail = new_head;
    } else {
        sll->tail = new_tail;
    }
}
```
