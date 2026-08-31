[<- prev](01-dll-node-destroy.md) ------------------------------------------------ [next ->](03-dll-destroy.md)

# 03) `dll_create`

## > Firma

```c
Dll *dll_create(bool is_circular);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_EALLOC`

## > Definición

```c
Dll *dll_create(bool is_circular) {
    Dll *new_dll = malloc(sizeof(Dll));

    new_dll->size = 0;
    new_dll->head = NULL;
    new_dll->tail = NULL;

    new_dll->is_circular = is_circular;

    return new_dll;
}
```
