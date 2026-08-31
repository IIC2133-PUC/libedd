[<- prev](index.md) ------------------------------------------------ [next ->](01-sll-node-destroy.md)

# 01) `sll_node_create`

## > Firma

```c
SllNode *sll_node_create(int data);
```

## > Descripción

Dado un valor entero `data`, crea un `SllNode` que tenga su atributo `data` igual al argumento del mismo nombre, y su
atributo `next` igual a `NULL`.

## > Posibles Errores

Listado: `EDD_EALLOC`

## > Definición

```c
SllNode *sll_node_create(int data) {
    SllNode *new_node = malloc(sizeof(SllNode));

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}
```
