#include "tests.h"

#include <iostream>
#include <vector>

namespace {

using GeneratorFunc = std::function<Graph()>;

double Accuracy(const Graph& found, const Graph& optimal) {
    if (optimal.EdgeCount() == 0) {
        return 1.0;
    }
    return static_cast<double>(found.EdgeCount()) / optimal.EdgeCount();
}

double Evaluate(const SolutionFunc& algorithm, const GeneratorFunc& generator, int experiments) {
    double average = 0.0;
    for (int i = 0; i < experiments; ++i) {

        Graph graph = generator();

        Graph exact = MaximumAcyclicSubgraph(graph);
        Graph answer = algorithm(graph);

        average += Accuracy(answer, exact);

        if (answer.EdgeCount() > exact.EdgeCount()) {
            std::cout << "mistake!\n";
            std::cout << graph.VertexCount() << "\n";
            for (Edge e : graph) {
                std::cout << "{" << e.from << ", " << e.to << "}" << ",\n";
            }

        }
    }

    return average / experiments;
}

double EvaluateDAG(const SolutionFunc& algorithm, const GeneratorFunc& generator, int experiments) {

    double average = 0.0;
    for (int i = 0; i < experiments; ++i) {

        Graph graph = generator();

        Graph answer = algorithm(graph);

        average += graph.EdgeCount() == 0 ? 1.0 : static_cast<double>(answer.EdgeCount()) / graph.EdgeCount();
    }

    return average / experiments;
}

double EvaluateAlmostDAG(const SolutionFunc& algorithm,
    const std::function<std::pair<Graph, int>()>& generator, int experiments) {

    double average = 0.0;

    for (int i = 0; i < experiments; ++i) {
        auto [graph, optimum] = generator();
        Graph answer = algorithm(graph);
        average += optimum == 0 ? 1.0 : static_cast<double>(answer.EdgeCount()) / optimum;
    }

    return average / experiments;
}
}


void TestAlgorithm(const std::string& name, const SolutionFunc& algorithm) {

    const std::vector<double> probabilities = {0.15, 0.3, 0.4, 0.5, 0.6, 0.7, 0.85};

    const std::vector<double> probabilities_with_zero = {0.0, 0.15, 0.3, 0.4, 0.5, 0.6, 0.7, 0.85};

    const std::vector<double> noises = {0.05, 0.1, 0.2, 0.3};

    std::cout << "\n=========================================\n";
    std::cout << name << '\n';
    std::cout << "=========================================\n\n";

    std::cout << "Random graphs\n";

    for (double p : probabilities) {

        double accuracy = Evaluate(algorithm,
            [p]() {  return GenerateRandomGraph(10 + rand() % 10, p);   },
            50);

        std::cout << "p = " << p << " : " << accuracy << '\n';
    }

    std::cout << "\nAll graphs on 5 vertices\n";

    auto graphs = EnumerateAllDirectedGraphs(5);

    double average = 0.0;

    for (const Graph& graph : graphs) {
        average += Accuracy(algorithm(graph),MaximumAcyclicSubgraph(graph));
    }
    average /= graphs.size();
    std::cout << average << "\n\n";

    std::cout << "Tournaments\n";

    std::cout << Evaluate(algorithm,
               [] {   return GenerateTournament(10 + rand() % 10);  },
               100) << "\n\n";

    std::cout << "DAGs\n";

    for (double p : probabilities) {

        std::cout << "p = " << p << " : " << EvaluateDAG(algorithm,
                   [p] {   return GenerateDAG( 100 + rand() % 900, p);   },
                   100) << '\n';
    }

    std::cout << "\nHamiltonian graphs\n";

    for (double p : probabilities_with_zero) {

        std::cout << "p = " << p << " : " << Evaluate(algorithm,
                   [p] {   return GenerateHamiltonianGraph(10 + rand() % 10, p);  },
                   50) << '\n';
    }

    std::cout << "\nNearly DAGs\n";

    for (double p : probabilities) {
        for (double noise : noises) {

            std::cout << "p = " << p << ", noise = " << noise << " : "
                      << Evaluate(algorithm,
                       [p, noise] {   return GenerateNearlyDAG(10 + rand() % 10, p, noise);  },
                       50) << '\n';
        }
    }

    std::cout << "\nAlmost DAGs\n";

    for (double p : probabilities) {

        std::cout << "p = " << p << " : " << EvaluateDAG(algorithm,
                   [p] {    return GenerateAlmostDAG(100 + rand() % 900, p);    },
                   100) << '\n';
    }

    std::cout << "\nBig graphs\n";

    for (double inner : probabilities) {
        for (double outer : probabilities) {

            std::cout << "inner = " << inner << ", outer = " << outer << " : "
                << EvaluateAlmostDAG(algorithm,
                       [inner, outer] {   return GenerateBigGraph(5 + rand() % 10,100 + rand() % 100, inner, outer);    },
                       100) << '\n';
        }
    }

    std::cout << '\n';
}
