#include "libedd_graph.h"
#include "libedd_cmd.h"
#include "libedd_err.h"

static Edge *graph_edge_create(EddError *err, Vertex *vertex, int weight) {
    if (errhandle_nullptr(err, "graph_edge_create", vertex)) return NULL;

    Edge *new_edge = malloc(sizeof(Edge));
    check_allocation(new_edge);

    new_edge->weight = weight;
    new_edge->vertex = vertex;

    return new_edge;
}

static void graph_edge_destroy(void *edge) {
    if (edge != NULL) {
        free(edge);
    }
}

static Vertex *graph_vertex_create(size_t id, int key) {
    Vertex *new_vertex = malloc(sizeof(Vertex));
    check_allocation(new_vertex);

    new_vertex->id = id;
    new_vertex->key = key;
    new_vertex->adj_list = gsll_create(true, graph_edge_destroy);

    return new_vertex;
}

static void graph_vertex_destroy(void *vertex) {
    EddError err = EDD_NOERR;
    gsll_destroy(&err, ((Vertex *)vertex)->adj_list);
    if (!has_error(&err)) {
        free(vertex);
    }
}

Graph *graph_create(bool is_directed) {
    Graph *new_graph = malloc(sizeof(Graph));
    check_allocation(new_graph);

    new_graph->seq = 0;
    new_graph->vertices = gsll_create(true, graph_vertex_destroy);
    new_graph->is_directed = is_directed;

    return new_graph;
}

void graph_destroy(EddError *err, Graph *graph) {
    if (errhandle_nullptr(err, "graph_destroy", graph)) return;

    gsll_destroy(err, graph->vertices);
    free(graph);
}

void graph_print(EddError *err, Graph *graph, FILE *output_file) {
    if (errhandle_nullptr(err, "graph_print", graph)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }

    fprintf(output_file, "Graph\n> seq        : %zu\n> is_directed: %s\n> log        : ",
            graph->seq, graph->is_directed ? "true" : "false");

    if (graph->vertices->size == 0) {
        fprintf(output_file, "(nil)\n");
        return;
    }

    fprintf(output_file, "\n~~~ size: %zu (format: (weight)[id | key]) ~~~\n", graph->vertices->size);

    GSllNode *curr = graph->vertices->head;
    Vertex *curr_vertex;
    while (curr != NULL) {
        curr_vertex = (Vertex *)(curr->data);
        fprintf(output_file, "[%zu | %d]: ", curr_vertex->id, curr_vertex->key);
        if (curr_vertex->adj_list->size == 0) {
            fprintf(output_file, "(nil)\n");
            curr = curr->next;
            continue;
        }

        GSllNode *subcurr = curr_vertex->adj_list->head;
        Edge *curr_edge;
        while (subcurr != NULL) {
            curr_edge = (Edge *)(subcurr->data);
            fprintf(output_file, "(%d)[%zu | %d] -> ",
                    curr_edge->weight, curr_edge->vertex->id, curr_edge->vertex->key);
            subcurr = subcurr->next;
        }
        fprintf(output_file, "\n");

        curr = curr->next;
    }
}

bool graph_is_adjacent(EddError *err, Vertex *vertex, Vertex *neighbor) {
    const char *self = "graph_is_adjacent";
    if (errhandle_nullptr(err, self, vertex)) return false;
    if (errhandle_nullptr(err, self, neighbor)) return false;

    bool is_adjacent = false;
    GSllNode *curr = vertex->adj_list->head;
    Edge *edge;
    while (curr != NULL && !is_adjacent) {
        edge = (Edge *)(curr->data);
        if (edge->vertex == neighbor) {
            is_adjacent = true;
            continue;
        }

        curr = curr->next;
    }

    return is_adjacent;
}

size_t graph_adj_list_size(EddError *err, Vertex *vertex) {
    const char *self = "graph_adj_list_size";
    if (errhandle_nullptr(err, self, vertex)) return 0;

    return vertex->adj_list->size;
}

Edge *graph_get_nth_edge(EddError *err, Vertex *vertex, size_t index) {
    const char *self = "graph_get_nth_edge";
    if (errhandle_nullptr(err, self, vertex)) return NULL;
    if (errhandle_oob(err, self, vertex->adj_list->size, index)) return NULL;

    GSllNode *curr = vertex->adj_list->head;
    for (size_t i = 0; i < index; i++) {
        curr = curr->next;
    }

    return (Edge *)(curr->data);
}

