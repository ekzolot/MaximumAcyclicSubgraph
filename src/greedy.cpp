#include "greedy.h"

Graph AcyclicSubgraph(const Graph& graph) {
    Graph e1;
    Graph e2;
    for (const Edge& edge : graph) {
        (edge.from < edge.to ? e1 : e2).AddEdge(edge);
    }
    if (e1.EdgeCount() > e2.EdgeCount()) {
        return e1;
    }
    return e2;
}