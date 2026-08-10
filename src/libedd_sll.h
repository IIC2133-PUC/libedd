#ifndef LIBEDD_SLL_H
#define LIBEDD_SLL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "libedd_err.h"

/* === General Definitions (structs, typedefs, etc) === */

typedef struct sll_node {
    int data;
    struct sll_node *next;
} SllNode;

typedef struct sll {
    SllNode *head;
    SllNode *tail;
    size_t size;
} Sll;

/* ============= */

/* === Function Declarations === */

SllNode *sll_node_create(int data);
int sll_node_destroy(EddError *err, SllNode *node);

Sll *sll_create();
void sll_destroy(EddError *err, Sll *sll);
void sll_print(EddError *err, Sll *sll);
SllNode *sll_at(EddError *err, Sll *sll, size_t index);

void sll_push(EddError *err, Sll *sll, int data);
void sll_pushleft(EddError *err, Sll *sll, int data);
void sll_enq(EddError *err, Sll *sll, int data);
void sll_enqleft(EddError *err, Sll *sll, int data);
void sll_insert(EddError *err, Sll *sll, int data, size_t index);

int sll_pop(EddError *err, Sll *sll);
int sll_deq(EddError *err, Sll *sll);
int sll_remove(EddError *err, Sll *sll, size_t index);
int sll_remove_by_ptr(EddError *err, Sll *sll, SllNode *target_node);
int sll_remove_by_val(EddError *err, Sll *sll, int target);

void sll_cmd(EddError *err, Sll *sll, FILE *input_file, const char *cmd);

/* ============= */

#endif
