#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_VERTICES 5000
#define MIN_NUMBER_ANY 0

typedef struct Graph {
  unsigned int **matrix;
  unsigned short number_vertices;
} Graph;

typedef enum State {
  BAD_NUMBER_OF_VERTICES,
  BAD_NUMBER_OF_EDGES,
  BAD_VERTEX,
  BAD_LENGTH,
  BAD_NUMBER_OF_LINES,
  SUCCESS
} State;

void HandleError(State state);
Graph *CreateGraph(int number_vertices);
State InitializeGraph(Graph *graph, int number_edges);
void FreeGraph(Graph *graph);
void PrintPathToVertices(Graph *graph, unsigned int costs[]);
void PrintShortestPath(Graph *graph, unsigned int costs[], int parents[],
                       bool visited[], int end);
void DijkstraAlgorithm(Graph *graph, int start, int end);

#endif // GRAPH_H
