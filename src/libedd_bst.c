#include "libedd_bst.h"
#include "libedd_err.h"

static char default_movement_function(BstNode *node, int key) {
    if (key < node->key) {
        return 'l';
    } else if (key == node->key) {
        return 's';
    }

    return 'r';
}

BstNode *bst_node_create(int key) {
    BstNode *new_node = malloc(sizeof(BstNode));
    check_allocation(new_node);

    new_node->key = key;

    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

int bst_node_destroy(EddError *err, BstNode *node) {
    if (errhandle_nullptr(err, "bst_node_destroy", node)) return 0;

    int key = node->key;
    free(node);

    return key;
}

Bst *bst_create(MovementFunction move_to) {
    Bst *new_bst = malloc(sizeof(Bst));
    check_allocation(new_bst);

    move_to = (move_to == NULL) ? default_movement_function : move_to;

    new_bst->root = NULL;
    new_bst->size = 0;
    new_bst->move_to = move_to;

    return new_bst;
}

void bst_destroy(EddError *err, Bst *bst) {
    if (errhandle_nullptr(err, "bst_destroy", bst)) return;

    size_t capacity = (bst->size == 0) ? 1 : bst->size;
    BstNode *stack[capacity];

    stack[0] = bst->root;
    size_t size = 1;

    BstNode *current_node = bst->root;
    while (size > 0 && current_node != NULL) {
        current_node = stack[size - 1];
        size--;

        if (current_node->left != NULL) {
            stack[size] = current_node->left;
            size++;
        }

        if (current_node->right != NULL) {
            stack[size] = current_node->right;
            size++;
        }

        bst_node_destroy(err, current_node);
        if (has_error(err)) break;
    }

    free(bst);

    return;
}

static void bst_rec_tree_print(
    EddError *err,
    BstNode *node,
    char *stack,
    size_t stack_idx,
    char parent,
    const char *left_sep,
    const char *right_sep,
    FILE *output_file
) {
    if (has_error(err)) return;
    const char *self = "bst_rec_tree_print";
    if (errhandle_nullptr(err, self, node)) return;
    if (errhandle_nullptr(err, self, stack)) return;
    if (errhandle_oob(err, self, 64, stack_idx)) return;

    if (node->parent != NULL) {
        fprintf(output_file, "         ");
    }

    for (size_t i = 0; i < stack_idx; i++) {
        if (stack[i] == 'l') {
            fprintf(output_file, "%s", left_sep);
        } else if (stack[i] == 'r') {
            fprintf(output_file, "%s", right_sep);
        }
    }

    if (parent == 'l') {
        stack[stack_idx] = 'l';
        fprintf(output_file, "└─");
    } else if (parent == 'r') {
        stack[stack_idx] = 'r';
        fprintf(output_file, "├─");
    }

    fprintf(output_file, "[%d]\n", node->key);

    if (node->right != NULL) {
        bst_rec_tree_print(err, node->right, stack, stack_idx + 1, 'r', left_sep, right_sep, output_file);
    }

    if (node->left != NULL) {
        bst_rec_tree_print(err, node->left, stack, stack_idx + 1, 'l', left_sep, right_sep, output_file);
    }
}

void bst_print(EddError *err, Bst *bst, FILE *output_file) {
    const char *self = "bst_print";
    if (errhandle_nullptr(err, self, bst)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }

    fprintf(output_file, "Bst\n");
    fprintf(output_file, "> root : ");
    if (bst->size == 0) {
        fprintf(output_file, "(nil)\n");
    } else {
        fprintf(output_file, "%d\n", bst->root->key);
    }
    fprintf(output_file, "> size : %zu\n", bst->size);
    fprintf(output_file, "> log  : ");

    if (bst->size == 0) {
        fprintf(output_file, "\n");
        return;
    }

    char stack[64];
    for (size_t i = 0; i < 64; i++) {
        stack[i] = '\0';
    }
    const char *left_sep = "   ";
    const char *right_sep = "│  ";
    bst_rec_tree_print(err, bst->root, stack, 0, 't', left_sep, right_sep, output_file);

    return;
}

static BstNode *bst_min_from(EddError *err, BstNode *node) {
    if (errhandle_nullptr(err, "bst_min_from", node)) return NULL;

    BstNode *current_node = node;
    while (current_node->left != NULL) {
        current_node = current_node->left;
    }

    return current_node;
}

static BstNode *bst_max_from(EddError *err, BstNode *node) {
    if (errhandle_nullptr(err, "bst_min_from", node)) return NULL;

    BstNode *current_node = node;
    while (current_node->right != NULL) {
        current_node = current_node->right;
    }

    return current_node;
}

static BstNode *bst_predecessor(EddError *err, BstNode *node) {
    const char *self = "bst_predecessor";
    if (errhandle_nullptr(err, self, node)) return NULL;

    if (node->left != NULL) {
        return bst_max_from(err, node->left);
    }

    BstNode *parent_node = node->parent;
    BstNode *current_node = node;
    while (parent_node != NULL && current_node == parent_node->left) {
        current_node = parent_node;
        parent_node = parent_node->parent;
    }

    if (parent_node == NULL) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
    }

    return parent_node;
}

