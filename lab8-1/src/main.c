#include "graph.h"

int main() {
  State state = SUCCESS;

  int number_vertices = 0;
  if (scanf("%d", &number_vertices) != 1)
    return 0;

  if (number_vertices < MIN_NUMBER_ANY || number_vertices > MAX_NUMBER_VERTICES)
    state = BAD_NUMBER_OF_VERTICES;

  if (state != SUCCESS) {
    HandleError(state);
    return 0;
  }

  int number_edges = 0;
  if (scanf("%d", &number_edges) != 1)
    return 0;

  if (number_edges < MIN_NUMBER_ANY ||
      number_edges > number_vertices * (number_vertices - 1) / 2) {
    state = BAD_NUMBER_OF_EDGES;
  }

  if ((number_edges == 0 && number_vertices == 0) ||
      (number_edges + 1 < number_vertices)) {
    state = NO_SPANNING_TREE;
  }

  if (state != SUCCESS) {
    HandleError(state);
    return 0;
  }

  Graph *graph = CreateGraph(number_vertices);
  state = InitializeGraph(graph, number_edges);

  if (state != SUCCESS) {
    HandleError(state);
    FreeGraph(graph);
    return 0;
  }

  int *parent = malloc(number_vertices * sizeof(int));
  CreateMinSpanTree(graph, parent);
  PrintMinSpanTree(graph->number_vertices, parent);

  free(parent);
  FreeGraph(graph);
  return 0;
}
