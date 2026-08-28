# Módulo `sll`

## > Descripción

## > Definiciones

## > Funciones

---

## ~> Base de `SllNode`

---

## 01) `sll_node_create`

- Descripción:

- Firma:
```c
SllNode *sll_node_create(int data);
```

- Lista de Errores: `EDD_EALLOC`

- Definición:
```c
SllNode *sll_node_create(int data) {
    SllNode *new_node = malloc(sizeof(SllNode));

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}
```

---

## 02) `sll_node_destroy`

- Descripción:

- Firma:
```c
int sll_node_destroy(EddError *err, SllNode *node);
```

- Lista de Errores: `EDD_ENULLPTR`

- Definición:
```c
int sll_node_destroy(EddError *err, SllNode *node) {
    int data = node->data;
    free(node);

    return data;
}
```

---

## ~> Base de `Sll`

---

## 03) `sll_create`

- Descripción:

- Firma:
```c
Sll *sll_create();
```

- Lista de Errores: `EDD_EALLOC`

- Definición:
```c
Sll *sll_create() {
    Sll *new_sll = malloc(sizeof(Sll));

    new_sll->head = NULL;
    new_sll->tail = NULL;
    new_sll->size = 0;

    return new_sll;
}
```

---

## 04) `sll_destroy`

- Descripción:

- Firma:
```c
void sll_destroy(EddError *err, Sll *sll);
```

- Lista de Errores: `EDD_ENULLPTR`

- Definición:
```c
void sll_destroy(EddError *err, Sll *sll) {
    SllNode *current_node = sll->head;
    SllNode *next_node = NULL;

    while (current_node != NULL) {
        next_node = current_node->next;
        sll_node_destroy(err, current_node);
        current_node = next_node;
    }

    free(sll);

    return;
}
```

---

## 05) `sll_print`

- Descripción:

- Firma:
```c
void sll_print(EddError *err, Sll *sll, FILE *output_file);
```

- Lista de Errores: `EDD_ENULLPTR`

- Definición:
```c
void sll_print(EddError *err, Sll *sll, FILE *output_file) {
    if (output_file == NULL) {
        output_file = stdout;
    }

    if (sll->size == 0) {
        fprintf(output_file, "Sll\n> size: %zu\n> head: %p\n> tail: %p\n> log : (nil)\n", sll->size, sll->head, sll->tail);
        return;
    }

    fprintf(output_file, "Sll\n> size: %zu\n> head: %d\n> tail: %d\n> log : ", sll->size, sll->head->data, sll->tail->data);
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < sll->size; i++) {
        fprintf(output_file, "[%d]->", current_node->data);
        current_node = current_node->next;
    }
    fprintf(output_file, "\n");

    return;
}
```

---

## 06) `sll_at`

- Descripción:

- Firma:
```c
SllNode *sll_at(EddError *err, Sll *sll, size_t index);
```

- Lista de Errores: `EDD_ENULLPTR, EDD_ENOENT, EDD_EOOB`

- Definición:
```c
SllNode *sll_at(EddError *err, Sll *sll, size_t index) {
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node;
}
```

---

## ~> Inserción en `Sll`

---

## 07) `sll_push`

- Descripción:

- Firma:
```c
void sll_push(EddError *err, Sll *sll, int data);
```

- Lista de Errores: `EDD_ENULLPTR`, indirectamente: `EDD_EALLOC`

- Definición:
```c
void sll_push(EddError *err, Sll *sll, int data) {
    SllNode *new_node = sll_node_create(data);

    if (sll->size == 0) {
        sll->head = new_node;
        sll->tail = new_node;
        sll->size++;
        return;
    }

    sll->tail->next = new_node;
    sll->tail = new_node;
    sll->size++;

    return;
}
```

---

## 08) `sll_pushleft`

- Descripción:

- Firma:
```c
void sll_pushleft(EddError *err, Sll *sll, int data);
```

- Lista de Errores: `EDD_ENULLPTR`, indirectamente: `EDD_EALLOC`

- Definición:
```c
void sll_pushleft(EddError *err, Sll *sll, int data) {
    SllNode *new_node = sll_node_create(data);

    if (sll->size == 0) {
        sll->head = new_node;
        sll->tail = new_node;
        sll->size++;
        return;
    }

    new_node->next = sll->head;
    sll->head = new_node;
    sll->size++;

    return;
}
```

---

## 09) `sll_enq`

- Descripción:

- Firma:
```c
void sll_enq(EddError *err, Sll *sll, int data);
```

- Lista de Errores: `EDD_ENULLPTR`, indirectamente: `EDD_EALLOC`

- Definición:
```c
void sll_enq(EddError *err, Sll *sll, int data) {
    sll_push(err, sll, data);
}
```

---

## 10) `sll_enqleft`

- Descripción:

- Firma:
```c
void sll_enqleft(EddError *err, Sll *sll, int data);
```

