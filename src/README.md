# Maximum Acyclic Subgraph

A C++ implementation and experimental study of algorithms for the **Maximum Acyclic Subgraph (MAS)** problem.

The project was completed as part of a university course on computational complexity.

## Problem

Given a directed graph \(G = (V, E)\), the goal is to find the largest subset of edges that forms an acyclic subgraph.

The Maximum Acyclic Subgraph problem is NP-hard. The project compares the performance of 2 polynomial-time algorithms (the simple greedy algorithms and the one with added heuristic) that give 1/2-approximation of the solution.

## Graph generators

The project contains generators for several graph families:

- Random directed graphs (Erdős–Rényi model)
- Tournaments
- Directed acyclic graphs (DAGs)
- "Nearly acyclic" graphs (DAGs with added noise)
- Graphs containing a Hamiltonian cycle
- Large synthetic benchmark graphs with a known optimal solution


## Code files structure

```
graph.h / graph.cpp            Graph data structure
greedy.h / greedy.cpp            Classical greedy algorithm
smart_greedy.h / smart_greedy.cpp Improved greedy algorithm
honest_solution.h / .cpp         Exact solution found via dynamic programming approach
graph_generators.h / .cpp        Test graph generators
tests.h / tests.cpp              Experimental evaluation
main.cpp                         Entry point
```
