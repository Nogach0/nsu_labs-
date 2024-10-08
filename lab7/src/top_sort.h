#ifndef TOP_SORT_H
#define TOP_SORT_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_VERTICES 2000
#define MIN_NUMBER_ANY 0
#define ERROR_QUEUE (-1)

typedef struct Graph {
  unsigned char *matrix;
  unsigned short number_vertices;
} Graph;

typedef enum State {
  BAD_NUMBER_OF_VERTICES,
  BAD_NUMBER_OF_EDGES,
  BAD_VERTEX,
  BAD_NUMBER_OF_LINES,
  SUCCESS
} State;

void HandleError(State state);
Graph *CreateGraph(int number_vertices);
State InitializeGraph(Graph *graph, int number_edges);
void FreeGraph(Graph *graph);
void PrintVertices(Graph *graph, int *result);
void FindTopologicalOrdering(Graph *graph, int *result);

#endif // TOP_SORT_H
