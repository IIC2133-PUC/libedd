#ifndef LIBEDD_CMD_H
#define LIBEDD_CMD_H

/* === CMD name for EDD functions === */

#define LIBEDD_CMDNAME_BUGGY_CALLS            "BUGGY-CALLS"

// -- SLL -- //

#define LIBEDD_CMDNAME_SLL_PRINT              "SLL-PRINT"
#define LIBEDD_CMDNAME_SLL_AT                 "SLL-AT"
#define LIBEDD_CMDNAME_SLL_PUSH               "SLL-PUSH"
#define LIBEDD_CMDNAME_SLL_PUSHLEFT           "SLL-PUSHLEFT"
#define LIBEDD_CMDNAME_SLL_ENQ                "SLL-ENQ"
#define LIBEDD_CMDNAME_SLL_ENQLEFT            "SLL-ENQLEFT"
#define LIBEDD_CMDNAME_SLL_INSERT             "SLL-INSERT"
#define LIBEDD_CMDNAME_SLL_POP                "SLL-POP"
#define LIBEDD_CMDNAME_SLL_DEQ                "SLL-DEQ"
#define LIBEDD_CMDNAME_SLL_REMOVE             "SLL-REMOVE"
#define LIBEDD_CMDNAME_SLL_REMOVE_BY_PTR      "SLL-REMOVE-BY-PTR"
#define LIBEDD_CMDNAME_SLL_REMOVE_BY_VAL      "SLL-REMOVE-BY-VAL"

// -- DLL -- //

#define LIBEDD_CMDNAME_DLL_PRINT              "DLL-PRINT"
#define LIBEDD_CMDNAME_DLL_AT                 "DLL-AT"
#define LIBEDD_CMDNAME_DLL_PUSH               "DLL-PUSH"
#define LIBEDD_CMDNAME_DLL_PUSHLEFT           "DLL-PUSHLEFT"
#define LIBEDD_CMDNAME_DLL_ENQ                "DLL-ENQ"
#define LIBEDD_CMDNAME_DLL_ENQLEFT            "DLL-ENQLEFT"
#define LIBEDD_CMDNAME_DLL_INSERT             "DLL-INSERT"
#define LIBEDD_CMDNAME_DLL_POP                "DLL-POP"
#define LIBEDD_CMDNAME_DLL_DEQ                "DLL-DEQ"
#define LIBEDD_CMDNAME_DLL_REMOVE             "DLL-REMOVE"
#define LIBEDD_CMDNAME_DLL_REMOVE_BY_PTR      "DLL-REMOVE-BY-PTR"
#define LIBEDD_CMDNAME_DLL_REMOVE_BY_VAL      "DLL-REMOVE-BY-VAL"
#define LIBEDD_CMDNAME_DLL_REVERSE            "DLL-REVERSE"

// -- GSLL -- //

#define LIBEDD_CMDNAME_GSLL_PRINT             "GSLL-PRINT"
#define LIBEDD_CMDNAME_GSLL_AT                "GSLL-AT"
#define LIBEDD_CMDNAME_GSLL_PUSH              "GSLL-PUSH"
#define LIBEDD_CMDNAME_GSLL_ENQ               "GSLL-ENQ"
#define LIBEDD_CMDNAME_GSLL_INSERT            "GSLL-INSERT"
#define LIBEDD_CMDNAME_GSLL_POP               "GSLL-POP"
#define LIBEDD_CMDNAME_GSLL_DEQ               "GSLL-DEQ"
#define LIBEDD_CMDNAME_GSLL_REMOVE            "GSLL-REMOVE"
#define LIBEDD_CMDNAME_GSLL_REMOVE_BY_VAL     "GSLL-REMOVE-BY-VAL"

// -- SORT -- //

#define LIBEDD_CMDNAME_SORT_ARR_MERGESORT     "SORT-ARR-MERGESORT"
#define LIBEDD_CMDNAME_SORT_SLL_MERGESORT     "SORT-SLL-MERGESORT"
#define LIBEDD_CMDNAME_SORT_DLL_MERGESORT     "SORT-DLL-MERGESORT"

// -- HEAP -- //

#define LIBEDD_CMDNAME_HEAP_PRINT             "HEAP-PRINT"
#define LIBEDD_CMDNAME_HEAP_PEEK              "HEAP-PEEK"
#define LIBEDD_CMDNAME_HEAP_PUSH              "HEAP-PUSH"
#define LIBEDD_CMDNAME_HEAP_POP               "HEAP-POP"

// -- BST -- //

