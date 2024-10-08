#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_VERTICES 5000
#define MIN_NUMBER_ANY 0
#define ERROR_NO_SPANNING_TREE (-2)

// Enumerated type for different states.
typedef enum State {
  BAD_NUMBER_OF_VERTICES,
  BAD_NUMBER_OF_EDGES,
  BAD_VERTEX,
  BAD_LENGTH,
  BAD_NUMBER_OF_LINES,
  NO_SPANNING_TREE,
  SUCCESS
} State;

void HandleError(State state);

typedef struct Graph {
  unsigned int **matrix;
  unsigned short number_vertices;
} Graph;

void FreeGraph(Graph *graph);
Graph *CreateGraph(int number_vertices);
State InitializeGraph(Graph *graph, int number_edges);
void PrintMinSpanTree(int n, int *parent);
void CreateMinSpanTree(Graph *graph, int *parent);

#endif /* GRAPH_H */
