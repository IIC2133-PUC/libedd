#ifndef LIBEDD_SORT_H
#define LIBEDD_SORT_H

#include "libedd_err.h"
#include "libedd_sll.h"
#include "libedd_dll.h"

/* === Function Declarations === */

void sort_arr_mergesort(EddError *err, int *arr, size_t size);
void sort_sll_mergesort(EddError *err, Sll *sll);
void sort_dll_mergesort(EddError *err, Dll *dll);
void sort_cmd(EddError *err, void *list, size_t list_size, FILE *input_file, const char *cmd);

/* ============= */

#endif
