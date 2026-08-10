#ifndef LIBEDD_ERR_H
#define LIBEDD_ERR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* === General Definitions (structs, typedefs, etc) === */

extern bool EDD_DEBUG;

typedef enum libedd_err {
    // General errors
    EDD_NOERR        , // No errors, default value
    EDD_EALLOC       , // Allocation failed (CRITICAL ERROR, should terminate program with this value as status)
    EDD_ENULLPTR     , // Unexpected null pointer
    EDD_EOOB         , // Search within a data structure is out of bounds (OOB)
    EDD_ENOENT       , // No such entry/member

    // Sorting specific errors
    EDD_SORT_EIDXCOLL, // Indices passed for inplace operation generate overlapping ranges that should not be overlapping

    // Heap specific errors
    EDD_HEAP_EFULL   , // The heap is full (size == capacity), any push/insertion attempt will be ignored
} EddError;

/* ============= */

/* === Function Declarations === */

void check_allocation(void* ptr);
bool is_edderr_null(EddError *err, const char *caller);
void edd_debug(EddError *err, const char *caller);
bool has_error(EddError *err);

bool errhandle_nullptr(EddError *err, const char *caller, void *ptr);
bool errhandle_oob(EddError *err, const char *caller, size_t size, size_t index);
bool errhandle_noent(EddError *err, const char *caller, size_t size);

/* ============= */

#endif
