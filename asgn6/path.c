#include "path.h"
#include "stack.h"
#include "graph.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct path {
uint32_t total_weight;
Stack *vertices;
} Path;

// Function to create a path
Path *path_create(uint32_t capacity) {
    Path *p = (Path *)malloc(sizeof(Path));
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    return p;
}

// Function to free a path and its associated memory
void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        if ((*pp)->vertices) {
            stack_free(&(*pp)->vertices);
        }
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

// Function to find the number of vertices in a path
uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

// Function to find the distance covered by a path
uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

// Function to add a vertex to the path
void path_add(Path *p, uint32_t val, const Graph *g) {
    uint32_t total_weight = path_distance(p);

    if (path_vertices(p) > 0) {
        uint32_t last_vertex;
        stack_peek(p->vertices, &last_vertex);

        //compare with the last vertex and current vertex to get the weight
        uint32_t weight = graph_get_weight(g, last_vertex, val);

        // Check if the weight is non-zero before updating total_weight
        if (weight != 0) {
            total_weight += weight;
            p->total_weight = total_weight;  // Update total_weight in the path
        }
    }
    stack_push(p->vertices, val);
}

// Function to remove the most recently added vertex from the path
uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex;
    if (stack_pop(p->vertices, &removed_vertex)) {
        if (path_vertices(p) > 1) {
            uint32_t last_vertex;
            stack_peek(p->vertices, &last_vertex);
            p->total_weight -= graph_get_weight(g, last_vertex, removed_vertex);
        } else {
            p->total_weight = 0;
        }
        return removed_vertex;
    }
    return UINT32_MAX; // or any other suitable error value
}

// Function to copy a path from src to dst
void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

// Function to print the path using vertex names from g to the file outfile
void path_print(const Path *p, FILE *outfile, const Graph *g) {
    printf("inside path_print\n");
    if (p == NULL || outfile == NULL || g == NULL) {
        // Handle invalid input
        fprintf(stderr, "Invalid input in path_print\n");
        return;
    }

    if (p->vertices == NULL) {
        // Handle case where vertices stack is not initialized
        fprintf(stderr, "Vertices stack is not initialized in path_print\n");
        return;
    }

    char **cities = graph_get_names(g);
    
    stack_print(p->vertices, outfile, cities);
}
