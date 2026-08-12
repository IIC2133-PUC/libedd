#include "libedd_sort.h"

static void sort_arr_merge(EddError *err, int *arr, size_t fa, size_t la, size_t fb, size_t lb) {
    const char *self = "sort_arr_merge";
    if (errhandle_nullptr(err, self, arr)) return;
    if (!(fa <= la && la <= fb && fb <= lb)) {
        *err = EDD_SORT_EIDXCOLL;
        edd_debug(err, self);
        return;
    }

    if (arr[la] <= arr[fb]) return;

    size_t idx_a = fa;
    size_t idx_b = fb;
    size_t size = (lb - fa) + 1;
    int aux_arr[size];
    size_t idx = 0;
    while (idx_a <= la && idx_b <= lb) {
        if (arr[idx_a] <= arr[idx_b]) {
            aux_arr[idx] = arr[idx_a];
            idx_a++;
        } else {
            aux_arr[idx] = arr[idx_b];
            idx_b++;
        }
        idx++;
    }

    while (idx_a <= la) {
        aux_arr[idx] = arr[idx_a];
        idx_a++;
        idx++;
    }

    while (idx_b <= lb) {
        aux_arr[idx] = arr[idx_b];
        idx_b++;
        idx++;
    }

    for (size_t i = 0; i < size; i++) {
        arr[i] = aux_arr[i];
    }
}

static void sort_arr_rec_mergesort(EddError *err, int *arr, size_t size) {
    if (has_error(err)) return;

    if (size < 2) {
        return;
    }

    size_t mid = size / 2;
    sort_arr_rec_mergesort(err, arr, mid);
    sort_arr_rec_mergesort(err, &arr[mid], mid + (size % 2));
    sort_arr_merge(err, arr, 0, mid - 1, mid, size - 1);

    return;
}

void sort_arr_mergesort(EddError *err, int *arr, size_t size) {
    if (errhandle_nullptr(err, "sort_arr_mergesort", arr)) return;
    sort_arr_rec_mergesort(err, arr, size);
}

static SllNode *sort_sll_merge(EddError *err, SllNode* start_a, SllNode* start_b) {
    const char *self = "sort_sll_merge";
    if (errhandle_nullptr(err, self, start_a)) return NULL;
    if (errhandle_nullptr(err, self, start_b)) return NULL;

    SllNode* merge_head = (start_a->data <= start_b->data) ? start_a : start_b;
    SllNode* current_a = (merge_head == start_a) ? start_a->next : start_a;
    SllNode* current_b = (merge_head == start_b) ? start_b->next : start_b;
    SllNode* merge_tail = merge_head;
    merge_tail->next = NULL;

    while (current_a != NULL && current_b != NULL) {
        if (current_a->data <= current_b->data) {
            merge_tail->next = current_a;
            merge_tail = current_a;
            current_a = current_a->next;
            merge_tail->next = NULL;
        } else {
            merge_tail->next = current_b;
            merge_tail = current_b;
            current_b = current_b->next;
            merge_tail->next = NULL;
        }
    }

    if (current_a == NULL) {
        merge_tail->next = current_b;
    } else if (current_b == NULL) {
        merge_tail->next = current_a;
    }

    return merge_head;
}

static SllNode *sort_sll_rec_mergesort(EddError *err, SllNode *head, size_t size) {
    if (has_error(err)) return NULL;

    if (size < 2) {
        return head;
    }

    size_t mid = size / 2;
    SllNode *prev_mid_node = NULL;
    SllNode *mid_node = head;
    for (size_t i = 0; i < mid; i++) {
        prev_mid_node = mid_node;
        mid_node = mid_node->next;
    }

    prev_mid_node->next = NULL;

    SllNode* first_half = sort_sll_rec_mergesort(err, head, mid);
    SllNode* second_half = sort_sll_rec_mergesort(err, mid_node, mid + (size % 2));
    return sort_sll_merge(err, first_half, second_half);
}

void sort_sll_mergesort(EddError *err, Sll *sll) {
    if (errhandle_nullptr(err, "sort_sll_mergesort", sll)) return;
    if (sll->size == 0) return;

    SllNode *new_head = sort_sll_rec_mergesort(err, sll->head, sll->size);

    sll->head = new_head;
    SllNode *new_tail = new_head;
    for (size_t i = 0; i < (sll->size - 1); i++) {
        new_tail = new_tail->next;
    }

    if (new_tail == NULL) {
        sll->tail = new_head;
    } else {
        sll->tail = new_tail;
    }
}