- Lista de Errores: `EDD_ENULLPTR`, indirectamente: `EDD_EALLOC`

- Definición:
```c
void sll_enqleft(EddError *err, Sll *sll, int data) {
    sll_pushleft(err, sll, data);
}
```

---

## 11) `sll_insert`

- Descripción:

- Firma:
```c
void sll_insert(EddError *err, Sll *sll, int data,
                size_t index);
```

- Lista de Errores: `EDD_ENULLPTR, EDD_EOOB`, indirectamente: `EDD_EALLOC`

- Definición:
```c
void sll_insert(EddError *err, Sll *sll, int data, 
                size_t index) {
    if (index == 0) {
        sll_pushleft(err, sll, data);
        return;
    } else if (index == sll->size) {
        sll_push(err, sll, data);
        return;
    }

    SllNode *new_node = sll_node_create(data);
    SllNode *prev_node = NULL;
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < index; i++) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    prev_node->next = new_node;
    new_node->next = current_node;
    sll->size++;

    return;
}
```

---

## ~> Eliminación en `Sll`

---

## 12) `sll_pop`

- Descripción:

- Firma:
```c
int sll_pop(EddError *err, Sll *sll);
```

- Lista de Errores: `EDD_ENULLPTR, EDD_ENOENT`

- Definición:
```c
int sll_pop(EddError *err, Sll *sll) {
    int popped_data = sll_node_destroy(err, sll->tail);

    if (sll->size == 1) {
        sll->head = NULL;
        sll->tail = NULL;
    } else {
        SllNode *prev_to_tail_node = sll->head;
        for (size_t i = 0; i < sll->size - 2; i++) {
            prev_to_tail_node = prev_to_tail_node->next;
        }

        sll->tail = prev_to_tail_node;
        sll->tail->next = NULL;
    }

    sll->size--;

    return popped_data;
}
```

---

## 13) `sll_deq`

- Descripción:

- Firma:
```c
int sll_deq(EddError *err, Sll *sll);
```

- Lista de Errores: `EDD_ENULLPTR, EDD_ENOENT`

- Definición:
```c
int sll_deq(EddError *err, Sll *sll) {
    SllNode *new_head = sll->head->next;
    int deq_data = sll_node_destroy(err, sll->head);

    sll->head = new_head;
    if (sll->size == 1) {
        sll->tail = new_head;
    }
    sll->size--;

    return deq_data;
}
```

---

## 14) `sll_remove`

- Descripción:

- Firma:
```c
int sll_remove(EddError *err, Sll *sll, size_t index);
```

- Lista de Errores: `EDD_ENULLPTR, EDD_ENOENT, EDD_EOOB`

- Definición:
```c
int sll_remove(EddError *err, Sll *sll, size_t index) {
    if (index == 0) {
        return sll_deq(err, sll);
    } else if (index == (sll->size - 1)) {
        return sll_pop(err, sll);
    }

    SllNode *prev_node = NULL;
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < index; i++) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    prev_node->next = current_node->next;
    int removed_data = sll_node_destroy(err, current_node);
    sll->size--;

    return removed_data;
}
```

---

## 15) `sll_remove_by_ptr`

```c
int sll_remove_by_ptr(EddError *err, Sll *sll,
                      SllNode *target_node);
```

- Descripción:

- Lista de Errores: `EDD_ENULLPTR, EDD_ENOENT`

- Definición:
```c
int sll_remove_by_ptr(EddError *err, Sll *sll,
                      SllNode *target_node) {
    if (target_node == sll->head) {
        return sll_deq(err, sll);
    } else if (target_node == sll->tail) {
        return sll_pop(err, sll);
    }

    bool found = false;
    SllNode *prev_node = NULL;
    SllNode *current_node = sll->head;
    while (current_node != NULL && !found) {
        if (current_node == target_node) {
            found = true;
            continue;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (!found) {
        return 0;
    }

    SllNode *next_node = current_node->next;
    int removed_data = sll_node_destroy(err, current_node);

    prev_node->next = next_node;
    sll->size--;

    return removed_data;
}
```

---

## 16) `sll_remove_by_val`

```c
int sll_remove_by_val(EddError *err, Sll *sll, int target);
```

- Descripción:

- Lista de Errores: `EDD_ENULLPTR, EDD_ENOENT`

- Definición:
```c
int sll_remove_by_val(EddError *err, Sll *sll, int target) {
    if (target == sll->head->data) {
        return sll_deq(err, sll);
    } else if (target == sll->tail->data) {
        return sll_pop(err, sll);
    }

    bool found = false;
    SllNode *prev_node = NULL;
    SllNode *current_node = sll->head;
    while (current_node != NULL && !found) {
        if (current_node->data == target) {
            found = true;
            continue;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (!found) {
        return 0;
    }

    SllNode *next_node = current_node->next;
    int removed_data = sll_node_destroy(err, current_node);

    prev_node->next = next_node;
    sll->size--;

    return removed_data;
}
```

---
