#include "libedd_gsll.h"

static void default_free_function(void *ptr) {
    free(ptr);
}

GSllNode *gsll_node_create(EddError *err, void *data) {
    if (errhandle_nullptr(err, "gsll_node_create", data)) return NULL;

    GSllNode *new_node = malloc(sizeof(GSllNode));
    check_allocation(new_node);

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void *gsll_node_destroy(EddError *err, GSll *gsll, GSllNode *node) {
    const char *self = "gsll_node_destroy";
    if (errhandle_nullptr(err, self, gsll)) return 0;
    if (errhandle_nullptr(err, self, node)) return 0;

    void *data = node->data;
    if (gsll->free_on_remove) {
        gsll->data_free(node->data);
    }
    free(node);

    return data;
}

GSll *gsll_create(bool free_on_remove, FreeFunction data_free) {
    GSll *new_gsll = malloc(sizeof(GSll));
    check_allocation(new_gsll);

    new_gsll->head = NULL;
    new_gsll->tail = NULL;
    new_gsll->size = 0;

    new_gsll->free_on_remove = free_on_remove;
    new_gsll->data_free = data_free == NULL ? default_free_function : data_free;

    return new_gsll;
}

void gsll_destroy(EddError *err, GSll *gsll) {
    if (errhandle_nullptr(err, "gsll_destroy", gsll)) return;

    GSllNode *current_node = gsll->head;
    GSllNode *next_node = NULL;

    while (current_node != NULL && !has_error(err)) {
        next_node = current_node->next;
        gsll_node_destroy(err, gsll, current_node);
        current_node = next_node;
    }

    free(gsll);

    return;
}

void gsll_print(EddError *err, GSll *gsll, FILE *output_file) {
    if (errhandle_nullptr(err, "gsll_print", gsll)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }

    if (gsll->size == 0) {
        fprintf(output_file, "GSll\n"
                "> size          : %zu\n"
                "> head          : %p\n"
                "> tail          : %p\n"
                "> free_on_remove: %s\n"
                "> log           : (nil)\n",
                gsll->size, gsll->head, gsll->tail, gsll->free_on_remove ? "true" : "false");
        return;
    }

    fprintf(output_file, "GSll\n"
            "> size          : %zu\n"
            "> head          : %p\n"
            "> tail          : %p\n"
            "> free_on_remove: %s\n"
            "> log           : ",
            gsll->size, gsll->head->data, gsll->tail->data, gsll->free_on_remove ? "true" : "false");
    GSllNode *current_node = gsll->head;
    for (size_t i = 0; i < gsll->size; i++) {
        fprintf(output_file, "[%p]->", current_node->data);
        current_node = current_node->next;
    }
    fprintf(output_file, "\n");

    return;
}

GSllNode *gsll_at(EddError *err, GSll *gsll, size_t index) {
    const char *self = "gsll_at";
    if (errhandle_nullptr(err, self, gsll)) return NULL;
    if (errhandle_noent(err, self, gsll->size)) return NULL;
    if (errhandle_oob(err, self, gsll->size, index)) return NULL;

    GSllNode *current_node = gsll->head;
    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node;
}

void gsll_push(EddError *err, GSll *gsll, void *data) {
    const char *self = "gsll_push";
    if (errhandle_nullptr(err, self, gsll)) return;
    if (errhandle_nullptr(err, self, data)) return;

    GSllNode *new_node = gsll_node_create(err, data);

    if (gsll->size == 0) {
        gsll->head = new_node;
        gsll->tail = new_node;
        gsll->size++;
        return;
    }

    gsll->tail->next = new_node;
    gsll->tail = new_node;
    gsll->size++;

    return;
}

void gsll_enq(EddError *err, GSll *gsll, void *data) {
    const char *self = "gsll_enq";
    if (errhandle_nullptr(err, self, gsll)) return;
    if (errhandle_nullptr(err, self, data)) return;

    GSllNode *new_node = gsll_node_create(err, data);

    if (gsll->size == 0) {
        gsll->head = new_node;
        gsll->tail = new_node;
        gsll->size++;
        return;
    }

    new_node->next = gsll->head;
    gsll->head = new_node;
    gsll->size++;

    return;
}

void gsll_insert(EddError *err, GSll *gsll, void *data, size_t index) {
    const char *self = "gsll_insert";
    if (errhandle_nullptr(err, self, gsll)) return;
    if (errhandle_nullptr(err, self, data)) return;
    if (errhandle_oob(err, self, gsll->size + 1, index)) return;

    if (index == 0) {
        gsll_enq(err, gsll, data);
        return;
    } else if (index == gsll->size) {
        gsll_push(err, gsll, data);
        return;
    }

    GSllNode *new_node = gsll_node_create(err, data);
    GSllNode *prev_node = NULL;
    GSllNode *current_node = gsll->head;
    for (size_t i = 0; i < index; i++) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    prev_node->next = new_node;
    new_node->next = current_node;
    gsll->size++;

    return;
}

void *gsll_pop(EddError *err, GSll *gsll) {
    const char *self = "gsll_pop";
    if (errhandle_nullptr(err, self, gsll)) return 0;
    if (errhandle_noent(err, self, gsll->size)) return 0;

    void *popped_data = gsll_node_destroy(err, gsll, gsll->tail);
    if (has_error(err)) return 0;

    if (gsll->size == 1) {
        gsll->head = NULL;
        gsll->tail = NULL;
    } else {
        GSllNode *prev_to_tail_node = gsll->head;
        for (size_t i = 0; i < gsll->size - 2; i++) {
            prev_to_tail_node = prev_to_tail_node->next;
        }

        gsll->tail = prev_to_tail_node;
        gsll->tail->next = NULL;
    }

    gsll->size--;

    return popped_data;
}

void *gsll_deq(EddError *err, GSll *gsll) {
    const char *self = "gsll_deq";
    if (errhandle_nullptr(err, self, gsll)) return 0;
    if (errhandle_noent(err, self, gsll->size)) return 0;

    GSllNode *new_head = gsll->head->next;
    void *deq_data = gsll_node_destroy(err, gsll, gsll->head);
    if (has_error(err)) return 0;

    gsll->head = new_head;
    if (gsll->size == 1) {
        gsll->tail = new_head;
    }
    gsll->size--;

    return deq_data;
}

void *gsll_remove(EddError *err, GSll *gsll, size_t index) {
    const char *self = "gsll_remove";
    if (errhandle_nullptr(err, self, gsll)) return 0;
    if (errhandle_noent(err, self, gsll->size)) return 0;
    if (errhandle_oob(err, self, gsll->size, index)) return 0;

    if (index == 0) {
        return gsll_deq(err, gsll);
    } else if (index == (gsll->size - 1)) {
        return gsll_pop(err, gsll);
    }

    GSllNode *prev_node = NULL;
    GSllNode *current_node = gsll->head;
    for (size_t i = 0; i < index; i++) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    prev_node->next = current_node->next;
    void *removed_data = gsll_node_destroy(err, gsll, current_node);
    gsll->size--;

    return removed_data;
}

void *gsll_remove_by_val(EddError *err, GSll *gsll, void *target) {
    const char *self = "gsll_remove_by_val";
    if (errhandle_nullptr(err, self, gsll)) return 0;
    if (errhandle_nullptr(err, self, target)) return 0;
    if (errhandle_noent(err, self, gsll->size)) return 0;

    if (target == gsll->head->data) {
        return gsll_deq(err, gsll);
    } else if (target == gsll->tail->data) {
        return gsll_pop(err, gsll);
    }

    bool found = false;
    GSllNode *prev_node = NULL;
    GSllNode *current_node = gsll->head;
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

    GSllNode *next_node = current_node->next;
    void *removed_data = gsll_node_destroy(err, gsll, current_node);
    if (has_error(err)) return 0;

    prev_node->next = next_node;
    gsll->size--;

    return removed_data;
}

void gsll_cmd(EddError *err, GSll *gsll, FILE *input_file, FILE *output_file, const char *cmd) {
    const char *self = "gsll_cmd";
    if (errhandle_nullptr(err, self, gsll)) return;
    if (errhandle_nullptr(err, self, input_file)) return;
    if (errhandle_nullptr(err, self, (void*)cmd)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }

    size_t index;
    size_t addr;

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_PRINT)) {
        gsll_print(err, gsll, output_file);
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_AT)) {
        fscanf(input_file, " %zu", &index);
        GSllNode *result = gsll_at(err, gsll, index);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GSLL_AT, index);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GSLL_AT, index, result->data);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_PUSH)) {
        fscanf(input_file, " %zu", &addr);
        gsll_push(err, gsll, (void *)addr);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GSLL_PUSH, (void *)addr);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GSLL_PUSH, (void *)addr);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_ENQ)) {
        fscanf(input_file, " %zu", &addr);
        gsll_enq(err, gsll, (void *)addr);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GSLL_ENQ, (void *)addr);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GSLL_ENQ, (void *)addr);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_INSERT)) {
        fscanf(input_file, " %zu %zu", &addr, &index);
        gsll_insert(err, gsll, (void *)addr, index);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GSLL_INSERT, (void *)addr, index);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GSLL_INSERT, (void *)addr, index);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_POP)) {
        void *popped_data = gsll_pop(err, gsll);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GSLL_POP);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GSLL_POP, popped_data);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_DEQ)) {
        void *deq_data = gsll_deq(err, gsll);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GSLL_DEQ);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GSLL_DEQ, deq_data);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_REMOVE)) {
        fscanf(input_file, " %zu", &index);
        void *popped_data = gsll_remove(err, gsll, index);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GSLL_REMOVE);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GSLL_REMOVE, popped_data, index);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GSLL_REMOVE_BY_VAL)) {
        fscanf(input_file, " %zu", &addr);
        void *popped_data = gsll_remove_by_val(err, gsll, (void *)addr);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GSLL_REMOVE_BY_VAL);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GSLL_REMOVE_BY_VAL, popped_data);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_BUGGY_CALLS)) {
        EDD_DEBUG = true;

        GSll *temp_gsll = gsll_create(false, NULL);
        gsll_push(err, temp_gsll, (void *)0xAA);
        GSllNode *temp_node = gsll_at(err, temp_gsll, 0);

        gsll_node_destroy(NULL, temp_gsll, temp_node);
        gsll_node_destroy(err, NULL, temp_node);
        gsll_node_destroy(err, temp_gsll, NULL);
        gsll_destroy(NULL, temp_gsll);
        gsll_destroy(err, NULL);
        gsll_print(NULL, temp_gsll, output_file);
        gsll_print(err, NULL, output_file);
        gsll_at(NULL, temp_gsll, 0);
        gsll_at(err, NULL, 0);
        gsll_push(NULL, temp_gsll, (void *)0xFF);
        gsll_push(err, NULL, (void *)0xFF);
        gsll_enq(NULL, temp_gsll, (void *)0xFF);
        gsll_enq(err, NULL, (void *)0xFF);
        gsll_insert(NULL, temp_gsll, (void *)0xFF, 0);
        gsll_insert(err, NULL, (void *)0xFF, 0);
        gsll_pop(NULL, temp_gsll);
        gsll_pop(err, NULL);
        gsll_deq(NULL, temp_gsll);
        gsll_deq(err, NULL);
        gsll_remove(NULL, temp_gsll, 0);
        gsll_remove(err, NULL, 0);
        gsll_remove_by_val(NULL, temp_gsll, (void *)0xFF);
        gsll_remove_by_val(err, NULL, (void *)0xFF);
        gsll_remove_by_val(err, temp_gsll, NULL);

        gsll_print(err, temp_gsll, output_file);
        gsll_destroy(err, temp_gsll);
    }
}