Edge *graph_get_edge(EddError *err, Vertex *vertex, Vertex *neighbor) {
    const char *self = "graph_get_edge";
    if (errhandle_nullptr(err, self, vertex)) return NULL;
    if (errhandle_nullptr(err, self, neighbor)) return NULL;

    bool is_adjacent = false;
    GSllNode *curr = vertex->adj_list->head;
    Edge *edge;
    while (curr != NULL && !is_adjacent) {
        edge = (Edge *)(curr->data);
        if (edge->vertex == neighbor) {
            is_adjacent = true;
            continue;
        }

        curr = curr->next;
    }

    if (!is_adjacent) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return NULL;
    }

    return edge;
}

Edge *graph_add_edge(EddError *err, Graph *graph, Vertex *vertex, Vertex *neighbor, int weight) {
    const char *self = "graph_add_edge";
    if (errhandle_nullptr(err, self, graph)) return NULL;
    if (errhandle_nullptr(err, self, vertex)) return NULL;
    if (errhandle_nullptr(err, self, neighbor)) return NULL;

    if (graph_is_adjacent(err, vertex, neighbor)) {
        *err = EDD_GRAPH_EEDUP;
        edd_debug(err, self);
        return NULL;
    }

    Edge *new_edge = graph_edge_create(err, neighbor, weight);
    gsll_push(err, vertex->adj_list, new_edge);

    if (!graph->is_directed) {
        Edge *mirror_edge = graph_edge_create(err, vertex, weight);
        gsll_push(err, neighbor->adj_list, mirror_edge);
    }

    return new_edge;
}

int graph_remove_edge(EddError *err, Graph *graph, Vertex *vertex, Vertex *neighbor) {
    const char *self = "graph_remove_edge";
    if (errhandle_nullptr(err, self, graph)) return 0;
    if (errhandle_nullptr(err, self, vertex)) return 0;
    if (errhandle_nullptr(err, self, neighbor)) return 0;

    if (!graph_is_adjacent(err, vertex, neighbor)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    Edge *edge = graph_get_edge(err, vertex, neighbor);
    int removed_weight = edge->weight;
    gsll_remove_by_val(err, vertex->adj_list, edge);

    if (!graph->is_directed) {
        Edge *mirror_edge = graph_get_edge(err, neighbor, vertex);
        gsll_remove_by_val(err, neighbor->adj_list, mirror_edge);
    }

    return removed_weight;
}

bool graph_is_member(EddError *err, Graph *graph, Vertex *vertex) {
    const char *self = "graph_is_member";
    if (errhandle_nullptr(err, self, graph)) return false;
    if (errhandle_nullptr(err, self, vertex)) return false;

    bool is_member = false;
    GSllNode *curr = graph->vertices->head;
    Vertex *vtx;
    while (curr != NULL && !is_member) {
        vtx = (Vertex *)(curr->data);
        if (vtx == vertex) {
            is_member = true;
            continue;
        }

        curr = curr->next;
    }

    return is_member;
}

size_t graph_size(EddError *err, Graph *graph) {
    if (errhandle_nullptr(err, "graph_size", graph)) return 0;

    return graph->vertices->size;
}

Vertex *graph_get_nth_vertex(EddError *err, Graph *graph, size_t index) {
    const char *self = "graph_get_nth_vertex";
    if (errhandle_nullptr(err, self, graph)) return NULL;
    if (errhandle_oob(err, self, graph->vertices->size, index)) return NULL;

    GSllNode *curr = graph->vertices->head;
    for (size_t i = 0; i < index; i++) {
        curr = curr->next;
    }

    return (Vertex *)(curr->data);
}

Vertex *graph_get_vertex(EddError *err, Graph *graph, size_t vertex_id) {
    const char *self = "graph_get_vertex";
    if (errhandle_nullptr(err, self, graph)) return NULL;
    if (errhandle_oob(err, self, graph->seq, vertex_id)) return NULL;

    bool found = false;
    GSllNode *curr = graph->vertices->head;
    Vertex *vertex;
    while (curr != NULL && !found) {
        vertex = (Vertex *)(curr->data);
        if (vertex->id == vertex_id) {
            found = true;
            continue;
        }

        curr = curr->next;
    }

    if (!found) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return NULL;
    }

    return vertex;
}

Vertex *graph_add_vertex(EddError *err, Graph *graph, int key) {
    if (errhandle_nullptr(err, "graph_add_vertex", graph)) return NULL;

    Vertex *new_vertex = graph_vertex_create(graph->seq, key);
    gsll_push(err, graph->vertices, new_vertex);
    graph->seq++;

    return new_vertex;
}

