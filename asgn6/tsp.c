#include "path.h"
#include "vertices.h"
#include "graph.h"
#include "stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

//algorithm for going through all paths
void dfs(uint32_t v, Graph *g, uint32_t vertex_num, Path *p, Path *shortest, FILE *outfile){
    //it's trying to get an edge for the connection it doesn't even have
    //should modify the algorithm
    // printf("inside dfs\n");
    uint32_t start, end;
    graph_visit_vertex(g,v);
    start = v;

    //add the vertices to the path, only the ones that graph has not visited yet
    path_add(p, v, g);
    for(uint32_t i=1; i<vertex_num; i++){
        if(!graph_visited(g,i)){
            //get weight from start and end
            dfs(i,g,vertex_num, p, shortest, outfile);
        }
    }
    //here, it ends one loop of the recursion which means one path
    if(start != START_VERTEX){
        //try adding this to the path as well
        end = START_VERTEX;
        path_add(p,end,g);
    }

    //printf("dfs: path_vertices(p) = %u", path_vertices(p));
        uint32_t smallest_weight = path_distance(shortest);
        uint32_t current_weight = path_distance(p);
    if(path_vertices(p) == vertex_num + 1){
        // printf("Went to all cities\n");
        graph_unvisit_vertex(g,v);
        
        //calculate each weight of the shortest(static) and p(changes every time);

        //printf("smallest weight:%u, current weight:%u\n", smallest_weight, current_weight);
        // printf("smallest:%u, current:%u\n", smallest_weight, current_weight);
        //but it has to be all cities, so..........?
        if(smallest_weight == 0){
           // printf("smallest<-current\n");
            path_copy(shortest , p);
        }
        if(smallest_weight > current_weight && current_weight != 0){
            //printf("smallest weight:%u, current weight:%u\n", smallest_weight, current_weight);
            path_copy(shortest , p);
        }    
    }
        path_remove(p, g);
        
    if(start == START_VERTEX){
        // printf("Santa Cruz\n");
        graph_print(g);
        path_print(shortest, outfile, g);
        if(smallest_weight == 0){
            printf("No path found! Alicia's lost!\n");
        }
    }
    
}

int main(){
    char filename[50];
    FILE *file;

    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
    }

    uint32_t num_vertices, num_edges, start, end, weight;
    char city[50];
    //read each line of the file and insert data into graphs
    fscanf(file, "%u", &num_vertices);
    // printf("number of vertices: %u\n", num_vertices);
    Graph *g = graph_create(num_vertices, false);

    fgetc(file);
    //maps/bayarea.graph
    for(uint32_t i=0; i<num_vertices; i++){
        fscanf(file, "%49[^\n]", city);
        // printf("Read city: %s\n", city);
        graph_add_vertex(g, city, i);
        fgetc(file);
    }

    fscanf(file, "%u", &num_edges);
    // printf("%u\n", num_edges);

    for(uint j=0; j<num_edges; j++){
        fgetc(file);
        fscanf(file, "%u %u %u", &start, &end, &weight);
        // printf("%u %u %u\n", start, end, weight);
        graph_add_edge(g,start,end,weight);
    }

    fclose(file);

    Path *p = path_create(num_vertices+1);
    Path *shortest_path = path_create(num_vertices+1);
    // printf("created path\n");
    FILE *outfile = fopen("output.txt", "w");  // Open a file for writing
    // printf("open output.txt\n");
    if (outfile == NULL) {
        perror("Error opening output file");
        return 1;
    }

    // printf("reading dfs\n");
    dfs(START_VERTEX,g,num_vertices,p,shortest_path, outfile);
    // printf("out of dfs\n");
    fclose(outfile);
    //shortest path
    path_free(&p);
    path_free(&shortest_path);
    graph_free(&g);

    return 0;
}
