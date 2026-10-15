#include "libedd_hash_map.h"
#include "libedd_cmd.h"
#include "libedd_err.h"

static size_t default_hash_function(char *str, size_t length) {
    return length % 64;
}

HashMapNode *hash_map_node_create(char *str, size_t length) {
    HashMapNode *new_node = malloc(sizeof(HashMapNode));
    check_allocation(new_node);

    char *copy = calloc(length + 1, sizeof(char));
    check_allocation(copy);
    for (size_t i = 0; i < length; i++) {
        copy[i] = str[i];
    }

    new_node->data = copy;
    new_node->length = length;
    new_node->next = NULL;

    return new_node;
}

void hash_map_node_destroy(EddError *err, HashMapNode *node) {
    if (errhandle_nullptr(err, "hash_map_node_destroy", node)) return;

    free(node->data);
    free(node);

    return;
}

HashMap *hash_map_create(HashFunction hash, size_t capacity) {
    HashMap *new_hash_map = malloc(sizeof(HashMap));
    check_allocation(new_hash_map);

    new_hash_map->hash = hash == NULL ? default_hash_function : hash;
    new_hash_map->capacity = capacity > 0 ? capacity : 64;
    new_hash_map->size = 0;
    new_hash_map->table = calloc(new_hash_map->capacity, sizeof(HashMapNode*));
    check_allocation(new_hash_map->table);

    return new_hash_map;
}

void hash_map_destroy(EddError *err, HashMap *hash_map) {
    const char *self = "hash_map_destroy";
    if (errhandle_nullptr(err, self, hash_map)) return;
    if (errhandle_nullptr(err, self, hash_map->table)) return;

    HashMapNode *curr_node;
    HashMapNode *next_node;
    for (size_t i = 0; i < hash_map->capacity; i++) {
        curr_node = hash_map->table[i];
        while (curr_node != NULL && !has_error(err)) {
            next_node = curr_node->next;
            hash_map_node_destroy(err, curr_node);
            curr_node = next_node;
        }
    }

    free(hash_map->table);
    free(hash_map);

    return;
}

void hash_map_print(EddError *err, HashMap *hash_map, FILE *output_file) {
    const char *self = "hash_map_print";
    if (errhandle_nullptr(err, self, hash_map)) return;
    if (errhandle_nullptr(err, self, hash_map->table)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }

    fprintf(output_file, "HashMap\n> capacity: %zu\n> size    : %zu\n> log     : ",
            hash_map->capacity, hash_map->size);
    if (hash_map->size == 0) {
        fprintf(output_file, "(empty)\n");
        return;
    }

    fprintf(output_file, "\n");
    HashMapNode *node;
    for (size_t i = 0; i < hash_map->capacity; i++) {
        node = hash_map->table[i];
        if (node == NULL) continue;

        fprintf(output_file, "[%zu]: ", i);
        while (node != NULL) {
            fprintf(output_file, "%s -> ", node->data);
            node = node->next;
        }
        fprintf(output_file, "\n");
    }

    return;
}

HashMapNode *hash_map_at(EddError *err, HashMap *hash_map, size_t hash) {
    const char *self = "hash_map_at";
    if (errhandle_nullptr(err, self, hash_map)) return NULL;
    if (errhandle_nullptr(err, self, hash_map->table)) return NULL;
    if (errhandle_oob(err, self, hash_map->capacity, hash)) return NULL;

    return hash_map->table[hash];
}

bool hash_map_search(EddError *err, HashMap *hash_map, char *str, size_t length) {
    const char *self = "hash_map_search";
    if (errhandle_nullptr(err, self, hash_map)) return false;
    if (errhandle_nullptr(err, self, hash_map->table)) return false;
    if (errhandle_nullptr(err, self, str)) return false;

    size_t hash = hash_map->hash(str, length);
    if (errhandle_oob(err, self, hash_map->capacity, hash)) return false;

    HashMapNode *node = hash_map->table[hash];
    bool found = false;
    while (node != NULL && !found) {
        if (node->length == length && !strncmp(str, node->data, node->length)) {
            found = true;
            continue;
        }

        node = node->next;
    }

    return found;
}

void hash_map_insert(EddError *err, HashMap *hash_map, char *str, size_t length) {
    const char *self = "hash_map_insert";
    if (errhandle_nullptr(err, self, hash_map)) return;
    if (errhandle_nullptr(err, self, hash_map->table)) return;
    if (errhandle_nullptr(err, self, str)) return;

    size_t hash = hash_map->hash(str, length);
    if (errhandle_oob(err, self, hash_map->capacity, hash)) return;

    HashMapNode *new_node = hash_map_node_create(str, length);
    HashMapNode *node = hash_map->table[hash];
    if (node == NULL) {
        hash_map->table[hash] = new_node;
        hash_map->size++;
        return;
    }

    while (node->next != NULL) {
        node = node->next;
    }
    node->next = new_node;

    hash_map->size++;

    return;
}

