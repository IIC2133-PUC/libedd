#ifndef LIBEDD_DLL_H
#define LIBEDD_DLL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "libedd_err.h"
#include "libedd_cmd.h"

/* === General Definitions (structs, typedefs, etc) === */

typedef struct dll_node {
    int data;
    struct dll_node *prev;
    struct dll_node *next;
} DllNode;

typedef struct dll {
    DllNode *head;
    DllNode *tail;
    size_t size;

    bool is_circular;
} Dll;

/* ============= */

/* === Function Declarations === */

DllNode *dll_node_create(int data);
int dll_node_destroy(EddError *err, DllNode *node);

Dll *dll_create(bool is_circular);
void dll_destroy(EddError *err, Dll *dll);
void dll_print(EddError *err, Dll *dll, FILE *output_file);
void dll_connect_ends(EddError *err, Dll *dll);
DllNode *dll_at(EddError *err, Dll *dll, size_t index);

void dll_push(EddError *err, Dll *dll, int data);
void dll_pushleft(EddError *err, Dll *dll, int data);
void dll_enq(EddError *err, Dll *dll, int data);
void dll_enqleft(EddError *err, Dll *dll, int data);
void dll_insert(EddError *err, Dll *dll, int data, size_t index);

int dll_pop(EddError *err, Dll *dll);
int dll_deq(EddError *err, Dll *dll);
int dll_remove(EddError *err, Dll *dll, size_t index);
int dll_remove_by_ptr(EddError *err, Dll *dll, DllNode *target_node);
int dll_remove_by_val(EddError *err, Dll *dll, int target);

void dll_reverse(EddError *err, Dll *dll);

void dll_cmd(EddError *err, Dll *dll, FILE *input_file, FILE *output_file, const char *cmd);

/* ============= */

#endif
