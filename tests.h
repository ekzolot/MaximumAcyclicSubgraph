#include "tests_generator.h"
#include "greedy.h"
#include "honest_solution.h"
#include "smart_greedy.h"
#include <string>
#include <functional>


using SolutionFunc = std::function<Graph(const Graph&)>;

void TestAlgorithm(const std::string& name, const SolutionFunc& algorithm);