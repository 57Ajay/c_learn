#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph *createGraphMatrix(int V) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL) {
        perror("Failed to allocate memory for Graph structure");
        exit(EXIT_FAILURE);
    }

    graph->V = V;

    graph->adjMatrix = (int **)malloc(V * sizeof(int *));
    if (graph->adjMatrix == NULL) {
        perror("Failed to allocate memory for adjacency matrix rows");
        free(graph);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < V; i++) {
        graph->adjMatrix[i] = (int *)malloc(V * sizeof(int));
        if (graph->adjMatrix[i] == NULL) {
            perror("Failed to allocate memory for adjacency matrix columns");
            for (int j = 0; j < i; j++) {
                free(graph->adjMatrix[j]);
            }
            free(graph->adjMatrix);
            free(graph);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

void addEdgeMatrix(Graph *graph, int src, int dest) {
    if (graph == NULL || src < 0 || src >= graph->V || dest < 0 ||
        dest >= graph->V) {
        fprintf(stderr,
                "Error: Invalid graph or vertex indices for addEdgeMatrix.\n");
        return;
    }
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1; // For undirected graph
}

bool hasEdgeMatrix(const Graph *graph, int src, int dest) {
    if (graph == NULL || src < 0 || src >= graph->V || dest < 0 ||
        dest >= graph->V) {
        fprintf(stderr,
                "Error: Invalid graph or vertex indices for hasEdgeMatrix.\n");
        return false;
    }
    return (graph->adjMatrix[src][dest] == 1);
}

void printGraphMatrix(const Graph *graph) {
    if (graph == NULL) {
        printf("Graph is NULL.\n");
        return;
    }
    printf("Adjacency Matrix (%d vertices):\n", graph->V);
    // Print column headers
    printf("   ");
    for (int i = 0; i < graph->V; i++) {
        printf("%3d", i);
    }
    printf("\n");
    printf("  ---");
    for (int i = 0; i < graph->V; i++) {
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < graph->V; i++) {
        printf("%2d |", i); // Print row header
        for (int j = 0; j < graph->V; j++) {
            printf("%3d", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void freeGraphMatrix(Graph *graph) {
    if (graph == NULL) {
        return;
    }

    for (int i = 0; i < graph->V; i++) {
        if (graph->adjMatrix[i] != NULL) {
            free(graph->adjMatrix[i]);
        }
    }
    if (graph->adjMatrix != NULL) {
        free(graph->adjMatrix);
    }
    free(graph);
}

int graphMain() {
    int V = 5;

    Graph *myGraph = createGraphMatrix(V);
    if (myGraph == NULL) {
        fprintf(stderr, "Failed to create graph.\n");
        return 1;
    }

    printf("Graph created with %d vertices.\n", myGraph->V);

    addEdgeMatrix(myGraph, 0, 1);
    addEdgeMatrix(myGraph, 0, 4);
    addEdgeMatrix(myGraph, 1, 2);
    addEdgeMatrix(myGraph, 1, 3);
    addEdgeMatrix(myGraph, 1, 4);
    addEdgeMatrix(myGraph, 2, 3);
    addEdgeMatrix(myGraph, 3, 4);

    printf("\nAfter adding edges:\n");
    printGraphMatrix(myGraph);

    printf("\nChecking for edges:\n");
    printf("Edge (0, 1) exists: %s\n",
           hasEdgeMatrix(myGraph, 0, 1) ? "true" : "false");
    printf("Edge (1, 0) exists: %s\n",
           hasEdgeMatrix(myGraph, 1, 0) ? "true" : "false");
    printf("Edge (0, 2) exists: %s\n",
           hasEdgeMatrix(myGraph, 0, 2) ? "true" : "false");
    printf("Edge (3, 4) exists: %s\n",
           hasEdgeMatrix(myGraph, 3, 4) ? "true" : "false");

    freeGraphMatrix(myGraph);
    myGraph = NULL;

    return 0;
}
