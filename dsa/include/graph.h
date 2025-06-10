#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct Graph {
  int V;
  int **adjMatrix;
} Graph;

int graphMain();

Graph *createGraphMatrix(int V);

void addEdgeMatrix(Graph *graph, int src, int dest);

bool hasEdgeMatrix(const Graph *graph, int src, int dest);

void printGraphMatrix(const Graph *graph);

void freeGraphMatrix(Graph *graph);

#endif
