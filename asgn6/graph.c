#include "graph.h"
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 100

//struct for graph
typedef struct graph{
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

Graph *graph_create(uint32_t vertices, bool directed){
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;

    //use calloc to initialize everything with zeros
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));
    //allocate g->weights with a pointer for each row
    g->weights = calloc(vertices, sizeof(g->weights[0]));

    for(uint32_t i=0; i<vertices; i++){
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }

    return g;
}

void graph_free(Graph **gp){
    Graph *g = *gp;

    for (uint32_t i = 0; i < g->vertices; i++) {
        free(g->names[i]);
    }
    free(g->names);

    for (uint32_t i = 0; i < g->vertices; i++) {
        free(g->weights[i]);
    }
    free(g->weights);
    free(g->visited);
    free(g);

    *gp = NULL;
}

uint32_t graph_vertices(const Graph *g){
    return g->vertices;
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight){
    if(start >= g->vertices || end >= g->vertices){
        printf("Error: Vertex index out of bounds.\n");
        return;
    }
    g->weights[start][end] = weight;
    g->weights[end][start] = weight;
    // if(g->directed == false){
    //     g->weights[end][start] = weight;
    // }
    }

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end){
    // printf("inside of graph_get_weight\n");
    //look up the weight of the edge between start and end and return it
    //skip if there are no weights between the given start and end
    for(uint32_t i=0; i<g->vertices; i++){
        for(uint32_t j=0; j<g->vertices; j++){
            if(g->weights[i][j]){
                if(i==start && j==end){
                    // printf("graph_get_weight: it matches\n");
                    return g->weights[start][end];
                }
            }   
        }
    }
    return 0;
}

void graph_visit_vertex(Graph *g, uint32_t v){
    //add the vertex v to the list of visited vertices
    if(v >= g->vertices){
        printf("Error: Vertex index out of bounds.\n");
        return;
    }
    g->visited[v] = true;
}

void graph_unvisit_vertex(Graph *g, uint32_t v){
    if(v >= g->vertices){
        printf("Error: Vertex index out of bounds.\n");
        return;
    }
    g->visited[v] = false;
}

bool graph_visited(const Graph *g, uint32_t v){
    //return true if vertex v is visited in graph g, false otherwise
    return g->visited[v];
}

char **graph_get_names(const Graph *g){
    //get the name of the every city in an array. return a double pointer of an array of strings but not a copy.
    return g->names;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v){
    if(g->names[v]){
        free(g->names[v]);
    }
    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v){
    //get the name of the city with vertex v from the array of city names.
    return g->names[v];
}

void graph_print(const Graph *g){
    //prints a human relatable representation of a graph
    // Print vertex names
    printf("Vertex Names:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        printf("%d: %s\n", i, g->names[i]);
    }

    // Print edges and weights:
    printf("\nEdges and Weights:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            if (g->weights[i][j] != 0) {
                printf("Weight[%d -> %d]: %d\n", i, j, g->weights[i][j]);
            }
        }
    }
}
