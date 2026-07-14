#include "tests.h"
#include <iostream>
#include <iomanip>

int main() {

    std::cout << std::fixed << std::setprecision(4);

    TestAlgorithm("Simple greedy algorithm",AcyclicSubgraph);
    TestAlgorithm("Improved greedy algorithm",SmartAcyclicSubgraph);

    return 0;
}