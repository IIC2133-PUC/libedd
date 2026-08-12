#include <string.h>
#include <stdio.h>

#include "libedd_err.h"
#include "libedd_sll.h"
#include "libedd_dll.h"
#include "libedd_sort.h"
#include "libedd_heap.h"

bool EDD_DEBUG = true;

void sll_tester(FILE *input_file, FILE *output_file, size_t n_events) {
    EddError err = EDD_NOERR;
    Sll *sll = sll_create();

    char cmd[32];
    for (size_t i = 0; i < n_events; i++) {
        fscanf(input_file, "%s", cmd);
        sll_cmd(&err, sll, input_file, output_file, cmd);
    }

    sll_destroy(&err, sll);
}

void dll_tester(FILE *input_file, FILE *output_file, size_t n_events) {
    EddError err = EDD_NOERR;
    char cmd[32];

    fscanf(input_file, "%s", cmd);
    bool is_circular = false;
    if (!strcmp(cmd, "true")) {
        is_circular = true;
    }

    Dll *dll = dll_create(is_circular);

    for (size_t i = 0; i < n_events; i++) {
        fscanf(input_file, "%s", cmd);
        dll_cmd(&err, dll, input_file, output_file, cmd);
    }

    dll_destroy(&err, dll);
}

void sort_tester(FILE *input_file, FILE *output_file, size_t n_events) {
    EddError err = EDD_NOERR;
    char cmd[32];
    void *list;
    size_t list_size = (n_events > 2) ? (n_events - 2) : 1;
    int arr[list_size];
    for (size_t i = 0; i < list_size; i++) {
        arr[i] = 0;
    }

    char list_type[8];
    fscanf(input_file, "%s", list_type);

    if (!strcmp(list_type, "sll")) {
        list = sll_create();
    } else if (!strcmp(list_type, "dll")) {
        list = dll_create(false);
    } else {
        list = &arr;
    }

    int number;
    for (size_t i = 0; i < (n_events - 2); i++) {
        fscanf(input_file, "%d", &number);

        if (!strcmp(list_type, "sll")) {
            sll_push(&err, (Sll*)list, number);
        } else if (!strcmp(list_type, "dll")) {
            dll_push(&err, (Dll*)list, number);
        } else {
            ((int*)list)[i] = number;
        }
    }

    if (!strcmp(list_type, "sll")) {
        sll_print(&err, (Sll*)list, output_file);
    } else if (!strcmp(list_type, "dll")) {
        dll_print(&err, (Dll*)list, output_file);
    } else {
        fprintf(output_file, "Arr log: [");
        for (size_t i = 0; i < (list_size - 1); i++) {
            fprintf(output_file, "%d, ", ((int*)list)[i]);
        }
        fprintf(output_file, "%d]\n", ((int*)list)[list_size - 1]);
    }

    fscanf(input_file, "%s", cmd);
    sort_cmd(&err, list, list_size, input_file, output_file, cmd);

    if (!strcmp(list_type, "sll")) {
        sll_print(&err, (Sll*)list, output_file);
    } else if (!strcmp(list_type, "dll")) {
        dll_print(&err, (Dll*)list, output_file);
    } else {
        fprintf(output_file, "Arr log: [");
        for (size_t i = 0; i < (list_size - 1); i++) {
            fprintf(output_file, "%d, ", ((int*)list)[i]);
        }
        fprintf(output_file, "%d]\n", ((int*)list)[list_size - 1]);
    }

    if (!strcmp(list_type, "sll")) {
        sll_destroy(&err, (Sll*)list);
    } else if (!strcmp(list_type, "dll")) {
        dll_destroy(&err, (Dll*)list);
    }
}

void heap_tester(FILE *input_file, FILE *output_file, size_t n_events) {
    EddError err = EDD_NOERR;
    char cmd[32];

    size_t capacity = 0;
    bool is_min = false;

    fscanf(input_file, "%zu", &capacity);
    fscanf(input_file, "%s", cmd);
    if (!strcmp(cmd, "true")) {
        is_min = true;
    }

    Heap *heap = heap_create(capacity, is_min, NULL);

    for (size_t i = 0; i < n_events; i++) {
        fscanf(input_file, "%s", cmd);
        heap_cmd(&err, heap, input_file, output_file, cmd);
    }

    heap_destroy(&err, heap);
}

static bool check_arguments(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s EDD INPUT_FILE OUTPUT_FILE\n", argv[0]);
        printf("Where:\n");
        printf("\tEDD is the data structure to test\n");
        printf("\tINPUT_FILE is the path to the test file\n");
        printf("\tOUTPUT_FILE is the path to the program output file\n");
        exit(1);
    }
    return true;
}

int main(int argc, char **argv) {
    check_arguments(argc, argv);
    char *edd_to_test = argv[1];
    FILE *input_file = fopen(argv[2], "r");
    FILE *output_file = fopen(argv[3], "w");

    size_t N;
    int buffer = fscanf(input_file, "%zu", &N);
    if (buffer != 1) {
        printf("Error reading number of test events\n");
        return 1;
    }

    if (!strcmp(edd_to_test, "sll")) {
        sll_tester(input_file, output_file, N);
    }

    if (!strcmp(edd_to_test, "dll")) {
        dll_tester(input_file, output_file, N);
    }

    if (!strcmp(edd_to_test, "sort")) {
        sort_tester(input_file, output_file, N);
    }

    if (!strcmp(edd_to_test, "heap")) {
        heap_tester(input_file, output_file, N);
    }

    if (!strcmp(edd_to_test, "bst")) {
        //
    }

    if (!strcmp(edd_to_test, "avl")) {
        //
    }

    if (!strcmp(edd_to_test, "graph")) {
        //
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
