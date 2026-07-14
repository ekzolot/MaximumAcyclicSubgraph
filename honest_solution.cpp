#include "honest_solution.h"
#include <algorithm>
#include <vector>

Graph MaximumAcyclicSubgraph(const Graph& graph) {

    const int n = graph.VertexCount();

    std::vector<unsigned long long> adj(n);
    for (const Edge& edge : graph) {
        adj[edge.from] |= (1ULL << edge.to);
    }

    std::vector<unsigned long long> dp(1ULL << n);
    std::vector<long long> first(1ULL << n, -1);
    for (unsigned long long mask = 1; mask < (1ULL << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1ULL << i)) {
                if (dp[mask ^ (1ULL << i)] + std::popcount(static_cast<unsigned long long>(mask & adj[i])) >= dp[mask]) {
                    dp[mask] = dp[mask ^ (1ULL << i)] + std::popcount(static_cast<unsigned long long>(mask & adj[i]));
                    first[mask] = i;
                }
            }
        }
    }

    std::vector<int> position(n);
    unsigned long long current_mask = (1ULL << n) - 1;
    int cur_pos = 0;
    while (first[current_mask] != -1) {
        position[first[current_mask]] = cur_pos++;
        current_mask ^= (1ULL << first[current_mask]);
    }


    Graph answer;
    answer.ReserveEdges(dp[(1LL << n) - 1]);
    for (const Edge& edge : graph) {
        if (position[edge.from] < position[edge.to]) {
            answer.AddEdge(edge);
        }
    }
    return answer;
}