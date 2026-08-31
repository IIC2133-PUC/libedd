[<- prev](00-has-error.md) ------------------------------------------------ [next ->](index.md)

# 02) `check_allocation`

## > Firma

```c
void check_allocation(void* ptr);
```

## > Descripción

Dado un puntero a un dato de cualquier tipo (`void *` representa un puntero sin información de tipo; que apunta a "memoria cruda"), verifica
si su valor es `NULL`. De ser así, la función ^^detiene la ejecución del programa con código de salida `EDD_EALLOC`^^.

Por tanto, está pensada para usarse después de cualquier llamada a una función que asigne memoria dinámicamente (p.e.: `malloc` y `calloc`),
para asegurar que el llamado fue exitoso, y si no terminar el programa.

## > Posibles Errores

Listado: `EDD_EALLOC`

## > Definición

```c
void check_allocation(void* ptr) {
    if (ptr == NULL) {
        printf("\033[0;31m[!] CRITICAL ERROR: ALLOCATION FAILED (POSIBLE OOM ERROR), TERMINATING PROGRAM\033[0m\n");
        exit(EDD_EALLOC);
    }
}
```
