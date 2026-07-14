#include "graph.h"

Edge::Edge(int from, int to) :from(from), to(to) {}

Graph::Graph(int vertex_count) : vertex_count_(vertex_count) {}
Graph::Graph(int vertex_count, std::vector<Edge> edges) : vertex_count_(vertex_count), edges_(std::move(edges)) {}

int Graph::VertexCount() const {
    return vertex_count_;
}

int Graph::EdgeCount() const {
    return edges_.size();
}

void Graph::AddEdge(Edge edge) {
    edges_.push_back(edge);
}

Graph BuildSubgraph(const Graph& graph, const std::vector<int>& order) {
    Graph subgraph(graph.VertexCount());
    for (const Edge& edge : graph) {
        if (order[edge.from] < order[edge.to]) {
            subgraph.AddEdge(edge);
        }
    }
    return subgraph;
}

void Graph::ReserveEdges(int new_edges_count) {
    edges_.reserve(new_edges_count);
}

Graph::iterator Graph::begin() {
    return edges_.begin();
}
Graph::iterator Graph::end() {
    return edges_.end();
}
Graph::const_iterator Graph::begin() const {
    return edges_.begin();
}
Graph::const_iterator Graph::end() const {
    return edges_.end();
}