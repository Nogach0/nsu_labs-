#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_VERTICES 5000
#define MIN_NUMBER_ANY 0

// Enumerated type for different states.
typedef enum TState {
    bad_number_of_vertices,
    bad_number_of_edges,
    bad_vertex,
    bad_length,
    bad_number_of_lines,
    no_spanning_tree,
    SUCCESS
} TState;

void ErrorHandler(TState state);

typedef struct Graph {
    unsigned int **matrix;
    unsigned short number_vertices;
} Graph;

void FreeGraph(Graph *graph);
Graph *CreateGraph(int number_vertices);
TState GraphInitialization(Graph *graph, int number_edges);
void PrimAlgorithm(Graph *graph);

#endif /* GRAPH_H */
