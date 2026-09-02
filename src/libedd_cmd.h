#ifndef LIBEDD_CMD_H
#define LIBEDD_CMD_H

/* === CMD name for EDD functions === */

#define LIBEDD_CMDNAME_BUGGY_CALLS        "BUGGY-CALLS"

// -- SLL -- //

#define LIBEDD_CMDNAME_SLL_PRINT          "SLL-PRINT"
#define LIBEDD_CMDNAME_SLL_AT             "SLL-AT"
#define LIBEDD_CMDNAME_SLL_PUSH           "SLL-PUSH"
#define LIBEDD_CMDNAME_SLL_PUSHLEFT       "SLL-PUSHLEFT"
#define LIBEDD_CMDNAME_SLL_ENQ            "SLL-ENQ"
#define LIBEDD_CMDNAME_SLL_ENQLEFT        "SLL-ENQLEFT"
#define LIBEDD_CMDNAME_SLL_INSERT         "SLL-INSERT"
#define LIBEDD_CMDNAME_SLL_POP            "SLL-POP"
#define LIBEDD_CMDNAME_SLL_DEQ            "SLL-DEQ"
#define LIBEDD_CMDNAME_SLL_REMOVE         "SLL-REMOVE"
#define LIBEDD_CMDNAME_SLL_REMOVE_BY_PTR  "SLL-REMOVE-BY-PTR"
#define LIBEDD_CMDNAME_SLL_REMOVE_BY_VAL  "SLL-REMOVE-BY-VAL"

// -- DLL -- //

#define LIBEDD_CMDNAME_DLL_PRINT          "DLL-PRINT"
#define LIBEDD_CMDNAME_DLL_AT             "DLL-AT"
#define LIBEDD_CMDNAME_DLL_PUSH           "DLL-PUSH"
#define LIBEDD_CMDNAME_DLL_PUSHLEFT       "DLL-PUSHLEFT"
#define LIBEDD_CMDNAME_DLL_ENQ            "DLL-ENQ"
#define LIBEDD_CMDNAME_DLL_ENQLEFT        "DLL-ENQLEFT"
#define LIBEDD_CMDNAME_DLL_INSERT         "DLL-INSERT"
#define LIBEDD_CMDNAME_DLL_POP            "DLL-POP"
#define LIBEDD_CMDNAME_DLL_DEQ            "DLL-DEQ"
#define LIBEDD_CMDNAME_DLL_REMOVE         "DLL-REMOVE"
#define LIBEDD_CMDNAME_DLL_REMOVE_BY_PTR  "DLL-REMOVE-BY-PTR"
#define LIBEDD_CMDNAME_DLL_REMOVE_BY_VAL  "DLL-REMOVE-BY-VAL"
#define LIBEDD_CMDNAME_DLL_REVERSE        "DLL-REVERSE"

// -- SORT -- //

#define LIBEDD_CMDNAME_SORT_ARR_MERGESORT "SORT-ARR-MERGESORT"
#define LIBEDD_CMDNAME_SORT_SLL_MERGESORT "SORT-SLL-MERGESORT"
#define LIBEDD_CMDNAME_SORT_DLL_MERGESORT "SORT-DLL-MERGESORT"

// -- HEAP -- //

#define LIBEDD_CMDNAME_HEAP_PRINT         "HEAP-PRINT"
#define LIBEDD_CMDNAME_HEAP_PEEK          "HEAP-PEEK"
#define LIBEDD_CMDNAME_HEAP_PUSH          "HEAP-PUSH"
#define LIBEDD_CMDNAME_HEAP_POP           "HEAP-POP"

// -- BST -- //
//
#define LIBEDD_CMDNAME_BST_PRINT          "BST-PRINT"
#define LIBEDD_CMDNAME_BST_SEARCH         "BST-SEARCH"
#define LIBEDD_CMDNAME_BST_INSERT         "BST-INSERT"
#define LIBEDD_CMDNAME_BST_REMOVE         "BST-REMOVE"

/* ============= */

/* === Messages for CMD functions === */

// -- SLL -- //

#define LIBEDD_CMDMSG_GOOD_SLL_AT             "Node at index %zu is: %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_AT              "Node at index %zu is: (nil)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_PUSH           "Pushed value %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_PUSH            "Pushing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_SLL_PUSHLEFT       "Left-pushed value %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_PUSHLEFT        "Left-pushing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_SLL_ENQ            "Enqueued value %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_ENQ             "Enqueueing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_SLL_ENQLEFT        "Left-enqueued value %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_ENQLEFT         "Left-enqueueing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_SLL_INSERT         "Appended value %d at index %zu\n"
#define LIBEDD_CMDMSG_ERR_SLL_INSERT          "Failed to append value %d at index %zu\n"

