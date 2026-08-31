[<- prev](04-dll-print.md) ------------------------------------------------ [next ->](06-dll-push.md)

# 06) `dll_at`

## > Firma

```c
DllNode *dll_at(EddError *err, Dll *dll, size_t index);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR, EDD_ENOENT, EDD_EOOB`

## > Definición

```c
DllNode *dll_at(EddError *err, Dll *dll, size_t index) {
    DllNode *current_node = dll->head;
    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node;
}
```
