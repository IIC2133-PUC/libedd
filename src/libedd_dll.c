#include "libedd_dll.h"

#define bool_as_str(b) ((b) ? "true" : "false")

DllNode *dll_node_create(int data) {
    DllNode *new_node = malloc(sizeof(DllNode));
    check_allocation(new_node);

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

int dll_node_destroy(EddError *err, DllNode *node) {
    if (errhandle_nullptr(err, "dll_node_destroy", node)) return 0;

    int data = node->data;
    free(node);

    return data;
}

Dll *dll_create(bool is_circular) {
    Dll *new_dll = malloc(sizeof(Dll));
    check_allocation(new_dll);

    new_dll->size = 0;
    new_dll->head = NULL;
    new_dll->tail = NULL;

    new_dll->is_circular = is_circular;

    return new_dll;
}

void dll_destroy(EddError *err, Dll *dll) {
    if (errhandle_nullptr(err, "dll_destroy", dll)) return;

    if (dll->is_circular && dll->size != 0) {
        dll->head->prev = NULL;
        dll->tail->next = NULL;
    }

    DllNode *current_node = dll->head;
    DllNode *next_node = NULL;
    while (current_node != NULL && !has_error(err)) {
        next_node = current_node->next;
        dll_node_destroy(err, current_node);
        current_node = next_node;
    }

    free(dll);

    return;
}

void dll_print(EddError *err, Dll *dll) {
    if (errhandle_nullptr(err, "dll_print", dll)) return;

    if (dll->size == 0) {
        printf("Dll\n> size        : %zu\n> head        : %p\n> tail        : %p\n",
               dll->size, dll->head, dll->tail);
        printf("> is_circular : %s\n> log forward : (nil)\n> log backward: (nil)\n",
               bool_as_str(dll->is_circular));
        return;
    }

    printf("Dll\n> size        : %zu\n> head        : %d\n> tail        : %d\n",
           dll->size, dll->head->data, dll->tail->data);
    printf("> is_circular : %s\n> log forward : ",
           bool_as_str(dll->is_circular));

    DllNode *current_node = dll->head;
    if (dll->is_circular) {
        printf("(%d)", current_node->prev->data);
    }
    printf("<-[%d]", current_node->data);
    current_node = current_node->next;
    for (size_t i = 1; i < (dll->size - 1); i++) {
        printf("-[%d]", current_node->data);
        current_node = current_node->next;
    }
    if (dll->size == 1) {
        printf("->");
    } else {
        printf("-[%d]->", current_node->data);
    }
    if (dll->is_circular) {
        printf("(%d)", current_node->next->data);
    }

    printf("\n> log backward: ");

    current_node = dll->tail;
    if (dll->is_circular) {
        printf("(%d)", current_node->next->data);
    }
    printf("<-[%d]", current_node->data);
    current_node = current_node->prev;
    for (size_t i = 1; i < (dll->size - 1); i++) {
        printf("-[%d]", current_node->data);
        current_node = current_node->prev;
    }
    if (dll->size == 1) {
        printf("->");
    } else {
        printf("-[%d]->", current_node->data);
    }
    if (dll->is_circular) {
        printf("(%d)", current_node->prev->data);
    }
    printf("\n");

    return;
}

void dll_connect_ends(EddError *err, Dll *dll) {
    if (errhandle_nullptr(err, "dll_connect_ends", dll)) return;

    if (dll->is_circular && dll->head != NULL && dll->tail != NULL) {
        dll->head->prev = dll->tail;
        dll->tail->next = dll->head;
    }

    return;
}

DllNode *dll_at(EddError *err, Dll *dll, size_t index) {
    const char *self = "dll_at";
    if (errhandle_nullptr(err, self, dll)) return NULL;
    if (errhandle_noent(err, self, dll->size)) return NULL;
    if (errhandle_oob(err, self, dll->size, index)) return NULL;

    DllNode *current_node = dll->head;
    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node;
}

void dll_push(EddError *err, Dll *dll, int data) {
    if (errhandle_nullptr(err, "dll_push", dll)) return;

    DllNode *new_node = dll_node_create(data);

    if (dll->size == 0) {
        dll->head = new_node;
        dll->tail = new_node;
    } else {
        new_node->prev = dll->tail;
        dll->tail->next = new_node;
        dll->tail = new_node;
    }
    dll->size++;

    dll_connect_ends(err, dll);

    return;
}

void dll_pushleft(EddError *err, Dll *dll, int data) {
    if (errhandle_nullptr(err, "dll_pushleft", dll)) return;

    DllNode *new_node = dll_node_create(data);

    if (dll->size == 0) {
        dll->head = new_node;
        dll->tail = new_node;
    } else {
        new_node->next = dll->head;
        dll->head->prev = new_node;
        dll->head = new_node;
    }
    dll->size++;

    dll_connect_ends(err, dll);

    return;
}

void dll_enq(EddError *err, Dll *dll, int data) {
    if (errhandle_nullptr(err, "dll_enq", dll)) return;
    dll_push(err, dll, data);
}

void dll_enqleft(EddError *err, Dll *dll, int data) {
    if (errhandle_nullptr(err, "dll_enqleft", dll)) return;
    dll_pushleft(err, dll, data);
}

void dll_insert(EddError *err, Dll *dll, int data, size_t index) {
    const char *self = "dll_insert";
    if (errhandle_nullptr(err, self, dll)) return;
    if (errhandle_oob(err, self, dll->size + 1, index)) return;

    if (index == 0) {
        dll_pushleft(err, dll, data);
        return;
    } else if (index == dll->size) {
        dll_push(err, dll, data);
        return;
    }

    DllNode *index_node = dll_at(err, dll, index);
    if (has_error(err)) return;

    DllNode *prev_node = index_node->prev;
    DllNode *new_node = dll_node_create(data);

    prev_node->next = new_node;
    new_node->prev = prev_node;
    new_node->next = index_node;
    index_node->prev = new_node;
    dll->size++;

    dll_connect_ends(err, dll);

    return;
}

int dll_pop(EddError *err, Dll *dll) {
    const char *self = "dll_pop";
    if (errhandle_nullptr(err, self, dll)) return 0;
    if (errhandle_noent(err, self, dll->size)) return 0;

    DllNode *new_tail = dll->tail->prev;
    int popped_data = dll_node_destroy(err, dll->tail);
    if (has_error(err)) return 0;

    if (dll->size == 1) {
        dll->head = NULL;
        dll->tail = NULL;
    } else {
        dll->tail = new_tail;
        new_tail->next = NULL;
    }
    dll->size--;

    dll_connect_ends(err, dll);

    return popped_data;
}

int dll_deq(EddError *err, Dll *dll) {
    const char *self = "dll_deq";
    if (errhandle_nullptr(err, self, dll)) return 0;
    if (errhandle_noent(err, self, dll->size)) return 0;

    DllNode *new_head = dll->head->next;
    int popped_data = dll_node_destroy(err, dll->head);
    if (has_error(err)) return 0;

    if (dll->size == 1) {
        dll->head = NULL;
        dll->tail = NULL;
    } else {
        dll->head = new_head;
        new_head->prev = NULL;
    }
    dll->size--;

    dll_connect_ends(err, dll);

    return popped_data;
}

int dll_remove(EddError *err, Dll *dll, size_t index) {
    const char *self = "dll_remove";
    if (errhandle_nullptr(err, self, dll)) return 0;
    if (errhandle_noent(err, self, dll->size)) return 0;
    if (errhandle_oob(err, self, dll->size, index)) return 0;

    if (index == 0) {
        return dll_deq(err, dll);
    } else if (index == (dll->size - 1)) {
        return dll_pop(err, dll);
    }

    DllNode *index_node = dll_at(err, dll, index);
    if (has_error(err)) return 0;
    DllNode *prev_node = index_node->prev;
    DllNode *next_node = index_node->next;

    int removed_data = dll_node_destroy(err, index_node);
    if (has_error(err)) return 0;

    prev_node->next = next_node;
    next_node->prev = prev_node;
    dll->size--;

    dll_connect_ends(err, dll);

    return removed_data;
}

int dll_remove_by_ptr(EddError *err, Dll *dll, DllNode *target_node) {
    const char *self = "dll_remove_by_ptr";
    if (errhandle_nullptr(err, self, dll)) return 0;
    if (errhandle_nullptr(err, self, target_node)) return 0;

    if (target_node == dll->head) {
        return dll_deq(err, dll);
    } else if (target_node == dll->tail) {
        return dll_pop(err, dll);
    }

    bool found = false;
    DllNode *current_node = dll->head;
    DllNode *last_value = (dll->is_circular) ? dll->tail : NULL;
    while (current_node != last_value && !found && !has_error(err)) {
        if (current_node == target_node) {
            found = true;
            continue;
        }
        current_node = current_node->next;
    }

    if (!found) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    DllNode *prev_node = current_node->prev;
    DllNode *next_node = current_node->next;
    int removed_data = dll_node_destroy(err, current_node);
    if (has_error(err)) return 0;

    prev_node->next = next_node;
    next_node->prev = prev_node;
    dll->size--;

    dll_connect_ends(err, dll);

    return removed_data;
}

int dll_remove_by_val(EddError *err, Dll *dll, int target) {
    const char *self = "dll_remove_by_val";
    if (errhandle_nullptr(err, self, dll)) return 0;
    if (errhandle_noent(err, self, dll->size)) return 0;

    if (target == dll->head->data) {
        return dll_deq(err, dll);
    } else if (target == dll->tail->data) {
        return dll_pop(err, dll);
    }

    bool found = false;
    DllNode *current_node = dll->head;
    DllNode *last_value = (dll->is_circular) ? dll->tail : NULL;
    while (current_node != last_value && !found && !has_error(err)) {
        if (current_node->data == target) {
            found = true;
            continue;
        }
        current_node = current_node->next;
    }

    if (!found) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    DllNode *prev_node = current_node->prev;
    DllNode *next_node = current_node->next;
    int removed_data = dll_node_destroy(err, current_node);
    if (has_error(err)) return 0;

    prev_node->next = next_node;
    next_node->prev = prev_node;
    dll->size--;

    dll_connect_ends(err, dll);

    return removed_data;
}

void dll_reverse(EddError *err, Dll *dll) {
    if (errhandle_nullptr(err, "dll_reverse", dll)) return;

    if (dll->size < 2) return;

    DllNode *prev_node = NULL;
    DllNode *current_node = dll->tail;
    DllNode *next_node = NULL;
    for (size_t i = 0; i < dll->size; i++) {
        next_node = current_node->prev;
        current_node->prev = prev_node;
        current_node->next = next_node;
        prev_node = current_node;
        current_node = next_node;
    }

    DllNode *head = dll->head;
    dll->head = dll->tail;
    dll->tail = head;

    dll_connect_ends(err, dll);

    return;
}

void dll_cmd(EddError *err, Dll *dll, FILE *input_file, const char *cmd) {
    const char *self = "dll_cmd";
    if (errhandle_nullptr(err, self, dll)) return;
    if (errhandle_nullptr(err, self, input_file)) return;
    if (errhandle_nullptr(err, self, (void*)cmd)) return;

    size_t index;
    int number;

    if (!strcmp(cmd, "PRINT")) {
        dll_print(err, dll);
    }

    if (!strcmp(cmd, "AT")) {
        fscanf(input_file, " %zu", &index);
        DllNode *result = dll_at(err, dll, index);
        if (has_error(err)) {
            printf("Node at index %zu is: (nil)\n", index);
        } else {
            printf("Node at index %zu is: %d\n", index, result->data);
        }
    }

    if (!strcmp(cmd, "PUSH")) {
        fscanf(input_file, " %d", &number);
        dll_push(err, dll, number);
        if (has_error(err)) {
            printf("Pushing value %d failed\n", number);
        } else {
            printf("Pushed value %d\n", number);
        }
    }

    if (!strcmp(cmd, "PUSHLEFT")) {
        fscanf(input_file, " %d", &number);
        dll_pushleft(err, dll, number);
        if (has_error(err)) {
            printf("Left-pushing value %d failed\n", number);
        } else {
            printf("Left-pushed value %d\n", number);
        }
    }

    if (!strcmp(cmd, "ENQ")) {
        fscanf(input_file, " %d", &number);
        dll_enq(err, dll, number);
        if (has_error(err)) {
            printf("Enqueueing value %d failed\n", number);
        } else {
            printf("Enqueued value %d\n", number);
        }
    }

    if (!strcmp(cmd, "ENQLEFT")) {
        fscanf(input_file, " %d", &number);
        dll_enqleft(err, dll, number);
        if (has_error(err)) {
            printf("Left-enqueueing value %d failed\n", number);
        } else {
            printf("Left-enqueued value %d\n", number);
        }
    }

    if (!strcmp(cmd, "INSERT")) {
        fscanf(input_file, " %d %zu", &number, &index);
        dll_insert(err, dll, number, index);
        if (has_error(err)) {
            printf("Failed to append value %d at index %zu\n", number, index);
        } else {
            printf("Appended value %d at index %zu\n", number, index);
        }
    }

    if (!strcmp(cmd, "POP")) {
        int popped_data = dll_pop(err, dll);
        if (has_error(err)) {
            printf("Nothing to remove (empty dll)\n");
        } else {
            printf("Removed node %d\n", popped_data);
        }
    }

    if (!strcmp(cmd, "DEQ")) {
        int deq_data = dll_deq(err, dll);
        if (has_error(err)) {
            printf("Nothing to dequeue (empty dll)\n");
        } else {
            printf("Dequeued node %d\n", deq_data);
        }
    }

    if (!strcmp(cmd, "REMOVE")) {
        fscanf(input_file, " %zu", &index);
        int popped_data = dll_remove(err, dll, index);
        if (has_error(err)) {
            printf("Nothing to remove (empty dll or index out of range)\n");
        } else {
            printf("Removed node %d at index %zu\n", popped_data, index);
        }
    }

    if (!strcmp(cmd, "REMOVE_BY_PTR")) {
        fscanf(input_file, " %zu", &index);
        DllNode *target_node = dll_at(err, dll, index);
        if (has_error(err)) {
            target_node = (DllNode *) 42;
        }

        int popped_data = dll_remove_by_ptr(err, dll, target_node);
        if (has_error(err)) {
            printf("Nothing to remove (empty dll or no match found)\n");
        } else {
            printf("Removed node %d by ptr\n", popped_data);
        }
    }

    if (!strcmp(cmd, "REMOVE_BY_VAL")) {
        fscanf(input_file, " %d", &number);
        int popped_data = dll_remove_by_val(err, dll, number);
        if (has_error(err)) {
            printf("Nothing to remove (empty dll or no match found)\n");
        } else {
            printf("Removed (first) node %d by val\n", popped_data);
        }
    }

    if (!strcmp(cmd, "REVERSE")) {
        dll_reverse(err, dll);
        printf("Reversed dll\n");
    }

    if (!strcmp(cmd, "BUGGY_CALLS")) {
        EDD_DEBUG = true;

        Dll *temp_dll = dll_create(false);
        dll_push(err, temp_dll, 0);
        DllNode *temp_node = dll_at(err, temp_dll, 0);

        dll_node_destroy(NULL, temp_node);
        dll_node_destroy(err, NULL);
        dll_destroy(NULL, temp_dll);
        dll_destroy(err, NULL);
        dll_print(NULL, temp_dll);
        dll_print(err, NULL);
        dll_connect_ends(NULL, temp_dll);
        dll_connect_ends(err, NULL);
        dll_at(NULL, temp_dll, 0);
        dll_at(err, NULL, 0);
        dll_push(NULL, temp_dll, 1);
        dll_push(err, NULL, 1);
        dll_pushleft(NULL, temp_dll, 1);
        dll_pushleft(err, NULL, 1);
        dll_enq(NULL, temp_dll, 1);
        dll_enq(err, NULL, 1);
        dll_enqleft(NULL, temp_dll, 1);
        dll_enqleft(err, NULL, 1);
        dll_insert(NULL, temp_dll, 1, 0);
        dll_insert(err, NULL, 1, 0);
        dll_pop(NULL, temp_dll);
        dll_pop(err, NULL);
        dll_deq(NULL, temp_dll);
        dll_deq(err, NULL);
        dll_remove(NULL, temp_dll, 0);
        dll_remove(err, NULL, 0);
        dll_remove_by_ptr(NULL, temp_dll, temp_node);
        dll_remove_by_ptr(err, NULL, temp_node);
        dll_remove_by_ptr(err, temp_dll, NULL);
        dll_remove_by_val(NULL, temp_dll, 1);
        dll_remove_by_val(err, NULL, 1);
        dll_reverse(NULL, temp_dll);
        dll_reverse(err, NULL);

        dll_print(err, temp_dll);
        dll_destroy(err, temp_dll);
    }
}
