[<- prev](00-sll-node-create.md) ------------------------------------------------ [next ->](02-sll-create.md)

# 02) `sll_node_destroy`

## > Firma

```c
int sll_node_destroy(EddError *err, SllNode *node);
```

## > Descripción

## > Posibles Errores

Listado: `EDD_ENULLPTR`

## > Definición

```c
int sll_node_destroy(EddError *err, SllNode *node) {
    int data = node->data;
    free(node);

    return data;
}
```
