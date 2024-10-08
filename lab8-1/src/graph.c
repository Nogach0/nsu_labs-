#include "graph.h"

void HandleError(State state) {
  switch (state) {
  case BAD_NUMBER_OF_VERTICES:
    printf("bad number of vertices\n");
    break;

  case BAD_NUMBER_OF_EDGES:
    printf("bad number of edges\n");
    break;

  case BAD_VERTEX:
    printf("bad vertex\n");
    break;

  case BAD_LENGTH:
    printf("bad length\n");
    break;

  case BAD_NUMBER_OF_LINES:
    printf("bad number of lines\n");
    break;

  case NO_SPANNING_TREE:
    printf("no spanning tree\n");
    break;

  case SUCCESS:
    break;
  }
}

Graph *CreateGraph(int number_vertices) {
  Graph *new_graph = calloc(1, sizeof(Graph));
  new_graph->matrix = calloc(number_vertices, sizeof(int *));

  for (int i = 0; i < number_vertices; i++)
    new_graph->matrix[i] = calloc(number_vertices, sizeof(int));

  new_graph->number_vertices = number_vertices;
  return new_graph;
}

void FreeGraph(Graph *graph) {
  for (int i = 0; i < graph->number_vertices; i++)
    free(graph->matrix[i]);
  free(graph->matrix);
  free(graph);
}

State InitializeGraph(Graph *graph, int number_edges) {
  unsigned int row = 0, col = 0;
  unsigned int edge_length = 0;
  for (int i = 0; i < number_edges; i++) {

    if (scanf("%u %u %u", &row, &col, &edge_length) != 3)
      return BAD_NUMBER_OF_LINES;

    if (row > graph->number_vertices || row < 1 ||
        col > graph->number_vertices || col < 1) {
      return BAD_VERTEX;
    }

    if (edge_length > INT_MAX)
      return BAD_LENGTH;

    if (row == col)
      return NO_SPANNING_TREE;

    graph->matrix[row - 1][col - 1] = edge_length;
    graph->matrix[col - 1][row - 1] = edge_length;
  }
  return SUCCESS;
}

void PrintMinSpanTree(int n, int *parent) {
  if (parent[0] == ERROR_NO_SPANNING_TREE) {
    printf("no spanning tree\n");
    return;
  }
  for (int i = 1; i < n; i++)
    printf("%d %d\n", parent[i] + 1, i + 1);
}

void CreateMinSpanTree(Graph *graph, int *parent) {
  unsigned int *key = malloc(graph->number_vertices * sizeof(unsigned int));
  bool *visited = malloc(graph->number_vertices * sizeof(bool));
  const unsigned int kInfinity = UINT_MAX;

  for (int i = 0; i < graph->number_vertices; i++) {
    key[i] = kInfinity;
    visited[i] = false;
  }

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < graph->number_vertices; count++) {
    unsigned int min = kInfinity;
    int min_index = -1;

    for (int v = 0; v < graph->number_vertices; v++) {
      if (visited[v] == false && key[v] < min) {
        min = key[v];
        min_index = v;
      }
    }

    if (min_index == -1) {
      parent[0] = ERROR_NO_SPANNING_TREE;
      free(key);
      free(visited);
      return;
    }

    int u = min_index;

    visited[u] = true;

    for (int v = 0; v < graph->number_vertices; v++)
      if (graph->matrix[u][v] && visited[v] == false &&
          graph->matrix[u][v] < key[v]) {
        parent[v] = u;
        key[v] = graph->matrix[u][v];
      }
  }
  free(key);
  free(visited);
}
