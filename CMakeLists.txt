cmake_minimum_required(VERSION 4.2)
project(complexity_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(complexity_project
        src/graph.cpp
        src/greedy.cpp
        src/smart_greedy.cpp
        src/honest_solution.cpp
        src/tests_generator.cpp
        src/tests.cpp
        src/main.cpp
)
