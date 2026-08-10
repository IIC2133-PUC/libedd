#include "libedd_heap.h"

static int heap_default_priority(int key) {
    return key;
}

Heap *heap_create(size_t capacity, bool is_min, PriorityFunction priority) {
    Heap *new_heap = malloc(sizeof(Heap));
    check_allocation(new_heap);

    size_t heap_capacity = (capacity > 0) ? capacity : 1;
    new_heap->array = calloc(heap_capacity, sizeof(int));
    check_allocation(new_heap->array);

    new_heap->capacity = heap_capacity;
    new_heap->size = 0;
    new_heap->is_min = is_min;
    new_heap->priority = (priority == NULL) ? heap_default_priority : priority;

    return new_heap;
}

void heap_destroy(EddError *err, Heap *heap) {
    const char *self = "heap_destroy";
    if (errhandle_nullptr(err, self, heap)) return;
    if (errhandle_nullptr(err, self, heap->array)) return;

    free(heap->array);
    free(heap);

    return;
}

static void heap_rec_tree_print(
    EddError *err,
    Heap *heap,
    size_t heap_idx,
    char *stack,
    size_t stack_idx,
    char parent,
    const char *left_sep,
    const char *right_sep
) {
    if (has_error(err)) return;
    const char *self = "heap_rec_tree_print";
    if (errhandle_nullptr(err, self, heap)) return;
    if (errhandle_nullptr(err, self, stack)) return;
    if (errhandle_oob(err, self, heap->size, heap_idx)) return;
    if (errhandle_oob(err, self, 64, stack_idx)) return;

    if (heap_idx != 0) {
        printf("            ");
    }

    for (size_t i = 0; i < stack_idx; i++) {
        if (stack[i] == 'l') {
            printf("%s", left_sep);
        } else if (stack[i] == 'r') {
            printf("%s", right_sep);
        }
    }

    if (parent == 'l') {
        stack[stack_idx] = 'l';
        printf("└─");
    } else if (parent == 'r') {
        stack[stack_idx] = 'r';
        printf("├─");
    }

    printf("[%d]\n", heap->array[heap_idx]);

    size_t left = 2 * heap_idx + 1;
    size_t right = left + 1;

    if (right < heap->size) {
        heap_rec_tree_print(err, heap, right, stack, stack_idx + 1, 'r', left_sep, right_sep);
    }

    if (left < heap->size) {
        heap_rec_tree_print(err, heap, left, stack, stack_idx + 1, 'l', left_sep, right_sep);
    }
}

void heap_print(EddError *err, Heap *heap) {
    const char *self = "heap_print";
    if (errhandle_nullptr(err, self, heap)) return;
    if (errhandle_nullptr(err, self, heap->array)) return;

    printf("Heap\n");
    printf("> is_min  : %s\n", (heap->is_min) ? "true" : "false");
    printf("> size    : %zu\n", heap->size);
    printf("> capacity: %zu\n", heap->capacity);
    printf("> log     : ");

    if (heap->size == 0) {
        printf("(nil)\n");
        return;
    }

    char stack[64];
    for (size_t i = 0; i < 64; i++) {
        stack[i] = '\0';
    }
    const char *left_sep = "   ";
    const char *right_sep = "│  ";
    heap_rec_tree_print(err, heap, 0, stack, 0, 't', left_sep, right_sep);

    return;
}

size_t heap_compare(EddError *err, Heap* heap, size_t index_a, size_t index_b) {
    const char *self = "heap_compare";
    if (errhandle_nullptr(err, self, heap)) return 0;
    if (errhandle_oob(err, self, heap->size, index_a)) return 0;
    if (errhandle_oob(err, self, heap->size, index_b)) return 0;

    int priority_a = heap->priority(heap->array[index_a]);
    int priority_b = heap->priority(heap->array[index_b]);

    if (heap->is_min) {
        priority_a *= -1;
        priority_b *= -1;
    }

    if (priority_a < priority_b) {
        return index_b;
    }

    return index_a;
}

void heap_sift_down(EddError *err, Heap* heap, size_t index) {
    const char *self = "heap_sift_down";
    if (errhandle_nullptr(err, self, heap)) return;
    if (errhandle_oob(err, self, heap->size, index)) return;

    size_t max_priority_index = index;
    size_t child_index;
    bool in_position = false;
    while (!in_position && !has_error(err)) {
        child_index = 2 * index + 1;
        if (child_index < heap->size) {
            max_priority_index = heap_compare(err, heap, max_priority_index, child_index);
        }

        child_index++;
        if (child_index < heap->size) {
            max_priority_index = heap_compare(err, heap, max_priority_index, child_index);
        }

        if (max_priority_index == index) {
            in_position = true;
            continue;
        }

        int temp = heap->array[index];
        heap->array[index] = heap->array[max_priority_index];
        heap->array[max_priority_index] = temp;

        index = max_priority_index;
    }

    return;
}