#define LIBEDD_CMDNAME_BST_PRINT              "BST-PRINT"
#define LIBEDD_CMDNAME_BST_SEARCH             "BST-SEARCH"
#define LIBEDD_CMDNAME_BST_INSERT             "BST-INSERT"
#define LIBEDD_CMDNAME_BST_REMOVE             "BST-REMOVE"

// -- HASH MAP -- //

#define LIBEDD_CMDNAME_HASH_MAP_PRINT         "HASH-MAP-PRINT"
#define LIBEDD_CMDNAME_HASH_MAP_AT            "HASH-MAP-AT"
#define LIBEDD_CMDNAME_HASH_MAP_SEARCH        "HASH-MAP-SEARCH"
#define LIBEDD_CMDNAME_HASH_MAP_INSERT        "HASH-MAP-INSERT"
#define LIBEDD_CMDNAME_HASH_MAP_REMOVE        "HASH-MAP-REMOVE"

// -- GRAPH -- //

#define LIBEDD_CMDNAME_GRAPH_PRINT            "GRAPH-PRINT"
#define LIBEDD_CMDNAME_GRAPH_ID_IS_ADJACENT   "GRAPH-IS-ADJACENT"
#define LIBEDD_CMDNAME_GRAPH_ID_ADJ_LIST_SIZE "GRAPH-ADJ-LIST-SIZE"
#define LIBEDD_CMDNAME_GRAPH_ID_GET_NTH_EDGE  "GRAPH-GET-NTH-EDGE"
#define LIBEDD_CMDNAME_GRAPH_ID_GET_EDGE      "GRAPH-GET-EDGE"
#define LIBEDD_CMDNAME_GRAPH_ID_ADD_EDGE      "GRAPH-ADD-EDGE"
#define LIBEDD_CMDNAME_GRAPH_ID_REMOVE_EDGE   "GRAPH-REMOVE-EDGE"
#define LIBEDD_CMDNAME_GRAPH_ID_IS_MEMBER     "GRAPH-IS-MEMBER"
#define LIBEDD_CMDNAME_GRAPH_SIZE             "GRAPH-SIZE"
#define LIBEDD_CMDNAME_GRAPH_GET_NTH_VERTEX   "GRAPH-GET-NTH-VERTEX"
#define LIBEDD_CMDNAME_GRAPH_GET_VERTEX       "GRAPH-GET-VERTEX"
#define LIBEDD_CMDNAME_GRAPH_ADD_VERTEX       "GRAPH-ADD-VERTEX"
#define LIBEDD_CMDNAME_GRAPH_ID_REMOVE_VERTEX "GRAPH-REMOVE-VERTEX"

/* ============= */

/* === Messages for CMD functions === */

// -- SLL -- //

#define LIBEDD_CMDMSG_GOOD_SLL_AT                 "Node at index %zu is: %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_AT                  "Node at index %zu is: (nil)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_PUSH               "Pushed value %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_PUSH                "Pushing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_SLL_PUSHLEFT           "Left-pushed value %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_PUSHLEFT            "Left-pushing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_SLL_ENQ                "Enqueued value %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_ENQ                 "Enqueueing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_SLL_ENQLEFT            "Left-enqueued value %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_ENQLEFT             "Left-enqueueing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_SLL_INSERT             "Appended value %d at index %zu\n"
#define LIBEDD_CMDMSG_ERR_SLL_INSERT              "Failed to append value %d at index %zu\n"

#define LIBEDD_CMDMSG_GOOD_SLL_POP                "Removed node %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_POP                 "Nothing to remove (empty sll)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_DEQ                "Dequeued node %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_DEQ                 "Nothing to dequeue (empty sll)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_REMOVE             "Removed node %d at index %zu\n"
#define LIBEDD_CMDMSG_ERR_SLL_REMOVE              "Nothing to remove (empty sll or index out of range)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_REMOVE_BY_PTR      "Removed node %d by ptr\n"
#define LIBEDD_CMDMSG_ERR_SLL_REMOVE_BY_PTR       "Nothing to remove (empty sll or no match found)\n"

#define LIBEDD_CMDMSG_GOOD_SLL_REMOVE_BY_VAL      "Removed (first) node %d by val\n"
#define LIBEDD_CMDMSG_ERR_SLL_REMOVE_BY_VAL       "Nothing to remove (empty sll or no match found)\n"

// -- DLL -- //

#define LIBEDD_CMDMSG_GOOD_DLL_AT                 "Node at index %zu is: %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_AT                  "Node at index %zu is: (nil)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_PUSH               "Pushed value %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_PUSH                "Pushing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_DLL_PUSHLEFT           "Left-pushed value %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_PUSHLEFT            "Left-pushing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_DLL_ENQ                "Enqueued value %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_ENQ                 "Enqueueing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_DLL_ENQLEFT            "Left-enqueued value %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_ENQLEFT             "Left-enqueueing value %d failed\n"

