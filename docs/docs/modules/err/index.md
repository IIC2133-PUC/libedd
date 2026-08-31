# Módulo `err`

## > Descripción

## > Definiciones

```c
extern bool EDD_DEBUG;

typedef enum libedd_err {
    // General errors
    EDD_NOERR        ,
    EDD_EALLOC       ,
    EDD_ENULLPTR     ,
    EDD_EOOB         ,
    EDD_ENOENT       ,

    // Sorting specific errors
    EDD_SORT_EIDXCOLL,

    // Heap specific errors
    EDD_HEAP_EFULL   ,
} EddError;
```

Explicación de los códigos de error en `EddError`:

### ~> Errores Generales:

- `EDD_NOERR`: Representa un estado ^^sin errores^^

- `EDD_EALLOC`: Representa un error al intentar asignar memoria dinámicamente (dentro del heap), este es un ^^**ERROR CRÍTICO**^^, y por tanto ninguna instancia de `EddError` tendrá este valor, si no que, en caso de ocurrir, el programa será terminado con código de salida igual a `EDD_EALLOC`

- `EDD_ENULLPTR`: Error que ocurre cuando se recibe un puntero con valor `NULL` de forma inesperada, y por tanto inválida

- `EDD_EOOB`: Abreviación para "Out of Bounds" (fuera de los límites), representa un error al intentar una búsqueda fuera del rango permitido

- `EDD_ENOENT`: Abreviación para "No entity" (entidad no existente), es un error que se da cuando una búsqueda fracasa por no encontrar la entidad objetivo

### ~> Errores de Sorting:

- `EDD_SORT_EIDXCOLL`: Representa un error causado por intentar realizar una operación _in place_ con rangos de índices que tienen una intersección no-vacía (cuando debería serlo)

### ~> Errores de Heaps:

- `EDD_HEAP_EFULL`: Error que se da cuando un `Heap` tiene su capacidad al máximo, y se intenta insertar un nuevo valor

## > Funciones

- [01) has_error](00-has-error.md)
- [02) check_allocation](01-check-allocation.md)