void heap_sift_up(EddError *err, Heap* heap, size_t index) {
    const char *self = "heap_sift_up";
    if (errhandle_nullptr(err, self, heap)) return;
    if (errhandle_oob(err, self, heap->size, index)) return;

    bool in_position = false;
    while (!in_position && !has_error(err)) {
        if (index == 0) {
            in_position = true;
            continue;
        }

        size_t parent_index = (index - 1) / 2;
        if (index == heap_compare(err, heap, index, parent_index)) {
            int temp = heap->array[index];
            heap->array[index] = heap->array[parent_index];
            heap->array[parent_index] = temp;

            index = parent_index;
        } else {
            in_position = true;
        }
    }

    return;
}

int heap_peek(EddError *err, Heap *heap) {
    const char *self = "heap_peek";
    if (errhandle_nullptr(err, self, heap)) return 0;
    if (errhandle_noent(err, self, heap->size)) return 0;

    return heap->array[0];
}

void heap_push(EddError *err, Heap* heap, int key) {
    const char *self = "heap_push";
    if (errhandle_nullptr(err, self, heap)) return;
    if (heap->size >= heap->capacity) {
        *err = EDD_HEAP_EFULL;
        edd_debug(err, self);
        return;
    }

    heap->array[heap->size] = key;
    heap->size++;
    size_t new_index = heap->size - 1;

    heap_sift_up(err, heap, new_index);
}

int heap_pop(EddError *err, Heap* heap) {
    const char *self = "heap_pop";
    if (errhandle_nullptr(err, self, heap)) return 0;
    if (errhandle_noent(err, self, heap->size)) return 0;

    int extracted_key = heap->array[0];
    heap->size--;
    heap->array[0] = heap->array[heap->size];
    heap->array[heap->size] = 0;

    if (heap->size > 1) {
        heap_sift_down(err, heap, 0);
    }

    return extracted_key;
}

void heap_cmd(EddError *err, Heap *heap, FILE *input_file, const char *cmd) {
    const char *self = "heap_cmd";
    if (errhandle_nullptr(err, self, heap)) return;
    if (errhandle_nullptr(err, self, input_file)) return;
    if (errhandle_nullptr(err, self, (void*)cmd)) return;

    int key;

    if (!strcmp(cmd, "PRINT")) {
        heap_print(err, heap);
    }

    if (!strcmp(cmd, "PEEK")) {
        int top_key = heap_peek(err, heap);
        if (has_error(err)) {
            printf("Nothing to peek at (empty heap)\n");
        } else {
            printf("Top key is %d\n", top_key);
        }
    }

    if (!strcmp(cmd, "PUSH")) {
        fscanf(input_file, " %d", &key);
        heap_push(err, heap, key);
        if (has_error(err)) {
            printf("Pushing key %d failed\n", key);
        } else {
            printf("Pushed key %d\n", key);
        }
    }

    if (!strcmp(cmd, "POP")) {
        int popped_key = heap_pop(err, heap);
        if (has_error(err)) {
            printf("Nothing to remove (empty heap)\n");
        } else {
            printf("Removed key %d\n", popped_key);
        }
    }

    if (!strcmp(cmd, "BUGGY_CALLS")) {
        EDD_DEBUG = true;

        Heap *temp_heap = heap_create(1, false, NULL);

        heap_destroy(NULL, temp_heap);
        heap_destroy(err, NULL);
        heap_print(NULL, temp_heap);
        heap_print(err, NULL);
        heap_compare(NULL, temp_heap, 0, 0);
        heap_compare(err, NULL, 0, 0);
        heap_sift_down(NULL, temp_heap, 0);
        heap_sift_down(err, NULL, 0);
        heap_sift_up(NULL, temp_heap, 0);
        heap_sift_up(err, NULL, 0);
        heap_peek(NULL, temp_heap);
        heap_peek(err, NULL);
        heap_push(NULL, temp_heap, 1);
        heap_push(err, NULL, 1);
        heap_pop(NULL, temp_heap);
        heap_pop(err, NULL);

        heap_print(err, temp_heap);
        heap_destroy(err, temp_heap);
    }
}
