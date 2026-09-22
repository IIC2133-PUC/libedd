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
    new_node->height = 1;

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

static int bst_node_avl_balance_factor(EddError *err, BstNode *node) {
    if (errhandle_nullptr(err, "bst_node_avl_balance_factor", node)) return 0;

    size_t left_height = node->left != NULL ? node->left->height : 0;
    size_t right_height = node->right != NULL ? node->right->height : 0;

    return right_height - left_height;
}

static void bst_node_update_height(EddError *err, BstNode *node) {
    if (errhandle_nullptr(err, "bst_node_update_height", node)) return;

    size_t left_height = node->left != NULL ? node->left->height : 0;
    size_t right_height = node->right != NULL ? node->right->height : 0;

    size_t max_height = left_height;
    if (left_height < right_height) {
        max_height = right_height;
    }

    node->height = 1 + max_height;

    return;
}

Bst *bst_create(MovementFunction move_to, bool avl_mode) {
    Bst *new_bst = malloc(sizeof(Bst));
    check_allocation(new_bst);

    move_to = (move_to == NULL) ? default_movement_function : move_to;

    new_bst->root = NULL;
    new_bst->size = 0;
    new_bst->move_to = move_to;
    new_bst->avl_mode = avl_mode;

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
        fprintf(output_file, "            ");
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
    fprintf(output_file, "> root    : ");
    if (bst->size == 0) {
        fprintf(output_file, "(nil)\n");
    } else {
        fprintf(output_file, "%d\n", bst->root->key);
    }
    fprintf(output_file, "> size    : %zu\n", bst->size);
    fprintf(output_file, "> avl_mode: %s\n", bst->avl_mode ? "true" : "false");
    fprintf(output_file, "> log     : ");

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

static void bst_substitute_nodes(EddError *err, Bst* bst, BstNode *old_node, BstNode *substitute) {
    const char *self = "bst_substitute_nodes";
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

static void bst_avl_rotate(EddError *err, BstNode *high_node, BstNode *low_node, bool left_rotation) {
    const char *self = "bst_avl_rotate";
    if (errhandle_nullptr(err, self, high_node)) return;
    if (errhandle_nullptr(err, self, low_node)) return;
    if ((left_rotation && high_node->right != low_node) || (!left_rotation && high_node->left != low_node)) {
        *err = EDD_BST_EILLROT;
        edd_debug(err, self);
        return;
    }

    if (left_rotation) {
        high_node->right = low_node->left;
        if (low_node->left != NULL) {
            low_node->left->parent = high_node;
        }
        low_node->left = high_node;
    } else {
        high_node->left = low_node->right;
        if (low_node->right != NULL) {
            low_node->right->parent = high_node;
        }
        low_node->right = high_node;
    }

    if (high_node->parent != NULL) {
        BstNode *root = high_node->parent;
        if (root->left == high_node) {
            root->left = low_node;
        } else if (root->right == high_node) {
            root->right = low_node;
        }
    }
    low_node->parent = high_node->parent;
    high_node->parent = low_node;

    return;
}

static void bst_avl_rebalance(EddError *err, Bst *bst, BstNode *node) {
    const char *self = "bst_avl_rebalance";
    if (errhandle_nullptr(err, self, bst)) return;
    if (errhandle_nullptr(err, self, node)) return;
    if (!bst->avl_mode) return;

    int balance_factor = 0;
    BstNode *current_node = node;
    while (current_node != NULL && !has_error(err)) {
        balance_factor = bst_node_avl_balance_factor(err, current_node);
        if (abs(balance_factor) >= 2) break;
        current_node = current_node->parent;
    }

    if (abs(balance_factor) < 2) return;

    BstNode *child_node = current_node->left;
    if (current_node->left == NULL ||
        (current_node->right != NULL &&
        current_node->right->height > current_node->left->height)) {
        child_node = current_node->right;
    }

    balance_factor = bst_node_avl_balance_factor(err, child_node);
    if (child_node == current_node->left && balance_factor <= 0) {
        bst_avl_rotate(err, current_node, child_node, false);
    } else if (child_node == current_node->left && balance_factor > 0) {
        bst_avl_rotate(err, child_node, child_node->right, true);
        bst_avl_rotate(err, current_node, child_node->parent, false);
        bst_node_update_height(err, child_node);
    } else if (child_node == current_node->right && balance_factor >= 0) {
        bst_avl_rotate(err, current_node, child_node, true);
    } else if (child_node == current_node->right && balance_factor < 0) {
        bst_avl_rotate(err, child_node, child_node->left, false);
        bst_avl_rotate(err, current_node, child_node->parent, true);
        bst_node_update_height(err, child_node);
    }

    if (current_node == bst->root) {
        bst->root = current_node->parent;
    }

    while (current_node != NULL && !has_error(err)) {
        bst_node_update_height(err, current_node);
        current_node = current_node->parent;
    }

    return;
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

    current_node = parent_node;
    while (current_node != NULL && !has_error(err)) {
        bst_node_update_height(err, current_node);
        current_node = current_node->parent;
    }

    if (bst->avl_mode) {
        bst_avl_rebalance(err, bst, new_node);
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

    BstNode *first_height_update = target_node->parent;

    if (target_node->left == NULL) {
        bst_substitute_nodes(err, bst, target_node, target_node->right);
    } else if (target_node->right == NULL) {
        bst_substitute_nodes(err, bst, target_node, target_node->left);
    } else {
        BstNode *target_successor = bst_successor(err, target_node);
        if (has_error(err)) return 0;

        first_height_update = target_successor;
        if (target_successor->parent != target_node) {
            first_height_update = target_successor->parent;
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

    BstNode *current_node = first_height_update;
    while (current_node != NULL && !has_error(err)) {
        bst_node_update_height(err, current_node);
        current_node = current_node->parent;
    }

    if (bst->avl_mode && first_height_update != NULL) {
        bst_avl_rebalance(err, bst, first_height_update);
        if (has_error(err)) return 0;
    }

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

        BstNode *temp_node = bst_node_create(0);
        Bst *temp_bst = bst_create(NULL, false);
        bst_node_destroy(NULL, temp_node);
        bst_node_destroy(err, NULL);
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
        bst_node_destroy(err, temp_node);
        bst_destroy(err, temp_bst);
    }
}
