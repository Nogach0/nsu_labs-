#include "graph.h"

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

        case no_spanning_tree:
            printf("no spanning tree\n");
            break;

        case SUCCESS:
            break;
    }
}

Graph *CreateGraph(int number_vertices) {
    Graph *new_graph = calloc(1, sizeof(Graph));
    new_graph->matrix = calloc(number_vertices, sizeof(int *));

    for (int i = 0; i < number_vertices; i++) {
        new_graph->matrix[i] = calloc(number_vertices, sizeof(int));
    }

    new_graph->number_vertices = number_vertices;
    return new_graph;
}

void FreeGraph(Graph *graph) {
    for (int i = 0; i < graph->number_vertices; i++)
        free(graph->matrix[i]);
    free(graph->matrix);
    free(graph);
}

TState GraphInitialization(Graph *graph, int number_edges) {
    unsigned int row = 0, col = 0;
    unsigned int edge_length = 0;
    for (int i = 0; i < number_edges; i++) {

        if (scanf("%u %u %u", &row, &col, &edge_length) != 3)
            return bad_number_of_lines;

        if (row > graph->number_vertices || row < 1 ||
            col > graph->number_vertices || col < 1)
            return bad_vertex;

        if (edge_length > INT_MAX)
            return bad_length;

        if (row == col)
            return no_spanning_tree;

        graph->matrix[row - 1][col - 1] = edge_length;
        graph->matrix[col - 1][row - 1] = edge_length;
    }
    return SUCCESS;
}

void PrimAlgorithm(Graph *graph) {
    int parent[graph->number_vertices];
    unsigned int key[graph->number_vertices];
    bool visited[graph->number_vertices];
    const unsigned int kInfinity = UINT_MAX;

    for (int i = 0; i < graph->number_vertices; i++)
        key[i] = kInfinity, visited[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->number_vertices; count++) {
        unsigned int min = kInfinity;
        int min_index = -1;

        for (int v = 0; v < graph->number_vertices; v++)
            if (visited[v] == false && key[v] < min)
                min = key[v], min_index = v;

        if (min_index == -1) {
            printf("no spanning tree\n");
            return;
        }

        int u = min_index;

        visited[u] = true;

        for (int v = 0; v < graph->number_vertices; v++)
            if (graph->matrix[u][v] && visited[v] == false &&
                graph->matrix[u][v] < key[v])
                parent[v] = u, key[v] = graph->matrix[u][v];
    }

    for (int i = 1; i < graph->number_vertices; i++)
        printf("%d %d\n", parent[i] + 1, i + 1);
}
