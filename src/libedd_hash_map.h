#ifndef LIBEDD_HASH_MAP_H
#define LIBEDD_HASH_MAP_H

#include <string.h>

#include "libedd_err.h"
#include "libedd_cmd.h"

/* === General Definitions (structs, typedefs, etc) === */

typedef size_t (*HashFunction)(char *, size_t);

typedef struct hash_map_node {
    char *data;
    size_t length;
    struct hash_map_node* next;
} HashMapNode;

typedef struct hash_map {
    HashFunction hash;
    HashMapNode **table;
    size_t capacity;
    size_t size;
} HashMap;

/* ============= */

/* === Function Declarations === */

HashMapNode *hash_map_node_create(char *str, size_t length);
void hash_map_node_destroy(EddError *err, HashMapNode *node);

HashMap *hash_map_create(HashFunction hash, size_t capacity);
void hash_map_destroy(EddError *err, HashMap *hash_map);
void hash_map_print(EddError *err, HashMap *hash_map, FILE *output_file);
HashMapNode *hash_map_at(EddError *err, HashMap *hash_map, size_t hash);

bool hash_map_search(EddError *err, HashMap *hash_map, char *str, size_t length);
void hash_map_insert(EddError *err, HashMap *hash_map, char *str, size_t length);
void hash_map_remove(EddError *err, HashMap *hash_map, char *str, size_t length);

void hash_map_cmd(EddError *err, HashMap *hash_map, FILE *input_file, FILE *output_file, const char *cmd);

/* ============= */

#endif