#define LIBEDD_CMDMSG_GOOD_DLL_INSERT             "Appended value %d at index %zu\n"
#define LIBEDD_CMDMSG_ERR_DLL_INSERT              "Failed to append value %d at index %zu\n"

#define LIBEDD_CMDMSG_GOOD_DLL_POP                "Removed node %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_POP                 "Nothing to remove (empty dll)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_DEQ                "Dequeued node %d\n"
#define LIBEDD_CMDMSG_ERR_DLL_DEQ                 "Nothing to dequeue (empty dll)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_REMOVE             "Removed node %d at index %zu\n"
#define LIBEDD_CMDMSG_ERR_DLL_REMOVE              "Nothing to remove (empty dll or index out of range)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_REMOVE_BY_PTR      "Removed node %d by ptr\n"
#define LIBEDD_CMDMSG_ERR_DLL_REMOVE_BY_PTR       "Nothing to remove (empty dll or no match found)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_REMOVE_BY_VAL      "Removed (first) node %d by val\n"
#define LIBEDD_CMDMSG_ERR_DLL_REMOVE_BY_VAL       "Nothing to remove (empty dll or no match found)\n"

#define LIBEDD_CMDMSG_GOOD_DLL_REVERSE            "Reversed dll\n"
#define LIBEDD_CMDMSG_ERR_DLL_REVERSE             "Failed to reverse dll\n"

// -- GSLL -- //

#define LIBEDD_CMDMSG_GOOD_GSLL_AT                "Node at index %zu is: %p\n"
#define LIBEDD_CMDMSG_ERR_GSLL_AT                 "Node at index %zu is: (nil)\n"

#define LIBEDD_CMDMSG_GOOD_GSLL_PUSH              "Pushed value %p\n"
#define LIBEDD_CMDMSG_ERR_GSLL_PUSH               "Pushing value %p failed\n"

#define LIBEDD_CMDMSG_GOOD_GSLL_ENQ               "Enqueued value %p\n"
#define LIBEDD_CMDMSG_ERR_GSLL_ENQ                "Enqueueing value %p failed\n"

#define LIBEDD_CMDMSG_GOOD_GSLL_INSERT            "Appended value %p at index %zu\n"
#define LIBEDD_CMDMSG_ERR_GSLL_INSERT             "Failed to append value %p at index %zu\n"

#define LIBEDD_CMDMSG_GOOD_GSLL_POP               "Removed node %p\n"
#define LIBEDD_CMDMSG_ERR_GSLL_POP                "Nothing to remove (empty gsll)\n"

#define LIBEDD_CMDMSG_GOOD_GSLL_DEQ               "Dequeued node %p\n"
#define LIBEDD_CMDMSG_ERR_GSLL_DEQ                "Nothing to dequeue (empty gsll)\n"

#define LIBEDD_CMDMSG_GOOD_GSLL_REMOVE            "Removed node %p at index %zu\n"
#define LIBEDD_CMDMSG_ERR_GSLL_REMOVE             "Nothing to remove (empty gsll or index out of range)\n"

#define LIBEDD_CMDMSG_GOOD_GSLL_REMOVE_BY_VAL     "Removed (first) node %p by val\n"
#define LIBEDD_CMDMSG_ERR_GSLL_REMOVE_BY_VAL      "Nothing to remove (empty gsll or no match found)\n"

// -- SORT -- //

#define LIBEDD_CMDMSG_GOOD_SORT_ARR_MERGESORT     "Sorted array by mergesort\n"
#define LIBEDD_CMDMSG_ERR_SORT_ARR_MERGESORT      "Failed to sort array by mergesort\n"

#define LIBEDD_CMDMSG_GOOD_SORT_SLL_MERGESORT     "Sorted sll by mergesort\n"
#define LIBEDD_CMDMSG_ERR_SORT_SLL_MERGESORT      "Failed to sort sll by mergesort\n"

#define LIBEDD_CMDMSG_GOOD_SORT_DLL_MERGESORT     "Sorted dll by mergesort\n"
#define LIBEDD_CMDMSG_ERR_SORT_DLL_MERGESORT      "Failed to sort dll by mergesort\n"

// -- HEAP -- //

#define LIBEDD_CMDMSG_GOOD_HEAP_PEEK              "Top key is %d\n"
#define LIBEDD_CMDMSG_ERR_HEAP_PEEK               "Nothing to peek at (empty heap)\n"

#define LIBEDD_CMDMSG_GOOD_HEAP_PUSH              "Pushed key %d\n"
#define LIBEDD_CMDMSG_ERR_HEAP_PUSH               "Pushing key %d failed\n"

