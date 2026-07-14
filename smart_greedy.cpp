#include "smart_greedy.h"
#include <limits>

enum class Side {
    Front,
    Back
};

namespace {
    struct Candidate {
        int vertex = -1;
        int degree_diff = std::numeric_limits<int>::min();
        Side side = Side::Front;

        bool operator<(const Candidate& other) const {
            return degree_diff < other.degree_diff;
        }
    };

    constexpr int kForcedChoice = std::numeric_limits<int>::max();

    Candidate EvaluateVertex(int vert, const std::vector<int>& in_degrees, const std::vector<int>& out_degrees) {
        if (in_degrees[vert] == 0) {
            return Candidate{vert, kForcedChoice, Side::Front};
        }
        if (out_degrees[vert] == 0) {
            return Candidate{vert, kForcedChoice, Side::Back};
        }
        if (in_degrees[vert] >= out_degrees[vert]) {
            return Candidate{vert, in_degrees[vert] - out_degrees[vert], Side::Back};
        }
        return Candidate{vert, out_degrees[vert] - in_degrees[vert], Side::Front};
    }
}

Graph SmartAcyclicSubgraph(const Graph& graph) {

    const int n = graph.VertexCount();

    std::vector<bool> is_alive(n, true);

    std::vector<int> in_degrees(n);
    std::vector<int> out_degrees(n);

    std::vector<std::vector<int>> incoming(n);
    std::vector<std::vector<int>> outgoing(n);

    for (const Edge& edge : graph) {
        ++in_degrees[edge.to];
        ++out_degrees[edge.from];
        outgoing[edge.from].push_back(edge.to);
        incoming[edge.to].push_back(edge.from);
    }

    std::vector<int> position(n);

    int front_idx = 0;
    int back_idx = n - 1;

    while (front_idx <= back_idx) {

        Candidate best;

        for (int vert = 0; vert < n; ++vert) {
            if (!is_alive[vert]) {
                continue;
            }
            Candidate current = EvaluateVertex(vert, in_degrees, out_degrees);

            best = std::max(best, current);
        }

        position[best.vertex] = best.side == Side::Front ? front_idx : back_idx;
        is_alive[best.vertex] = false;

        for (int vert : incoming[best.vertex]) {
            --out_degrees[vert];
        }
        for (int vert : outgoing[best.vertex]) {
            --in_degrees[vert];
        }

        if (best.side == Side::Front) {
            ++front_idx;
        } else {
            --back_idx;
        }

    }

    return BuildSubgraph(graph, position);
}