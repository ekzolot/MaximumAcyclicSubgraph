#include "tests_generator.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

namespace {

std::mt19937& Generator() {
    static std::mt19937 generator(std::random_device{}());
    return generator;
}

bool Bernoulli(double probability) {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(Generator()) < probability;
}

std::vector<int> RandomPermutation(int vertex_count) {
    std::vector<int> permutation(vertex_count);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(), Generator());
    return permutation;
}

Edge DecodeEdge(int id, int vertex_count) {
    int from = id / (vertex_count - 1);
    int to = id % (vertex_count - 1);
    if (to >= from) {
        ++to;
    }
    return {from, to};
}

}

Graph GenerateRandomGraph(int vertex_count, double edge_probability) {

    Graph graph(vertex_count);

    for (int from = 0; from < vertex_count; ++from) {
        for (int to = 0; to < vertex_count; ++to) {
            if (from == to) {
                continue;
            }
            if (Bernoulli(edge_probability)) {
                graph.AddEdge({from, to});
            }
        }
    }

    return graph;
}

std::vector<Graph> EnumerateAllDirectedGraphs(int vertex_count) {
    const int edge_count = vertex_count * (vertex_count - 1);
    std::vector<Graph> graphs;

    for (long long mask = 1; mask < (1LL << edge_count); ++mask) {
        Graph graph(vertex_count);
        for (int edge = 0; edge < edge_count; ++edge) {
            if ((mask & (1LL << edge)) == 0) {
                continue;
            }
            graph.AddEdge(DecodeEdge(edge, vertex_count));
        }
        graphs.push_back(std::move(graph));
    }

    return graphs;
}

Graph GenerateTournament(int vertex_count) {
    Graph graph(vertex_count);

    for (int u = 0; u < vertex_count; ++u) {
        for (int v = 0; v < u; ++v) {
            if (Bernoulli(0.5)) {
                graph.AddEdge({u, v});
            } else {
                graph.AddEdge({v, u});
            }
        }
    }

    return graph;
}

Graph GenerateDAG(int vertex_count, double edge_probability) {

    Graph graph(vertex_count);
    std::vector<int> order = RandomPermutation(vertex_count);

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = 0; j < i; ++j) {
            if (Bernoulli(edge_probability)) {
                graph.AddEdge({order[j], order[i]});
            }
        }
    }

    return graph;
}

Graph GenerateHamiltonianGraph(int vertex_count, double edge_probability) {

    Graph graph(vertex_count);
    std::vector<int> order = RandomPermutation(vertex_count);
    std::vector<int> next(vertex_count);

    for (int i = 0; i < vertex_count; ++i) {
        int from = order[i];
        int to = order[(i + 1) % vertex_count];
        graph.AddEdge({from, to});
        next[from] = to;
    }

    for (int from = 0; from < vertex_count; ++from) {
        for (int to = 0; to < vertex_count; ++to) {
            if (from == to || next[from] == to) {
                continue;
            }
            if (Bernoulli(edge_probability)) {
                graph.AddEdge({from, to});
            }
        }
    }

    return graph;
}

Graph GenerateNearlyDAG(int vertex_count, double edge_probability, double noise) {

    Graph graph(vertex_count);
    std::vector<int> order = RandomPermutation(vertex_count);

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = 0; j < i; ++j) {
            if (Bernoulli(edge_probability)) {
                graph.AddEdge({order[j], order[i]});
            }
            if (Bernoulli(noise)) {
                graph.AddEdge({order[i], order[j]});
            }
        }
    }

    return graph;
}

Graph GenerateAlmostDAG(int vertex_count,
                        double edge_probability) {

    Graph graph(vertex_count);
    std::vector<int> order = RandomPermutation(vertex_count);
    std::vector<int> next(vertex_count);

    for (int i = 0; i < vertex_count; ++i) {
        int from = order[i];
        int to = order[(i + 1) % vertex_count];
        graph.AddEdge({from, to});
        next[from] = to;
    }

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = i + 1; j < vertex_count; ++j) {
            if (next[order[i]] == order[j]) {
                continue;
            }
            if (Bernoulli(edge_probability)) {
                graph.AddEdge({order[i], order[j]});
            }
        }
    }

    return graph;
}

std::pair<Graph, int> GenerateBigGraph(int vertex_count, int components_number, double probability_inner, double probability_outer) {

    Graph graph(vertex_count * components_number);
    int answer = 0;

    for (int comp = 0; comp < components_number; ++comp) {
        Graph small_graph = GenerateRandomGraph(vertex_count, probability_inner);
        for (const Edge& e : small_graph) {
            graph.AddEdge(Edge{e.from + comp * vertex_count, e.to + comp * vertex_count});
        }
        answer += MaximumAcyclicSubgraph(small_graph).EdgeCount();
    }
    for (int from_comp = 0; from_comp < components_number; ++from_comp) {
        for (int to_comp = from_comp + 1; to_comp < components_number; ++to_comp) {
            for (int from_vert = 0; from_vert < vertex_count; ++from_vert) {
                for (int to_vert = 0; to_vert < vertex_count; ++to_vert) {
                    if (Bernoulli(probability_outer)) {
                        graph.AddEdge(Edge{from_comp * vertex_count + from_vert, to_comp * vertex_count + to_vert});
                        ++answer;
                    }
                }
            }
        }
    }

    int total_vert_count = vertex_count * components_number;

    std::vector<int> order = RandomPermutation(total_vert_count);

    for (auto& edge : graph) {
        edge.from = order[edge.from];
        edge.to = order[edge.to];
    }

    return std::make_pair(graph, answer);
}