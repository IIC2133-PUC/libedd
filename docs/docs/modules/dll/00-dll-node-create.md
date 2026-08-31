[<- prev](index.md) ------------------------------------------------ [next ->](01-dll-node-destroy.md)

# 01) `dll_node_create`

## > Firma

```c
DllNode *dll_node_create(int data);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_EALLOC`

## > Definición

```c
DllNode *dll_node_create(int data) {
    DllNode *new_node = malloc(sizeof(DllNode));

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}
```