#define LIBEDD_CMDMSG_GOOD_HEAP_POP               "Removed key %d\n"
#define LIBEDD_CMDMSG_ERR_HEAP_POP                "Nothing to remove (empty heap)\n"

// -- BST -- //

#define LIBEDD_CMDMSG_GOOD_BST_SEARCH             "Found key %d inside the tree\n"
#define LIBEDD_CMDMSG_ERR_BST_SEARCH              "Key %d was not found inside the tree\n"

#define LIBEDD_CMDMSG_GOOD_BST_INSERT             "Pushed key %d\n"
#define LIBEDD_CMDMSG_ERR_BST_INSERT              "Pushing key %d failed (possibly due to it being a duplicate)\n"

#define LIBEDD_CMDMSG_GOOD_BST_REMOVE             "Removed key %d\n"
#define LIBEDD_CMDMSG_ERR_BST_REMOVE              "Failed to remove key %d (empty tree or no match found)\n"

// -- HASH MAP -- //

#define LIBEDD_CMDMSG_GOOD_HASH_MAP_AT            "Got index %zu of the hash map\n"
#define LIBEDD_CMDMSG_ERR_HASH_MAP_AT             "Index %zu not found in the hash map\n"

#define LIBEDD_CMDMSG_GOOD_HASH_MAP_SEARCH        "Value %s is inside the hash map\n"
#define LIBEDD_CMDMSG_ERR_HASH_MAP_SEARCH         "Value %s not found in the hash map\n"

#define LIBEDD_CMDMSG_GOOD_HASH_MAP_INSERT        "Inserted value %s in the hash map\n"
#define LIBEDD_CMDMSG_ERR_HASH_MAP_INSERT         "Inserting value %s failed (possibly oob hash value)\n"

#define LIBEDD_CMDMSG_GOOD_HASH_MAP_REMOVE        "Removed value %s from the hash map\n"
#define LIBEDD_CMDMSG_ERR_HASH_MAP_REMOVE         "Failed to remove value %s (possibly not found)\n"

// -- GRAPH -- //

#define LIBEDD_CMDMSG_GOOD_GRAPH_ID_IS_ADJACENT   "Vertices with IDs %zu and %zu are %s\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ID_IS_ADJACENT    "Failed to determine if vertices %zu and %zu are adjacent\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_ID_ADJ_LIST_SIZE "The adjacency list of the vertex with ID %zu has size %zu\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ID_ADJ_LIST_SIZE  "Failed to retrieve adjacency list size for vertex with ID %zu\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_ID_GET_NTH_EDGE  "The edge at index %zu of the adj. list for vertex with ID %zu is connected to vertex with ID %zu\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ID_GET_NTH_EDGE   "Failed to get edge at index %zu for vertex with ID %zu\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_ID_GET_EDGE      "The edge that connects the vertices with IDs %zu and %zu weights %d\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ID_GET_EDGE       "Failed to retrieve the edge between vertices with IDs %zu and %zu (probably doesn't exist)\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_ID_ADD_EDGE      "Added a new edge between vertices with IDs %zu and %zu, with weight %d\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ID_ADD_EDGE       "Failed to add new edge between vertices with IDs %zu and %zu (probably it already exists)\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_ID_REMOVE_EDGE   "Removed edge between vertices with IDs %zu and %zu, with weight %d\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ID_REMOVE_EDGE    "Failed to remove edge between vertices with IDs %zu and %zu\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_ID_IS_MEMBER     "Vertex with ID %zu %s to the graph\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ID_IS_MEMBER      "Failed to determine membership to the graph for vertex with ID %zu\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_SIZE             "The size of the vertices list of the graph is %zu\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_SIZE              "Failed to get the size of the vertices list for the graph\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_GET_NTH_VERTEX   "Found vertex with ID %zu at index %zu of the vertices list\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_GET_NTH_VERTEX    "Failed to retrieve a vertex at index %zu of the vertices list\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_GET_VERTEX       "Found vertex with ID %zu in the vertices list\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_GET_VERTEX        "Vertex with ID %zu not found in the vertices list\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_ADD_VERTEX       "Added a new vertex with key %d to the graph\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ADD_VERTEX        "Failed to add new vertex to the graph\n"

#define LIBEDD_CMDMSG_GOOD_GRAPH_ID_REMOVE_VERTEX "Removed vertex with ID %zu from the graph\n"
#define LIBEDD_CMDMSG_ERR_GRAPH_ID_REMOVE_VERTEX  "Failed to remove vertex with ID %zu from the graph\n"

/* ============= */

#endif
