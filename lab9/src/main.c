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

  int start, end;
  if (scanf("%d %d", &start, &end) != 2 || start <= MIN_NUMBER_ANY ||
      start > number_vertices || end <= MIN_NUMBER_ANY ||
      end > number_vertices) {
    state = BAD_VERTEX;
  }

  if (state != SUCCESS) {
    HandleError(state);
    return 0;
  }

  int number_edges = 0;
  if (scanf("%d", &number_edges) != 1) {
    return 0;
  }

  if (number_edges < MIN_NUMBER_ANY ||
      number_edges > number_vertices * (number_vertices - 1) / 2) {
    state = BAD_NUMBER_OF_EDGES;
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

  DijkstraAlgorithm(graph, start, end);

  FreeGraph(graph);
  return 0;
}
