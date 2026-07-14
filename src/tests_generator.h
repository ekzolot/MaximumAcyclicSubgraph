#include "graph.h"
#include "honest_solution.h"

Graph GenerateRandomGraph(int vertex_count, double edge_probability);

std::vector<Graph> EnumerateAllDirectedGraphs(int vertex_count);

Graph GenerateTournament(int vertex_count);

Graph GenerateDAG(int vertex_count, double edge_probability);

Graph GenerateHamiltonianGraph(int vertex_count, double edge_probability);

Graph GenerateNearlyDAG(int vertex_count, double edge_probability, double noise);

Graph GenerateAlmostDAG(int vertex_count, double edge_probability);

std::pair<Graph, int> GenerateBigGraph(int n, int components_number, double probability_inner, double probability_outer);