int graph_remove_vertex(EddError *err, Graph *graph, Vertex *vertex) {
    const char *self = "graph_remove_vertex";
    if (errhandle_nullptr(err, self, graph)) return 0;
    if (errhandle_nullptr(err, self, vertex)) return 0;

    if (!graph_is_member(err, graph, vertex)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    int removed_key = vertex->key;

    GSllNode *curr = graph->vertices->head;
    Vertex *curr_vertex;
    GSllNode *subcurr;
    GSllNode *subnext;
    while (curr != NULL) {
        curr_vertex = (Vertex *)(curr->data);
        if (curr_vertex == vertex) {
            curr = curr->next;
            continue;
        }

        subcurr = curr_vertex->adj_list->head;
        subnext = NULL;
        while (subcurr != NULL) {
            subnext = subcurr->next;
            if (((Edge *)(subcurr->data))->vertex == vertex) {
                graph_remove_edge(err, graph, curr_vertex, vertex);
            }
            subcurr = subnext;
        }

        curr = curr->next;
    }

    gsll_remove_by_val(err, graph->vertices, vertex);

    return removed_key;
}

bool graph_id_is_adjacent(EddError *err, Graph *graph, size_t vertex_id, size_t neighbor_id) {
    const char *self = "graph_id_is_adjacent";
    if (errhandle_nullptr(err, self, graph)) return false;

    EddError cpy_err = EDD_NOERR;
    Vertex *vertex = graph_get_vertex(err, graph, vertex_id);
    Vertex *neighbor = graph_get_vertex(err, graph, neighbor_id);
    if (has_error(err) || has_error(&cpy_err)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return false;
    }

    return graph_is_adjacent(err, vertex, neighbor);
}

size_t graph_id_adj_list_size(EddError *err, Graph *graph, size_t vertex_id) {
    const char *self = "graph_id_adj_list_size";
    if (errhandle_nullptr(err, self, graph)) return 0;

    Vertex *vertex = graph_get_vertex(err, graph, vertex_id);
    if (has_error(err)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    return graph_adj_list_size(err, vertex);
}

Edge *graph_id_get_nth_edge(EddError *err, Graph *graph, size_t vertex_id, size_t index) {
    const char *self = "graph_id_get_nth_edge";
    if (errhandle_nullptr(err, self, graph)) return NULL;

    Vertex *vertex = graph_get_vertex(err, graph, vertex_id);
    if (has_error(err)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return NULL;
    }

    return graph_get_nth_edge(err, vertex, index);
}

Edge *graph_id_get_edge(EddError *err, Graph *graph, size_t vertex_id, size_t neighbor_id) {
    const char *self = "graph_id_get_edge";
    if (errhandle_nullptr(err, self, graph)) return NULL;

    EddError cpy_err = EDD_NOERR;
    Vertex *vertex = graph_get_vertex(err, graph, vertex_id);
    Vertex *neighbor = graph_get_vertex(err, graph, neighbor_id);
    if (has_error(err) || has_error(&cpy_err)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return NULL;
    }

    return graph_get_edge(err, vertex, neighbor);
}

Edge *graph_id_add_edge(EddError *err, Graph *graph, size_t vertex_id, size_t neighbor_id, int weight) {
    const char *self = "graph_id_add_edge";
    if (errhandle_nullptr(err, self, graph)) return NULL;

    EddError cpy_err = EDD_NOERR;
    Vertex *vertex = graph_get_vertex(err, graph, vertex_id);
    Vertex *neighbor = graph_get_vertex(err, graph, neighbor_id);
    if (has_error(err) || has_error(&cpy_err)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return NULL;
    }

    return graph_add_edge(err, graph, vertex, neighbor, weight);
}

int graph_id_remove_edge(EddError *err, Graph *graph, size_t vertex_id, size_t neighbor_id) {
    const char *self = "graph_id_remove_edge";
    if (errhandle_nullptr(err, self, graph)) return 0;

    EddError cpy_err = EDD_NOERR;
    Vertex *vertex = graph_get_vertex(err, graph, vertex_id);
    Vertex *neighbor = graph_get_vertex(err, graph, neighbor_id);
    if (has_error(err) || has_error(&cpy_err)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    return graph_remove_edge(err, graph, vertex, neighbor);
}

bool graph_id_is_member(EddError *err, Graph *graph, size_t vertex_id) {
    const char *self = "graph_id_is_member";
    if (errhandle_nullptr(err, self, graph)) return false;

    Vertex *vertex = graph_get_vertex(err, graph, vertex_id);
    if (has_error(err)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return false;
    }

    return graph_is_member(err, graph, vertex);
}

int graph_id_remove_vertex(EddError *err, Graph *graph, size_t vertex_id) {
    const char *self = "graph_id_remove_vertex";
    if (errhandle_nullptr(err, self, graph)) return 0;

    Vertex *vertex = graph_get_vertex(err, graph, vertex_id);
    if (has_error(err)) {
        *err = EDD_ENOENT;
        edd_debug(err, self);
        return 0;
    }

    return graph_remove_vertex(err, graph, vertex);
}

void graph_cmd(EddError *err, Graph *graph, FILE *input_file, FILE *output_file, const char *cmd) {
    const char *self = "graph_cmd";
    if (errhandle_nullptr(err, self, graph)) return;
    if (errhandle_nullptr(err, self, input_file)) return;
    if (errhandle_nullptr(err, self, (void*)cmd)) return;
    if (output_file == NULL) {
        output_file = stdout;
    }

    size_t index;
    size_t vertex_id;
    size_t neighbor_id;
    int key;
    int weight;

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_PRINT)) {
        graph_print(err, graph, output_file);
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ID_IS_ADJACENT)) {
        fscanf(input_file, " %zu %zu", &vertex_id, &neighbor_id);
        bool is_adjacent = graph_id_is_adjacent(err, graph, vertex_id, neighbor_id);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ID_IS_ADJACENT, vertex_id, neighbor_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ID_IS_ADJACENT, vertex_id, neighbor_id, is_adjacent ? "adjacent" : "not adjacent");
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ID_ADJ_LIST_SIZE)) {
        fscanf(input_file, " %zu", &vertex_id);
        size_t adj_list_size = graph_id_adj_list_size(err, graph, vertex_id);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ID_ADJ_LIST_SIZE, vertex_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ID_ADJ_LIST_SIZE, vertex_id, adj_list_size);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ID_GET_NTH_EDGE)) {
        fscanf(input_file, " %zu %zu", &vertex_id, &index);
        Edge *edge = graph_id_get_nth_edge(err, graph, vertex_id, index);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ID_GET_NTH_EDGE, index, vertex_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ID_GET_NTH_EDGE, index, edge->vertex->id);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ID_GET_EDGE)) {
        fscanf(input_file, " %zu %zu", &vertex_id, &neighbor_id);
        Edge *edge = graph_id_get_edge(err, graph, vertex_id, neighbor_id);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ID_GET_EDGE, vertex_id, neighbor_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ID_GET_EDGE, vertex_id, neighbor_id, edge->weight);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ID_ADD_EDGE)) {
        fscanf(input_file, " %zu %zu %d", &vertex_id, &neighbor_id, &weight);
        graph_id_add_edge(err, graph, vertex_id, neighbor_id, weight);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ID_ADD_EDGE, vertex_id, neighbor_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ID_ADD_EDGE, vertex_id, neighbor_id, weight);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ID_REMOVE_EDGE)) {
        fscanf(input_file, " %zu %zu", &vertex_id, &neighbor_id);
        int edge_weight = graph_id_remove_edge(err, graph, vertex_id, neighbor_id);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ID_REMOVE_EDGE, vertex_id, neighbor_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ID_REMOVE_EDGE, vertex_id, neighbor_id, edge_weight);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ID_IS_MEMBER)) {
        fscanf(input_file, " %zu", &vertex_id);
        bool is_member = graph_id_is_member(err, graph, vertex_id);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ID_IS_MEMBER, vertex_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ID_IS_MEMBER, vertex_id, is_member ? "belongs" : "doesn't belong");
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_SIZE)) {
        size_t g_size = graph_size(err, graph);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_SIZE);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_SIZE, g_size);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_GET_NTH_VERTEX)) {
        fscanf(input_file, " %zu", &index);
        Vertex *vertex = graph_get_nth_vertex(err, graph, index);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_GET_NTH_VERTEX, index);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_GET_NTH_VERTEX, vertex->id, index);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_GET_VERTEX)) {
        fscanf(input_file, " %zu", &vertex_id);
        graph_get_vertex(err, graph, vertex_id);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_GET_VERTEX, vertex_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_GET_VERTEX, vertex_id);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ADD_VERTEX)) {
        fscanf(input_file, " %d", &key);
        graph_add_vertex(err, graph, key);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ADD_VERTEX);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ADD_VERTEX, key);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_GRAPH_ID_REMOVE_VERTEX)) {
        fscanf(input_file, " %zu", &vertex_id);
        graph_id_remove_vertex(err, graph, vertex_id);
        if (has_error(err)) {
            fprintf(output_file, LIBEDD_CMDMSG_ERR_GRAPH_ID_REMOVE_VERTEX, vertex_id);
        } else {
            fprintf(output_file, LIBEDD_CMDMSG_GOOD_GRAPH_ID_REMOVE_VERTEX, vertex_id);
        }
    }

    if (!strcmp(cmd, LIBEDD_CMDNAME_BUGGY_CALLS)) {
        EDD_DEBUG = true;

        Graph *temp_graph = graph_create(true);
        Vertex *temp_vertex = graph_add_vertex(err, temp_graph, 0);
        Vertex *temp_neighbor = graph_add_vertex(err, temp_graph, 1);

        graph_edge_create(NULL, temp_vertex, 0);
        graph_edge_create(err, NULL, 0);
        graph_destroy(NULL, temp_graph);
        graph_destroy(err, NULL);
        graph_print(NULL, temp_graph, output_file);
        graph_print(err, NULL, output_file);
        graph_is_adjacent(NULL, temp_vertex, temp_neighbor);
        graph_is_adjacent(err, NULL, temp_neighbor);
        graph_is_adjacent(err, temp_vertex, NULL);
        graph_adj_list_size(NULL, temp_vertex);
        graph_adj_list_size(err, NULL);
        graph_get_nth_edge(NULL, temp_vertex, 0);
        graph_get_nth_edge(err, NULL, 0);
        graph_get_edge(NULL, temp_vertex, temp_neighbor);
        graph_get_edge(err, NULL, temp_neighbor);
        graph_get_edge(err, temp_vertex, NULL);
        graph_add_edge(NULL, temp_graph, temp_vertex, temp_neighbor, 0);
        graph_add_edge(err, NULL, temp_vertex, temp_neighbor, 0);
        graph_add_edge(err, temp_graph, NULL, temp_neighbor, 0);
        graph_add_edge(err, temp_graph, temp_vertex, NULL, 0);
        graph_remove_edge(NULL, temp_graph, temp_vertex, temp_neighbor);
        graph_remove_edge(err, NULL, temp_vertex, temp_neighbor);
        graph_remove_edge(err, temp_graph, NULL, temp_neighbor);
        graph_remove_edge(err, temp_graph, temp_vertex, NULL);
        graph_is_member(NULL, temp_graph, temp_vertex);
        graph_is_member(err, NULL, temp_vertex);
        graph_is_member(err, temp_graph, NULL);
        graph_size(NULL, temp_graph);
        graph_size(err, NULL);
        graph_get_nth_vertex(NULL, temp_graph, 0);
        graph_get_nth_vertex(err, NULL, 0);
        graph_get_vertex(NULL, temp_graph, 0);
        graph_get_vertex(err, NULL, 0);
        graph_add_vertex(NULL, temp_graph, 2);
        graph_add_vertex(err, NULL, 2);
        graph_remove_vertex(NULL, temp_graph, temp_vertex);
        graph_remove_vertex(err, NULL, temp_vertex);
        graph_remove_vertex(err, temp_graph, NULL);
        graph_id_is_adjacent(NULL, temp_graph, 0, 1);
        graph_id_is_adjacent(err, NULL, 0, 1);
        graph_id_adj_list_size(NULL, temp_graph, 0);
        graph_id_adj_list_size(err, NULL, 0);
        graph_id_get_nth_edge(NULL, temp_graph, 0, 0);
        graph_id_get_nth_edge(err, NULL, 0, 0);
        graph_id_get_edge(NULL, temp_graph, 0, 1);
        graph_id_get_edge(err, NULL, 0, 1);
        graph_id_add_edge(NULL, temp_graph, 0, 1, 2);
        graph_id_add_edge(err, NULL, 0, 1, 2);
        graph_id_remove_edge(NULL, temp_graph, 0, 1);
        graph_id_remove_edge(err, NULL, 0, 1);
        graph_id_is_member(NULL, temp_graph, 0);
        graph_id_is_member(err, NULL, 0);
        graph_id_remove_vertex(NULL, temp_graph, 0);
        graph_id_remove_vertex(err, NULL, 0);

        graph_print(err, temp_graph, output_file);
        graph_destroy(err, temp_graph);
    }
}
