# Módulo `err`

## > Descripción

## > Definiciones

## > Funciones

---

## 01) `has_error`

- Descripción:

- Firma:
```c
bool has_error(EddError *err);
```

- Lista de Errores: `None`

- Definición:
```c
bool has_error(EddError *err) {
    if (*err != EDD_NOERR) {
        return true;
    }

    return false;
}
```

---

## 02) `check_allocation`

- Descripción:

- Firma:
```c
void check_allocation(void* ptr);
```

- Lista de Errores: `EDD_EALLOC`

- Definición:
```c
void check_allocation(void* ptr) {
    if (ptr == NULL) {
        printf("\033[0;31m[!] CRITICAL ERROR: ALLOCATION FAILED (POSIBLE OOM ERROR), TERMINATING PROGRAM\033[0m\n");
        exit(EDD_EALLOC);
    }
}
```

---
