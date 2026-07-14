#pragma once

#include <vector>

struct Edge {
    int from{};
    int to{};

    Edge(int from, int to);
};

class Graph {
public:

    Graph() = default;

    Graph(int vertex_count);

    Graph(int vertex_count, std::vector<Edge> edges);

    [[nodiscard]] int VertexCount() const;
    [[nodiscard]] int EdgeCount() const;

    void AddEdge(Edge edge);

    void ReserveEdges(int new_edges_count);

    using iterator = std::vector<Edge>::iterator;
    using const_iterator = std::vector<Edge>::const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;


private:

    int vertex_count_{};
    std::vector<Edge> edges_;
};

Graph BuildSubgraph(const Graph& graph, const std::vector<int>& order);