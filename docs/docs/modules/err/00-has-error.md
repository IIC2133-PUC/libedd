[<- prev](index.md) ------------------------------------------------ [next ->](01-check-allocation.md)

# 01) `has_error`

## > Firma

```c
bool has_error(EddError *err);
```

## > Descripción

Dada una instancia de `EddError`, la función retorna `true` si es que el valor de `err` ^^es un código de error^^ (es decir, cualquier
valor excepto `EDD_NOERR`), y retorna `false` en caso de que `err` no lo sea.

## > Posibles Errores

Listado: Ninguno

## > Definición

```c
bool has_error(EddError *err) {
    if (*err != EDD_NOERR) {
        return true;
    }

    return false;
}
```
