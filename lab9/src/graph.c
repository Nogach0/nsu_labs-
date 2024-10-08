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

State InitializeGraph(Graph *graph, int number_edges) {
  unsigned int row = 0, col = 0;
  unsigned int edge_length = 0;

  for (int i = 0; i < number_edges; i++) {
    if (scanf("%u %u %u", &row, &col, &edge_length) != 3) {
      return BAD_NUMBER_OF_LINES;
    }

    if (row > graph->number_vertices || row < 1 ||
        col > graph->number_vertices || col < 1) {
      return BAD_VERTEX;
    }

    if (edge_length > INT_MAX) {
      return BAD_LENGTH;
    }

    graph->matrix[row - 1][col - 1] = edge_length;
    graph->matrix[col - 1][row - 1] = edge_length;
  }
  return SUCCESS;
}

void FreeGraph(Graph *graph) {
  for (int i = 0; i < graph->number_vertices; i++)
    free(graph->matrix[i]);
  free(graph->matrix);
  free(graph);
}

void PrintPathToVertices(Graph *graph, unsigned int costs[]) {
  for (int i = 0; i < graph->number_vertices; i++) {
    if (costs[i] <= INT_MAX) {
      printf("%u ", costs[i]);
    } else if (costs[i] == UINT_MAX) {
      printf("oo ");
    } else if (costs[i] > INT_MAX && costs[i] != UINT_MAX) {
      printf("INT_MAX+ ");
    }
  }
}

void PrintShortestPath(Graph *graph, unsigned int costs[], int parents[],
                       bool visited[], int end) {
  int current = end - 1;

  if (!visited[current])
    printf("no path");

  int count_overflow = 0;
  for (int i = 0; i < graph->number_vertices; i++) {
    if (costs[i] >= INT_MAX && costs[i] != UINT_MAX) {
      count_overflow++;
    }
  }

  if (count_overflow > 2 && costs[current] > INT_MAX) {
    printf("overflow\n");
  } else {
    while (current != -1) {
      printf("%d ", current + 1);
      current = parents[current];
    }
  }
}

void DijkstraAlgorithm(Graph *graph, int start, int end) {
  unsigned int *costs = malloc(graph->number_vertices * sizeof(unsigned int));
  int *parents = malloc(graph->number_vertices * sizeof(int));
  bool *visited = malloc(graph->number_vertices * sizeof(bool));

  for (int i = 0; i < graph->number_vertices; i++) {
    costs[i] = UINT_MAX;
    parents[i] = -1;
    visited[i] = false;
  }

  costs[start - 1] = 0;

  for (int i = 0; i < graph->number_vertices; i++) {
    unsigned int min_cost = UINT_MAX;
    int current_node = -1;

    for (int j = 0; j < graph->number_vertices; j++) {
      if (!visited[j] && costs[j] < min_cost) {
        min_cost = costs[j];
        current_node = j;
      }
    }

    if (current_node == -1 || min_cost == UINT_MAX)
      break;

    visited[current_node] = true;

    for (int j = 0; j < graph->number_vertices; j++) {
      if (!visited[j] &&
          costs[current_node] + graph->matrix[current_node][j] < costs[j] &&
          graph->matrix[current_node][j]) {
        costs[j] = costs[current_node] + graph->matrix[current_node][j];
        parents[j] = current_node;
      }
    }
  }

  PrintPathToVertices(graph, costs);
  printf("\n");
  PrintShortestPath(graph, costs, parents, visited, end);

  free(costs);
  free(parents);
  free(visited);
}
