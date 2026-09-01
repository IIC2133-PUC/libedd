# Módulo `err`

## > Descripción

Dado que _C_ es un lenguaje con tipado fuerte y sin _error handling_ integrado, a veces se vuelve complicado manejar y reportar correctamente errores. Es por esto que este módulo define la infraestructura para esta labor en toda la librería.

Existen dos componentes claves para ello, la variable global `EDD_DEBUG` y el `enum EddError`. En conjunto, nos permiten definir
los tipos de errores en la librería con un código único, y decidir si reportarlos o no en consola.

Un aspecto importante en la librería es que, para que el manejo de errores se comporte en forma intuitiva, ^^**toda función de _LibEDD_ que pueda errar debe cumplir dos requisitos**^^:

- El primer parámetro ^^**siempre**^^ debe ser `EddError *err`, y en caso de que se llame la función con `err` igual a `NULL`, esta ^^**debe retornar inmediatamente**^^, sin ejecutar su lógica usual.

- Las invocaciones deben ser ^^**idempotentes** con respecto a `err` y no asumir nada del valor de dicho parámetro^^. Esto significa que toda función debe encargarse de ^^**dejar el valor en `err` igual a `EDD_NOERR` en caso de que no ocurran errores, o al código correspondiente en caso de que sí ocurra una excepción, antes de retornar**^^. De este modo, el orden de llamadas de las funciones no afectará el comportamiento de la instancia de `EddError` usada para manejo de errores.

Por último, para simplificar el manejo de errores dentro de código que use la librería, existe la función `has_error` que se detalla más abajo.

## > Definiciones

Dentro de `libedd_err.h` se encuentran:

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

En primer lugar, vemos la variable global `EDD_DEBUG` de tipo `bool`. Cuando toma el valor `true`, activa los mensajes de _debugging_ de la librería: cada vez que una llamada a función retorna con errores, se imprimirá un mensaje con la siguiente estructura:

`[DEBUG] (*código de error*) Error reported by *función*: *descripción*`

Donde:

- `código de error` es el valor en el `enum EddError` del error reportado por la función.

- `función` es el nombre de la función que reportó el error

- `descripción` es una explicación de lo que significa el error

Por ejemplo, si la función invocada es `sll_at` con un índice fuera de rango, el mensaje de _debugging_ impreso en consola sería:

`[DEBUG] (EDD_EOOB) Error reported by sll_at: Search is out of bounds (for example: index is bigger or equal to size)`

Por otro lado, tenemos el `enum EddError`, que contiene todos los códigos de error existentes en la librería. Esto permite que, al pasar por referencia una variable de tipo `EddError`, la función pueda asignar el código correspondiente en caso de error. A continuación, se deja una explicación detallada de qué significa cada uno:

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
