#include "graph.h"

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

    int number_edges = 0;
    if (scanf("%d", &number_edges) != 1)
        return 0;

    if (number_edges < MIN_NUMBER_ANY ||
        number_edges > number_vertices * (number_vertices - 1) / 2)
        state = bad_number_of_edges;

    if ((number_edges == 0 && number_vertices == 0) ||
        (number_edges + 1 < number_vertices))
        state = no_spanning_tree;

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

    PrimAlgorithm(graph);
    FreeGraph(graph);
    return 0;
}
