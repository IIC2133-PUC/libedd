#ifndef LIBEDD_GSLL_H
#define LIBEDD_GSLL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "libedd_err.h"
#include "libedd_cmd.h"

/* === General Definitions (structs, typedefs, etc) === */

typedef void (*FreeFunction)(void *);

typedef struct gsll_node {
    void* data;
    struct gsll_node *next;
} GSllNode;

typedef struct gsll {
    GSllNode *head;
    GSllNode *tail;
    size_t size;

    bool free_on_remove;
    FreeFunction data_free;
} GSll;

/* ============= */

/* === Function Declarations === */

GSllNode *gsll_node_create(EddError *err, void *data);
void *gsll_node_destroy(EddError *err, GSll *gsll, GSllNode *node);

GSll *gsll_create(bool free_on_remove, FreeFunction data_free);
void gsll_destroy(EddError *err, GSll *gsll);
void gsll_print(EddError *err, GSll *gsll, FILE *output_file);
GSllNode *gsll_at(EddError *err, GSll *gsll, size_t index);

void gsll_push(EddError *err, GSll *gsll, void *data);
void gsll_enq(EddError *err, GSll *gsll, void *data);
void gsll_insert(EddError *err, GSll *gsll, void *data, size_t index);

void *gsll_pop(EddError *err, GSll *gsll);
void *gsll_deq(EddError *err, GSll *gsll);
void *gsll_remove(EddError *err, GSll *gsll, size_t index);
void *gsll_remove_by_val(EddError *err, GSll *gsll, void *target);

void gsll_cmd(EddError *err, GSll *gsll, FILE *input_file, FILE *output_file, const char *cmd);

/* ============= */

#endif
