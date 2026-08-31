[<- prev](index.md) ------------------------------------------------ [next ->](01-sort-sll-mergesort.md)

# 01) `sort_arr_mergesort`

## > Firma

```c
void sort_arr_mergesort(EddError *err, int *arr, size_t size);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_SORT_EIDXCOLL`

## > Definición

Debido a la naturaleza de MergeSort, se incluye además la definición de `sort_arr_rec_mergesort` debido a que
es la función que realmente contiene la lógica del algoritmo:

```c
static void sort_arr_rec_mergesort(EddError *err, int *arr,
                                   size_t size) {
    if (size < 2) {
        return;
    }

    size_t mid = size / 2;
    sort_arr_rec_mergesort(err, arr, mid);
    sort_arr_rec_mergesort(err, &arr[mid], mid + (size % 2));
    sort_arr_merge(err, arr, 0, mid - 1, mid, size - 1);

    return;
}

void sort_arr_mergesort(EddError *err, int *arr, size_t size) {
    sort_arr_rec_mergesort(err, arr, size);
}
```