void hash_map_remove(EddError *err, HashMap *hash_map, char *str, size_t length) {
    const char *self = "hash_map_remove";
    if (errhandle_nullptr(err, self, hash_map)) return;
    if (errhandle_nullptr(err, self, hash_map->table)) return;
    if (errhandle_nullptr(err, self, str)) return;

    size_t hash = hash_map->hash(str, length);
    if (errhandle_oob(err, self, hash_map->capacity, hash)) return;

    HashMapNode *prev_node = NULL;
    HashMapNode *curr_node = hash_map->table[hash];
    bool found = false;
    while (curr_node != NULL && !found) {
        if (curr_node->length == length && !strncmp(str, curr_node->data, curr_node->length)) {
            found = true;
            continue;
        }

        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if (!found) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return;
    }

    if (prev_node == NULL) {
        hash_map->table[hash] = curr_node->next;
    } else {
        prev_node->next = curr_node->next;
    }

    hash_map->size--;
    hash_map_node_destroy(err, curr_node);

    return;
}

void hash_map_cmd(EddError *err, HashMap *hash_map, FILE *input_file, FILE *output_file, const char *cmd) {
    const char *self = "hash_map_cmd";
    if (errhandle_nullptr(err, self, hash_map)) return;
    if (errhandle_nullptr(err, self, hash_map->table)) return;
    if (errhandle_nullptr(err, self, input_file)) return;
    if (errhandle_nullptr(err, self, (void*)cmd)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }

    char *str;
    size_t length;
    size_t hash;

    if (!strcmp(cmd, LIBEDD_CMDNAME_HASH_MAP_PRINT)) {
        hash_map_print(err, hash_map, output_file);
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_HASH_MAP_AT)) {
        fscanf(input_file, " %zu", &hash);

        hash_map_at(err, hash_map, hash);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_HASH_MAP_AT, hash);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_HASH_MAP_AT, hash);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_HASH_MAP_SEARCH)) {
        fscanf(input_file, " %zu", &length);
        str = calloc(length + 1, sizeof(char));
        fscanf(input_file, " %s", str);

        bool found = hash_map_search(err, hash_map, str, length);
        if (has_error(err) || !found) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_HASH_MAP_SEARCH, str);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_HASH_MAP_SEARCH, str);
        }

        free(str);
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_HASH_MAP_INSERT)) {
        fscanf(input_file, " %zu", &length);
        str = calloc(length + 1, sizeof(char));
        fscanf(input_file, " %s", str);

        hash_map_insert(err, hash_map, str, length);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_HASH_MAP_INSERT, str);
            free(str);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_HASH_MAP_INSERT, str);
        }

        free(str);
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_HASH_MAP_REMOVE)) {
        fscanf(input_file, " %zu", &length);
        str = calloc(length + 1, sizeof(char));
        fscanf(input_file, " %s", str);

        hash_map_remove(err, hash_map, str, length);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_HASH_MAP_REMOVE, str);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_HASH_MAP_REMOVE, str);
        }

        free(str);
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_BUGGY_CALLS)) {
        EDD_DEBUG = true;

        HashMap *temp_hash_map = hash_map_create(NULL, 64);
        char *str = "hello";

        hash_map_destroy(NULL, temp_hash_map);
        hash_map_destroy(err, NULL);
        hash_map_print(NULL, temp_hash_map, output_file);
        hash_map_print(err, NULL, output_file);
        hash_map_at(NULL, temp_hash_map, 0);
        hash_map_at(err, NULL, 0);
        hash_map_search(NULL, temp_hash_map, str, 6);
        hash_map_search(err, NULL, str, 6);
        hash_map_search(err, temp_hash_map, NULL, 6);
        hash_map_insert(NULL, temp_hash_map, str, 6);
        hash_map_insert(err, NULL, str, 6);
        hash_map_insert(err, temp_hash_map, NULL, 6);
        hash_map_remove(NULL, temp_hash_map, str, 6);
        hash_map_remove(err, NULL, str, 6);
        hash_map_remove(err, temp_hash_map, NULL, 6);

        hash_map_print(err, temp_hash_map, output_file);
        hash_map_destroy(err, temp_hash_map);
    }
}