static BstNode *bst_successor(EddError *err, BstNode *node) {
    const char *self = "bst_successor";
    if (errhandle_nullptr(err, self, node)) return NULL;

    if (node->right != NULL) {
        return bst_min_from(err, node->right);
    }

    BstNode *parent_node = node->parent;
    BstNode *current_node = node;
    while (parent_node != NULL && current_node == parent_node->right) {
        current_node = parent_node;
        parent_node = parent_node->parent;
    }

    if (parent_node == NULL) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
    }

    return parent_node;
}

BstNode *bst_search(EddError *err, Bst *bst, int key) {
    const char *self = "bst_search";
    if (errhandle_nullptr(err, self, bst)) return NULL;
    if (errhandle_noent(err, self, bst->size)) return NULL;

    char move = '\0';
    bool found = false;
    BstNode *current_node = bst->root;
    while (!found && current_node != NULL) {
        if (current_node->key == key) {
            found = true;
            continue;
        }

        move = bst->move_to(current_node, key);
        if (errhandle_movstop(err, self, move)) return NULL;

        if (move == 'l') {
            current_node = current_node->left;
        } else if (move == 'r') {
            current_node = current_node->right;
        }
    }

    if (!found) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return NULL;
    }

    return current_node;
}

void bst_insert(EddError *err, Bst *bst, int key) {
    const char *self = "bst_insert";
    if (errhandle_nullptr(err, self, bst)) return;

    BstNode *parent_node = NULL;
    BstNode *current_node = bst->root;
    char move = '\0';
    while (current_node != NULL) {
        parent_node = current_node;

        move = bst->move_to(current_node, key);
        if (errhandle_movstop(err, self, move)) return;

        if (move == 'l') {
            current_node = current_node->left;
        } else if (move == 'r') {
            current_node = current_node->right;
        }
    }

    BstNode *new_node = bst_node_create(key);
    new_node->parent = parent_node;
    bst->size++;

    if (parent_node == NULL) {
        bst->root = new_node;
        return;
    }

    move = bst->move_to(parent_node, key);
    if (move == 'l') {
        parent_node->left = new_node;
    } else if (move == 'r'){
        parent_node->right = new_node;
    }

    return;
}

static void bst_substitute_nodes(EddError *err, Bst* bst, BstNode *old_node, BstNode *substitute) {
    const char *self = "bst_swap_nodes";
    if (errhandle_nullptr(err, self, bst)) return;
    if (errhandle_nullptr(err, self, old_node)) return;

    if (old_node->parent == NULL) {
        bst->root = substitute;
    } else if (old_node == old_node->parent->left) {
        old_node->parent->left = substitute;
    } else {
        old_node->parent->right = substitute;
    }

    if (substitute != NULL) {
        substitute->parent = old_node->parent;
    }

    return;
}

int bst_remove(EddError *err, Bst *bst, int key) {
    const char *self = "bst_remove";
    if (errhandle_nullptr(err, self, bst)) return 0;

    BstNode *target_node = bst_search(err, bst, key);
    if (*err != EDD_NOERR) {
        edd_debug(err, self);
        return 0;
    }

    if (target_node->left == NULL) {
        bst_substitute_nodes(err, bst, target_node, target_node->right);
    } else if (target_node->right == NULL) {
        bst_substitute_nodes(err, bst, target_node, target_node->left);
    } else {
        BstNode *target_successor = bst_successor(err, target_node);
        if (has_error(err)) return 0;

        if (target_successor->parent != target_node) {
            bst_substitute_nodes(err, bst, target_successor, target_successor->right);
            target_successor->right = target_node->right;
            target_successor->right->parent = target_successor;
        }

        bst_substitute_nodes(err, bst, target_node, target_successor);
        target_successor->left = target_node->left;
        target_successor->left->parent = target_successor;
    }

    bst_node_destroy(err, target_node);
    bst->size--;
    if (has_error(err)) return 0;

    return key;
}

void bst_cmd(EddError *err, Bst *bst, FILE *input_file, FILE *output_file, const char *cmd) {
    const char *self = "bst_cmd";
    if (errhandle_nullptr(err, self, bst)) return;
    if (errhandle_nullptr(err, self, input_file)) return;
    if (errhandle_nullptr(err, self, (void*)cmd)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }

    int key;

    if (!strcmp(cmd, LIBEDD_CMDNAME_BST_PRINT)) {
        bst_print(err, bst, output_file);
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_BST_SEARCH)) {
        fscanf(input_file, " %d", &key);
        bst_search(err, bst, key);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_BST_SEARCH, key);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_BST_SEARCH, key);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_BST_INSERT)) {
        fscanf(input_file, " %d", &key);
        bst_insert(err, bst, key);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_BST_INSERT, key);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_BST_INSERT, key);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_BST_REMOVE)) {
        fscanf(input_file, " %d", &key);
        bst_remove(err, bst, key);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_BST_REMOVE, key);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_BST_REMOVE, key);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_BUGGY_CALLS)) {
        EDD_DEBUG = true;

        Bst *temp_bst = bst_create(NULL);

        bst_destroy(NULL, temp_bst);
        bst_destroy(err, NULL);
        bst_print(NULL, temp_bst, output_file);
        bst_print(err, NULL, output_file);
        bst_search(NULL, temp_bst, 0);
        bst_search(err, NULL, 0);
        bst_insert(NULL, temp_bst, 0);
        bst_insert(err, NULL, 0);
        bst_remove(NULL, temp_bst, 0);
        bst_remove(err, NULL, 0);

        bst_print(err, temp_bst, output_file);
        bst_destroy(err, temp_bst);
    }
}