static DllNode *sort_dll_merge(EddError *err, DllNode* start_a, DllNode* start_b) {
    const char *self = "sort_dll_merge";
    if (errhandle_nullptr(err, self, start_a)) return NULL;
    if (errhandle_nullptr(err, self, start_b)) return NULL;

    DllNode* merge_head = (start_a->data <= start_b->data) ? start_a : start_b;
    DllNode* current_a = (merge_head == start_a) ? start_a->next : start_a;
    DllNode* current_b = (merge_head == start_b) ? start_b->next : start_b;
    DllNode* merge_tail = merge_head;
    merge_tail->prev = NULL;
    merge_tail->next = NULL;

    while (current_a != NULL && current_b != NULL) {
        if (current_a->data <= current_b->data) {
            merge_tail->next = current_a;
            current_a->prev = merge_tail;
            merge_tail = current_a;
            current_a = current_a->next;
            merge_tail->next = NULL;
        } else {
            merge_tail->next = current_b;
            current_b->prev = merge_tail;
            merge_tail = current_b;
            current_b = current_b->next;
            merge_tail->next = NULL;
        }
    }

    if (current_a == NULL) {
        merge_tail->next = current_b;
        current_b->prev = merge_tail;
    } else if (current_b == NULL) {
        merge_tail->next = current_a;
        current_a->prev = merge_tail;
    }

    return merge_head;
}

static DllNode *sort_dll_rec_mergesort(EddError *err, DllNode *head, size_t size) {
    if (has_error(err)) return NULL;

    if (size < 2) {
        return head;
    }

    size_t mid = size / 2;
    DllNode *mid_node = head;
    for (size_t i = 0; i < mid; i++) {
        mid_node = mid_node->next;
    }

    DllNode *prev_mid_node = mid_node->prev;
    prev_mid_node->next = NULL;
    mid_node->prev = NULL;

    DllNode* first_half = sort_dll_rec_mergesort(err, head, mid);
    DllNode* second_half = sort_dll_rec_mergesort(err, mid_node, mid + (size % 2));
    return sort_dll_merge(err, first_half, second_half);
}

void sort_dll_mergesort(EddError *err, Dll *dll) {
    if (errhandle_nullptr(err, "sort_dll_mergesort", dll)) return;
    if (dll->size == 0) return;

    if (dll->is_circular) {
        dll->head->prev = NULL;
        dll->tail->next = NULL;
    }

    DllNode *new_head = sort_dll_rec_mergesort(err, dll->head, dll->size);

    dll->head = new_head;
    DllNode *new_tail = new_head;
    for (size_t i = 0; i < (dll->size - 1); i++) {
        new_tail = new_tail->next;
    }

    if (new_tail == NULL) {
        dll->tail = new_head;
    } else {
        dll->tail = new_tail;
    }

    dll_connect_ends(err, dll);
}

void sort_cmd(EddError *err, void *list, size_t list_size, FILE *input_file, FILE *output_file, const char *cmd) {
    const char *self = "sort_cmd";
    if (errhandle_nullptr(err, self, list)) return;
    if (errhandle_nullptr(err, self, input_file)) return;
    if (errhandle_nullptr(err, self, (void*)cmd)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }


    if (!strcmp(cmd, LIBEDD_CMDNAME_SORT_ARR_MERGESORT)) {
        sort_arr_mergesort(err, (int*)list, list_size);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_SORT_ARR_MERGESORT);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_SORT_ARR_MERGESORT);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_SORT_SLL_MERGESORT)) {
        sort_sll_mergesort(err, (Sll*)list);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_SORT_SLL_MERGESORT);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_SORT_SLL_MERGESORT);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_SORT_DLL_MERGESORT)) {
        sort_dll_mergesort(err, (Dll*)list);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_SORT_DLL_MERGESORT);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_SORT_DLL_MERGESORT);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_BUGGY_CALLS)) {
        EDD_DEBUG = true;

        size_t temp_size = 3;
        int *temp_arr = calloc(temp_size, sizeof(int));
        check_allocation(temp_arr);
        Sll *temp_sll = sll_create();
        Dll *temp_dll = dll_create(false);
        for (size_t i = 0; i < temp_size; i++) {
            sll_push(err, temp_sll, 0);
            dll_push(err, temp_dll, 0);
        }

        sort_arr_mergesort(NULL, temp_arr, temp_size);
        sort_arr_mergesort(err, NULL, temp_size);
        sort_sll_mergesort(NULL, temp_sll);
        sort_sll_mergesort(err, NULL);
        sort_dll_mergesort(NULL, temp_dll);
        sort_dll_mergesort(err, NULL);

        fprintf(output_file, "[");
        for (size_t i = 0; i < (temp_size - 1); i++) {
            fprintf(output_file, "%d, ", temp_arr[i]);
        }
        fprintf(output_file, "%d]\n", temp_arr[temp_size - 1]);
        sll_print(err, temp_sll, output_file);
        dll_print(err, temp_dll, output_file);

        free(temp_arr);
        sll_destroy(err, temp_sll);
        dll_destroy(err, temp_dll);
    }
}
