[<- prev](07-dll-pushleft.md) ------------------------------------------------ [next ->](09-dll-enqleft.md)

# 09) `dll_enq`

## > Firma

```c
void dll_enq(EddError *err, Dll *dll, int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EALLOC`

## > Definición

```c
void dll_enq(EddError *err, Dll *dll, int data) {
    dll_push(err, dll, data);
}
```
