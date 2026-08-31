[<- prev](00-dll-node-create.md) ------------------------------------------------ [next ->](02-dll-create.md)

# 02) `dll_node_destroy`

## > Firma

```c
int dll_node_destroy(EddError *err, DllNode *node);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

```c
int dll_node_destroy(EddError *err, DllNode *node) {
    int data = node->data;
    free(node);

    return data;
}
```
