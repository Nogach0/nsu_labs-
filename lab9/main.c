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

typedef enum TState {
    bad_number_of_vertices,
    bad_number_of_edges,
    bad_vertex,
    bad_length,
    bad_number_of_lines,
    SUCCESS
} TState;

void ErrorHandler(TState state) {
    switch (state) {
        case bad_number_of_vertices:
            printf("bad number of vertices\n");
            break;

        case bad_number_of_edges:
            printf("bad number of edges\n");
            break;

        case bad_vertex:
            printf("bad vertex\n");
            break;

        case bad_length:
            printf("bad length\n");
            break;

        case bad_number_of_lines:
            printf("bad number of lines\n");
            break;

        case SUCCESS:
            break;
    }
}

Graph *CreateGraph (int number_vertices){
    Graph *new_graph = calloc(1, sizeof (Graph));
    new_graph -> matrix = calloc(number_vertices, sizeof (int *));

    for (int i = 0; i < number_vertices; i++)
        new_graph->matrix[i] = calloc(number_vertices, sizeof (int));

    new_graph->number_vertices = number_vertices;
    return new_graph;
}

TState GraphInitialization (Graph *graph, int number_edges){
    unsigned int row = 0, col = 0;
    unsigned int edge_length = 0;
    for (int i = 0; i < number_edges; i++){

        if (scanf("%u %u %u", &row, &col, &edge_length) != 3)
            return bad_number_of_lines;

        if (row > graph->number_vertices || row < 1 ||
            col > graph->number_vertices || col < 1)
            return bad_vertex;

        if (edge_length > INT_MAX)
            return bad_length;

        graph->matrix[row-1][col-1] = edge_length;
        graph->matrix[col-1][row-1] = edge_length;
    }
    return SUCCESS;
}

void FreeGraph(Graph *graph) {
    for (int i = 0; i < graph->number_vertices; i++)
        free(graph->matrix[i]);
    free(graph->matrix);
    free(graph);
}

void DijkstraAlgorith(Graph *graph, int start, int end) {
    unsigned int costs[graph->number_vertices];
    int parents[graph->number_vertices];
    bool visited[graph->number_vertices];


    for (int i = 0; i < graph->number_vertices; i++) {
        costs[i] = UINT_MAX;
        parents[i] = -1;
        visited[i] = false;
    }

    costs[start - 1] = 0;


    for (int i = 0; i < graph->number_vertices; i++) {
        int min_cost = UINT_MAX;
        int current_node = -1;


        for (int v = 0; v < graph->number_vertices; v++) {
            if (!visited[v] && costs[v] < min_cost) {
                min_cost = costs[v];
                current_node = v;
            }
        }

        visited[current_node] = true;


        for (int v = 0; v < graph->number_vertices; v++) {
            if (!visited[v] && graph->matrix[current_node][v] != 0 &&
                costs[current_node] + graph->matrix[current_node][v] < costs[v]) {
                costs[v] = costs[current_node] + graph->matrix[current_node][v];
                parents[v] = current_node;
            }
        }
    }

    for (int i = 0; i < graph->number_vertices; i++){
        printf("%u ", costs[(start - 1)+i]);
    }
    int current = end - 1;
    while (current != -1) {
        printf("%d ", current + 1);
        current = parents[current];
    }
}

int main() {
    TState state = SUCCESS;

    int number_vertices = 0;
    if (scanf("%d", &number_vertices) != 1)
        return 0;

    if (number_vertices < MIN_NUMBER_ANY || number_vertices > MAX_NUMBER_VERTICES)
        state = bad_number_of_vertices;

    if (state != SUCCESS) {
        ErrorHandler(state);
        return 0;
    }

    int start, end;
    if (scanf("%d %d", &start, &end) != 2)
        return 0;

    int number_edges = 0;
    if (scanf("%d", &number_edges) != 1){
        return 0;
    }

    if (number_edges < MIN_NUMBER_ANY ||
        number_edges > number_vertices * (number_vertices - 1) / 2)
        state = bad_number_of_edges;

    if (state != SUCCESS) {
        ErrorHandler(state);
        return 0;
    }

    Graph *graph = CreateGraph(number_vertices);
    state = GraphInitialization(graph, number_edges);

    if (state != SUCCESS) {
        ErrorHandler(state);
        FreeGraph(graph);
        return 0;
    }


    /*for (int i = 0; i < number_vertices; i++){
        for (int j = 0; j < number_vertices; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
*/
    DijkstraAlgorith(graph, start, end);

    return 0;
}

