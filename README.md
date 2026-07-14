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

The improved greedy heuristic consistently outperformed the classical greedy algorithm on all tested graph families. 

Although on absolutely random directed graphs (Erdős–Rényi model) simple greedy algorithm performed not badly on average, especially on dense graphs (where the probability of edge is high), on some specific types of graphs, such as DAGs or others, simple algorithm's accuracy is quite close to the theoretical minimum of 1/2. Actually, it's easy to provide an example of a graph where the accuracy of simple greedy algorithm is exactly 1/2. This example is provided in the end of the article's text.

THe improved greedy algorithm heuristics demonstrated the great performance of all of the test groups (the average accuracy is always at leat 0.94). By small size graph consideration, I wasn't able to find a graph on which it reaches the theoretical minimum accuracy rate of 1/2. Nevertheless, there still exist graphs on which the performance of improved greedy heuristic is way lower then the average ones. The example of such graph (with the accuracy score of 7/9) is provided in the end of the article.
