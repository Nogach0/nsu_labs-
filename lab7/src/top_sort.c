#include "top_sort.h"

void HandleError(State state) {
    switch (state) {
        case BAD_NUMBER_OF_VERTICES:
            printf("bad number of vertices");
            break;

        case BAD_NUMBER_OF_EDGES:
            printf("bad number of edges");
            break;

        case BAD_VERTEX:
            printf("bad vertex");
            break;

        case BAD_NUMBER_OF_LINES:
            printf("bad number of lines");
            break;

        case SUCCESS:
            break;
    }
}

Graph *CreateGraph(int number_vertices) {
    Graph *new_graph = malloc(sizeof(Graph));

    new_graph->matrix =
            calloc(number_vertices * number_vertices, sizeof(unsigned char));
    new_graph->number_vertices = number_vertices;

    return new_graph;
}

State InitializeGraph(Graph *graph, int number_edges) {
    unsigned int start = 0, end = 0;
    for (int i = 0; i < number_edges; i++) {

        if (scanf("%u %u", &start, &end) != 2) {
            return BAD_NUMBER_OF_LINES;
        }

        if (start > graph->number_vertices || start < 1 ||
            end > graph->number_vertices || end < 1) {
            return BAD_VERTEX;
        }

        graph->matrix[graph->number_vertices * (start - 1) + (end - 1)] = 1;
    }
    return SUCCESS;
}

void FreeGraph(Graph *graph) {
    free(graph->matrix);
    free(graph);
}

void PrintVertices(Graph *graph, int *result) {
    if (result[graph->number_vertices - 1] == ERROR_QUEUE) {
        printf("impossible to sort");
    } else {
        for (int i = 0; i < graph->number_vertices; i++) {
            printf("%d ", result[i] + 1);
        }
    }
}

void FindTopologicalOrdering(Graph *graph, int *result) {
    int *number_occurrences = calloc(graph->number_vertices, sizeof(int));
    int *visited = calloc(graph->number_vertices, sizeof(int));

    for (int i = 0; i < graph->number_vertices; i++) {
        for (int j = 0; j < graph->number_vertices; j++) {
            if (graph->matrix[graph->number_vertices * i + j]) {
                number_occurrences[j]++;
            }
        }
    }

    int *queue = malloc(graph->number_vertices * sizeof(int));
    int front = 0, back = -1;

    for (int i = 0; i < graph->number_vertices; i++) {
        if (number_occurrences[i] == 0) {
            queue[++back] = i;
        }
    }

    int result_idx = 0;
    while (front <= back) {
        int node = queue[front++];
        result[result_idx++] = node;

        visited[node] = 1;

        for (int i = 0; i < graph->number_vertices; i++) {
            if (graph->matrix[graph->number_vertices * node + i] && !visited[i]) {
                number_occurrences[i]--;

                if (number_occurrences[i] == 0) {
                    queue[++back] = i;
                }
            }
        }
    }
    free(queue);
    free(number_occurrences);
    free(visited);
}
