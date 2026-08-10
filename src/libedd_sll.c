#include "libedd_sll.h"

SllNode *sll_node_create(int data) {
    SllNode *new_node = malloc(sizeof(SllNode));
    check_allocation(new_node);

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

int sll_node_destroy(EddError *err, SllNode *node) {
    if (errhandle_nullptr(err, "sll_node_destroy", node)) return 0;

    int data = node->data;
    free(node);

    return data;
}

Sll *sll_create() {
    Sll *new_sll = malloc(sizeof(Sll));
    check_allocation(new_sll);

    new_sll->head = NULL;
    new_sll->tail = NULL;
    new_sll->size = 0;

    return new_sll;
}

void sll_destroy(EddError *err, Sll *sll) {
    if (errhandle_nullptr(err, "sll_destroy", sll)) return;

    SllNode *current_node = sll->head;
    SllNode *next_node = NULL;

    while (current_node != NULL && !has_error(err)) {
        next_node = current_node->next;
        sll_node_destroy(err, current_node);
        current_node = next_node;
    }

    free(sll);

    return;
}

void sll_print(EddError *err, Sll *sll) {
    if (errhandle_nullptr(err, "sll_print", sll)) return;

    if (sll->size == 0) {
        printf("Sll\n> size: %zu\n> head: %p\n> tail: %p\n> log : (nil)\n", sll->size, sll->head, sll->tail);
        return;
    }

    printf("Sll\n> size: %zu\n> head: %d\n> tail: %d\n> log : ", sll->size, sll->head->data, sll->tail->data);
    SllNode *current_node = sll->head;
    for (size_t i = 0; i < sll->size; i++) {
        printf("[%d]->", current_node->data);
        current_node = current_node->next;
    }
    printf("\n");

    return;
}

SllNode *sll_at(EddError *err, Sll *sll, size_t index) {
    const char *self = "sll_at";
    if (errhandle_nullptr(err, self, sll)) return NULL;
    if (errhandle_noent(err, self, sll->size)) return NULL;
    if (errhandle_oob(err, self, sll->size, index)) return NULL;

    SllNode *current_node = sll->head;
    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node;
}

void sll_push(EddError *err, Sll *sll, int data) {
    if (errhandle_nullptr(err, "sll_push", sll)) return;

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

void sll_pushleft(EddError *err, Sll *sll, int data) {
    if (errhandle_nullptr(err, "sll_pushleft", sll)) return;

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

void sll_enq(EddError *err, Sll *sll, int data) {
    if (errhandle_nullptr(err, "sll_enq", sll)) return;
    sll_push(err, sll, data);
}

void sll_enqleft(EddError *err, Sll *sll, int data) {
    if (errhandle_nullptr(err, "sll_enqleft", sll)) return;
    sll_pushleft(err, sll, data);
}

void sll_insert(EddError *err, Sll *sll, int data, size_t index) {
    const char *self = "sll_insert";
    if (errhandle_nullptr(err, self, sll)) return;
    if (errhandle_oob(err, self, sll->size + 1, index)) return;

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

int sll_pop(EddError *err, Sll *sll) {
    const char *self = "sll_pop";
    if (errhandle_nullptr(err, self, sll)) return 0;
    if (errhandle_noent(err, self, sll->size)) return 0;

    int popped_data = sll_node_destroy(err, sll->tail);
    if (has_error(err)) return 0;

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

int sll_deq(EddError *err, Sll *sll) {
    const char *self = "sll_deq";
    if (errhandle_nullptr(err, self, sll)) return 0;
    if (errhandle_noent(err, self, sll->size)) return 0;

    SllNode *new_head = sll->head->next;
    int deq_data = sll_node_destroy(err, sll->head);
    if (has_error(err)) return 0;

    sll->head = new_head;
    if (sll->size == 1) {
        sll->tail = new_head;
    }
    sll->size--;

    return deq_data;
}

int sll_remove(EddError *err, Sll *sll, size_t index) {
    const char *self = "sll_remove";
    if (errhandle_nullptr(err, self, sll)) return 0;
    if (errhandle_noent(err, self, sll->size)) return 0;
    if (errhandle_oob(err, self, sll->size, index)) return 0;

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

int sll_remove_by_ptr(EddError *err, Sll *sll, SllNode *target_node) {
    const char *self = "sll_remove_by_ptr";
    if (errhandle_nullptr(err, self, sll)) return 0;
    if (errhandle_nullptr(err, self, target_node)) return 0;

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
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    SllNode *next_node = current_node->next;
    int removed_data = sll_node_destroy(err, current_node);
    if (has_error(err)) return 0;

    prev_node->next = next_node;
    sll->size--;

    return removed_data;
}

int sll_remove_by_val(EddError *err, Sll *sll, int target) {
    const char *self = "sll_remove_by_val";
    if (errhandle_nullptr(err, self, sll)) return 0;
    if (errhandle_noent(err, self, sll->size)) return 0;

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
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    SllNode *next_node = current_node->next;
    int removed_data = sll_node_destroy(err, current_node);
    if (has_error(err)) return 0;

    prev_node->next = next_node;
    sll->size--;

    return removed_data;
}

void sll_cmd(EddError *err, Sll *sll, FILE *input_file, const char *cmd) {
    const char *self = "sll_cmd";
    if (errhandle_nullptr(err, self, sll)) return;
    if (errhandle_nullptr(err, self, input_file)) return;
    if (errhandle_nullptr(err, self, (void*)cmd)) return;

    size_t index;
    int number;

    if (!strcmp(cmd, "PRINT")) {
        sll_print(err, sll);
    }

    if (!strcmp(cmd, "AT")) {
        fscanf(input_file, " %zu", &index);
        SllNode *result = sll_at(err, sll, index);
        if (has_error(err)) {
            printf("Node at index %zu is: (nil)\n", index);
        } else {
            printf("Node at index %zu is: %d\n", index, result->data);
        }
    }

    if (!strcmp(cmd, "PUSH")) {
        fscanf(input_file, " %d", &number);
        sll_push(err, sll, number);
        if (has_error(err)) {
            printf("Pushing value %d failed\n", number);
        } else {
            printf("Pushed value %d\n", number);
        }
    }

    if (!strcmp(cmd, "PUSHLEFT")) {
        fscanf(input_file, " %d", &number);
        sll_pushleft(err, sll, number);
        if (has_error(err)) {
            printf("Left-pushing value %d failed\n", number);
        } else {
            printf("Left-pushed value %d\n", number);
        }
    }

    if (!strcmp(cmd, "ENQ")) {
        fscanf(input_file, " %d", &number);
        sll_enq(err, sll, number);
        if (has_error(err)) {
            printf("Enqueueing value %d failed\n", number);
        } else {
            printf("Enqueued value %d\n", number);
        }
    }

    if (!strcmp(cmd, "ENQLEFT")) {
        fscanf(input_file, " %d", &number);
        sll_enqleft(err, sll, number);
        if (has_error(err)) {
            printf("Left-enqueueing value %d failed\n", number);
        } else {
            printf("Left-enqueued value %d\n", number);
        }
    }

    if (!strcmp(cmd, "INSERT")) {
        fscanf(input_file, " %d %zu", &number, &index);
        sll_insert(err, sll, number, index);
        if (has_error(err)) {
            printf("Failed to append value %d at index %zu\n", number, index);
        } else {
            printf("Appended value %d at index %zu\n", number, index);
        }
    }

    if (!strcmp(cmd, "POP")) {
        int popped_data = sll_pop(err, sll);
        if (has_error(err)) {
            printf("Nothing to remove (empty sll)\n");
        } else {
            printf("Removed node %d\n", popped_data);
        }
    }

    if (!strcmp(cmd, "DEQ")) {
        int deq_data = sll_deq(err, sll);
        if (has_error(err)) {
            printf("Nothing to dequeue (empty sll)\n");
        } else {
            printf("Dequeued node %d\n", deq_data);
        }
    }

    if (!strcmp(cmd, "REMOVE")) {
        fscanf(input_file, " %zu", &index);
        int popped_data = sll_remove(err, sll, index);
        if (has_error(err)) {
            printf("Nothing to remove (empty sll or index out of range)\n");
        } else {
            printf("Removed node %d at index %zu\n", popped_data, index);
        }
    }

    if (!strcmp(cmd, "REMOVE_BY_PTR")) {
        fscanf(input_file, " %zu", &index);
        SllNode *target_node = sll_at(err, sll, index);
        if (has_error(err)) {
            target_node = (SllNode *) 42;
        }

        int popped_data = sll_remove_by_ptr(err, sll, target_node);
        if (has_error(err)) {
            printf("Nothing to remove (empty sll or no match found)\n");
        } else {
            printf("Removed node %d by ptr\n", popped_data);
        }
    }

    if (!strcmp(cmd, "REMOVE_BY_VAL")) {
        fscanf(input_file, " %d", &number);
        int popped_data = sll_remove_by_val(err, sll, number);
        if (has_error(err)) {
            printf("Nothing to remove (empty sll or no match found)\n");
        } else {
            printf("Removed (first) node %d by val\n", popped_data);
        }
    }

    if (!strcmp(cmd, "BUGGY_CALLS")) {
        EDD_DEBUG = true;

        Sll *temp_sll = sll_create();
        sll_push(err, temp_sll, 0);
        SllNode *temp_node = sll_at(err, temp_sll, 0);

        sll_node_destroy(NULL, temp_node);
        sll_node_destroy(err, NULL);
        sll_destroy(NULL, temp_sll);
        sll_destroy(err, NULL);
        sll_print(NULL, temp_sll);
        sll_print(err, NULL);
        sll_at(NULL, temp_sll, 0);
        sll_at(err, NULL, 0);
        sll_push(NULL, temp_sll, 1);
        sll_push(err, NULL, 1);
        sll_pushleft(NULL, temp_sll, 1);
        sll_pushleft(err, NULL, 1);
        sll_enq(NULL, temp_sll, 1);
        sll_enq(err, NULL, 1);
        sll_enqleft(NULL, temp_sll, 1);
        sll_enqleft(err, NULL, 1);
        sll_insert(NULL, temp_sll, 1, 0);
        sll_insert(err, NULL, 1, 0);
        sll_pop(NULL, temp_sll);
        sll_pop(err, NULL);
        sll_deq(NULL, temp_sll);
        sll_deq(err, NULL);
        sll_remove(NULL, temp_sll, 0);
        sll_remove(err, NULL, 0);
        sll_remove_by_ptr(NULL, temp_sll, temp_node);
        sll_remove_by_ptr(err, NULL, temp_node);
        sll_remove_by_ptr(err, temp_sll, NULL);
        sll_remove_by_val(NULL, temp_sll, 1);
        sll_remove_by_val(err, NULL, 1);

        sll_print(err, temp_sll);
        sll_destroy(err, temp_sll);
    }
}
