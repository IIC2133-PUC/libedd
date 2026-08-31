[<- prev](08-dll-enq.md) ------------------------------------------------ [next ->](10-dll-insert.md)

# 10) `dll_enqleft`

## > Firma

```c
void dll_enqleft(EddError *err, Dll *dll, int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`, indirectamente `EDD_EALLOC`

## > Definición

```c
void dll_enqleft(EddError *err, Dll *dll, int data) {
    dll_pushleft(err, dll, data);
}
```
