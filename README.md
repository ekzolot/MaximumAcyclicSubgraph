# Maximum Acyclic Subgraph

Implementation and experimental evaluation of algorithms for the **Maximum Acyclic Subgraph (MAS)** problem.

This project was developed as a part of university course on computational complexity.

## Overview

Given a directed graph \(G = (V, E)\), the **Maximum Acyclic Subgraph** problem asks for the largest subset of edges that forms an acyclic directed graph.

The problem is NP-hard, making exact algorithms infeasible for large instances. As a result, approximation and heuristic algorithms are commonly used in practice.

This project implements both exact and greedy algorithms and compares their accuracy on several families of directed graphs.


The proof of NP-hardness of the MAS problem is presented in the article, as well as the full description of both approximation algorithms and correctness proofs. 

The article text is in **article/MaximumAcyclicSubgraph.pdf**.

## Graph generators

The project contains generators for several graph families:

- Random directed graphs (Erdős–Rényi model)
- Tournaments
- Directed acyclic graphs (DAGs)
- "Nearly acyclic" graphs (DAGs with added noise)
- Graphs containing a Hamiltonian cycle
- Large synthetic benchmark graphs with a known optimal solution

These graph families allow the algorithms to be evaluated under different structural properties.


## Experimental evaluation

The algorithms were tested on multiple graph families.

For small graphs, the exact dynamic programming algorithm was used to compute the optimal solution.

For larger graphs, specially constructed graph families with known optimal solutions were used.

The reported performance measure is the average approximation ratio

`|E_algorithm| / |E_optimal|`

computed over multiple randomly generated graph instances.

# Main findings

The improved greedy heuristic consistently outperformed the classical greedy algorithm on all graph families considered in the experiments.

On completely random directed graphs (Erdős–Rényi model), the classical greedy algorithm achieved reasonably good average performance, especially on dense graphs (i.e., when the edge probability is high). However, on certain graph families, such as DAG-like graphs, its approximation ratio was much closer to the theoretical lower bound of 1/2. Moreover, it is easy to construct a graph on which the classical greedy algorithm achieves exactly this worst-case ratio. Such an example is presented at the end of the accompanying report.

The improved greedy heuristic demonstrated strong performance across all tested graph families, with an average approximation ratio of at least 0.94 in every experimental setting. An exhaustive search over small directed graphs did not reveal any instance on which the heuristic attains the theoretical lower bound of 1/2. Nevertheless, graphs on which the heuristic performs significantly worse than average do exist. One such example, for which the approximation ratio is 7/9, is presented at the end of the accompanying report.

