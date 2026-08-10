#include "libedd_err.h"

void check_allocation(void* ptr) {
    if (ptr == NULL) {
        printf("\033[0;31m[!] CRITICAL ERROR: ALLOCATION FAILED (POSIBLE OOM ERROR), TERMINATING PROGRAM\033[0m\n");
        exit(EDD_EALLOC);
    }
}

bool is_edderr_null(EddError *err, const char *caller) {
    if (err == NULL) {
        printf("[\033[0;33mDEBUG\033[0m] \033[0;31mCRITICAL\033[0m Error reported by \033[0;36m%s\033[0m: ", caller);
        printf("Function requires a non-NULL EddError instance, ");
        printf("\033[0;31mNO CODE WAS EXECUTED INSIDE THE FUNCTION\033[0m\n");
        return true;
    }

    return false;
}

void edd_debug(EddError *err, const char *caller) {
    if (is_edderr_null(err, "edd_debug")) return;

    if (!EDD_DEBUG) return;

    printf("[\033[0;33mDEBUG\033[0m] ");
    switch (*err) {
        case EDD_NOERR:
            printf("(\033[0;35mEDD_NOERR\033[0m) ");
            printf("No errors reported by \033[0;36m%s\033[0m\n", caller);
            break;

        case EDD_EALLOC:
            printf("(\033[0;35mEDD_EALLOC\033[0m) ");
            printf("CRITICAL Error reported by \033[0;36m%s\033[0m: ", caller);
            printf("Allocation failure (possibly out of memory, program should be terminated)\n");
            break;

        case EDD_ENULLPTR:
            printf("(\033[0;35mEDD_ENULLPTR\033[0m) ");
            printf("Error reported by \033[0;36m%s\033[0m: ", caller);
            printf("Unexpected NULL pointer passed as function argument\n");
            break;

        case EDD_EOOB:
            printf("(\033[0;35mEDD_EOOB\033[0m) ");
            printf("Error reported by \033[0;36m%s\033[0m: ", caller);
            printf("Search is out of bounds (for example: index is bigger or equal to size)\n");
            break;

        case EDD_ENOENT:
            printf("(\033[0;35mEDD_ENOENT\033[0m) ");
            printf("Error reported by \033[0;36m%s\033[0m: ", caller);
            printf("Member/Entity not found or doesn't exist\n");
            break;

        case EDD_SORT_EIDXCOLL:
            printf("(\033[0;35mEDD_SORT_EIDXCOLL\033[0m) ");
            printf("Error reported by \033[0;36m%s\033[0m: ", caller);
            printf("Indices passed for inplace operation generate overlapping ranges that should not be overlapping\n");
            break;

        case EDD_HEAP_EFULL:
            printf("(\033[0;35mEDD_HEAP_EFULL\033[0m) ");
            printf("Error reported by \033[0;36m%s\033[0m: ", caller);
            printf("The heap is full (size == capacity), any push/insertion attempt will be ignored\n");
            break;

        default:
            printf("(\033[0;35mEDD_???\033[0m) ");
            printf("Error reported by \033[0;36m%s\033[0m: ", caller);
            printf("Unknown error (if this is a function you created, ");
            printf("is recommended to use already existing errors in the EddError enum (defined in libedd_err.h)\n");
            break;
    }

    return;
}

bool has_error(EddError *err) {
    if (is_edderr_null(err, "has_error")) return true;

    if (*err != EDD_NOERR) {
        edd_debug(err, "has_error");
        return true;
    }

    return false;
}

bool errhandle_nullptr(EddError *err, const char *caller, void *ptr) {
    if (is_edderr_null(err, caller)) return true;

    if (ptr == NULL) {
        *err = EDD_ENULLPTR;
        edd_debug(err, caller);
        return true;
    }

    *err = EDD_NOERR;
    return false;
}

bool errhandle_oob(EddError *err, const char *caller, size_t size, size_t index) {
    if (is_edderr_null(err, caller)) return true;

    if (index >= size) {
        *err = EDD_EOOB;
        edd_debug(err, caller);
        return true;
    }

    *err = EDD_NOERR;
    return false;
}

bool errhandle_noent(EddError *err, const char *caller, size_t size) {
    if (is_edderr_null(err, caller)) return true;

    if (size == 0) {
        *err = EDD_ENOENT;
        edd_debug(err, caller);
        return true;
    }

    *err = EDD_NOERR;
    return false;
}

