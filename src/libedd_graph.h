#ifndef LIBEDD_GRAPH_H
#define LIBEDD_GRAPH_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "libedd_err.h"
#include "libedd_cmd.h"
#include "libedd_gsll.h"

/* === General Definitions (structs, typedefs, etc) === */

typedef struct graph_edge {
    int weight;
    struct graph_vertex *vertex;
} Edge;

typedef struct graph_vertex {
    size_t id;
    int key;
    GSll *adj_list;
} Vertex;

typedef struct graph {
    size_t seq;
    GSll *vertices;
    bool is_directed;
} Graph;

/* ============= */

/* === Function Declarations === */

Graph *graph_create(bool is_directed);
void graph_destroy(EddError *err, Graph *graph);
void graph_print(EddError *err, Graph *graph, FILE *output_file);

bool graph_is_adjacent(EddError *err, Vertex *vertex, Vertex *neighbor);
size_t graph_adj_list_size(EddError *err, Vertex *vertex);
Edge *graph_get_nth_edge(EddError *err, Vertex *vertex, size_t index);
Edge *graph_get_edge(EddError *err, Vertex *vertex, Vertex *neighbor);
Edge *graph_add_edge(EddError *err, Graph *graph, Vertex *vertex, Vertex *neighbor, int weight);
int graph_remove_edge(EddError *err, Graph *graph, Vertex *vertex, Vertex *neighbor);

bool graph_is_member(EddError *err, Graph *graph, Vertex *vertex);
size_t graph_size(EddError *err, Graph *graph);
Vertex *graph_get_nth_vertex(EddError *err, Graph *graph, size_t index);
Vertex *graph_get_vertex(EddError *err, Graph *graph, size_t vertex_id);
Vertex *graph_add_vertex(EddError *err, Graph *graph, int key);
int graph_remove_vertex(EddError *err, Graph *graph, Vertex *vertex);

bool graph_id_is_adjacent(EddError *err, Graph *graph, size_t vertex_id, size_t neighbor_id);
size_t graph_id_adj_list_size(EddError *err, Graph *graph, size_t vertex_id);
Edge *graph_id_get_nth_edge(EddError *err, Graph *graph, size_t vertex_id, size_t index);
Edge *graph_id_get_edge(EddError *err, Graph *graph, size_t vertex_id, size_t neighbor_id);
Edge *graph_id_add_edge(EddError *err, Graph *graph, size_t vertex_id, size_t neighbor_id, int weight);
int graph_id_remove_edge(EddError *err, Graph *graph, size_t vertex_id, size_t neighbor_id);

bool graph_id_is_member(EddError *err, Graph *graph, size_t vertex_id);
int graph_id_remove_vertex(EddError *err, Graph *graph, size_t vertex_id);

void graph_cmd(EddError *err, Graph *graph, FILE *input_file, FILE *output_file, const char *cmd);

/* ============= */

#endif
