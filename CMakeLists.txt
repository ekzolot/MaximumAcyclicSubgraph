cmake_minimum_required(VERSION 4.2)
project(complexity_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(complexity_project
        graph.cpp
        greedy.cpp
        smart_greedy.cpp
        honest_solution.cpp
        tests_generator.cpp
        tests.cpp
        main.cpp
)