#define LIBEDD_CMDMSG_GOOD_SLL_POP            "Removed node %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_POP             "Nothing to remove (empty sll)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_DEQ            "Dequeued node %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_DEQ             "Nothing to dequeue (empty sll)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_REMOVE         "Removed node %d at index %zu\n"
#define LIBEDD_CMDMSG_ERR_SLL_REMOVE          "Nothing to remove (empty sll or index out of range)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_REMOVE_BY_PTR  "Removed node %d by ptr\n"
#define LIBEDD_CMDMSG_ERR_SLL_REMOVE_BY_PTR   "Nothing to remove (empty sll or no match found)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_REMOVE_BY_VAL  "Removed (first) node %d by val\n"
#define LIBEDD_CMDMSG_ERR_SLL_REMOVE_BY_VAL   "Nothing to remove (empty sll or no match found)\n"

// -- DLL -- //

#define LIBEDD_CMDMSG_GOOD_DLL_AT             "Node at index %zu is: %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_AT              "Node at index %zu is: (nil)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_PUSH           "Pushed value %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_PUSH            "Pushing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_DLL_PUSHLEFT       "Left-pushed value %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_PUSHLEFT        "Left-pushing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_DLL_ENQ            "Enqueued value %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_ENQ             "Enqueueing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_DLL_ENQLEFT        "Left-enqueued value %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_ENQLEFT         "Left-enqueueing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_DLL_INSERT         "Appended value %d at index %zu\n"
#define LIBEDD_CMDMSG_ERR_DLL_INSERT          "Failed to append value %d at index %zu\n"

#define LIBEDD_CMDMSG_GOOD_DLL_POP            "Removed node %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_POP             "Nothing to remove (empty dll)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_DEQ            "Dequeued node %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_DEQ             "Nothing to dequeue (empty dll)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_REMOVE         "Removed node %d at index %zu\n"
#define LIBEDD_CMDMSG_ERR_DLL_REMOVE          "Nothing to remove (empty dll or index out of range)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_REMOVE_BY_PTR  "Removed node %d by ptr\n"
#define LIBEDD_CMDMSG_ERR_DLL_REMOVE_BY_PTR   "Nothing to remove (empty dll or no match found)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_REMOVE_BY_VAL  "Removed (first) node %d by val\n"
#define LIBEDD_CMDMSG_ERR_DLL_REMOVE_BY_VAL   "Nothing to remove (empty dll or no match found)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_REVERSE        "Reversed dll\n"
#define LIBEDD_CMDMSG_ERR_DLL_REVERSE         "Failed to reverse dll\n"

// -- SORT -- //

#define LIBEDD_CMDMSG_GOOD_SORT_ARR_MERGESORT "Sorted array by mergesort\n"
#define LIBEDD_CMDMSG_ERR_SORT_ARR_MERGESORT  "Failed to sort array by mergesort\n"

#define LIBEDD_CMDMSG_GOOD_SORT_SLL_MERGESORT "Sorted sll by mergesort\n"
#define LIBEDD_CMDMSG_ERR_SORT_SLL_MERGESORT  "Failed to sort sll by mergesort\n"

#define LIBEDD_CMDMSG_GOOD_SORT_DLL_MERGESORT "Sorted dll by mergesort\n"
#define LIBEDD_CMDMSG_ERR_SORT_DLL_MERGESORT  "Failed to sort dll by mergesort\n"

// -- HEAP -- //

#define LIBEDD_CMDMSG_GOOD_HEAP_PEEK          "Top key is %d\n"
#define LIBEDD_CMDMSG_ERR_HEAP_PEEK           "Nothing to peek at (empty heap)\n"

#define LIBEDD_CMDMSG_GOOD_HEAP_PUSH          "Pushed key %d\n"
#define LIBEDD_CMDMSG_ERR_HEAP_PUSH           "Pushing key %d failed\n"

#define LIBEDD_CMDMSG_GOOD_HEAP_POP           "Removed key %d\n"
#define LIBEDD_CMDMSG_ERR_HEAP_POP            "Nothing to remove (empty heap)\n"

// -- BST -- //

#define LIBEDD_CMDMSG_GOOD_BST_SEARCH         "Found key %d inside the tree\n"
#define LIBEDD_CMDMSG_ERR_BST_SEARCH          "Key %d was not found inside the tree\n"

#define LIBEDD_CMDMSG_GOOD_BST_INSERT         "Pushed key %d\n"
#define LIBEDD_CMDMSG_ERR_BST_INSERT          "Pushing key %d failed (possibly due to it being a duplicate)\n"

#define LIBEDD_CMDMSG_GOOD_BST_REMOVE         "Removed key %d\n"
#define LIBEDD_CMDMSG_ERR_BST_REMOVE          "Failed to remove key %d (empty tree or no match found)\n"

/* ============= */

#endif
