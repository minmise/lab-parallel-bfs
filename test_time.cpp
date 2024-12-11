#include <chrono>
#include <iostream>
#include <vector>

#include "seq_bfs.hpp"
#include "par_bfs.hpp"
#include "test_generator.hpp"

int test_time_seq(const std::vector<std::vector<int>> &graph) {
    std::vector<int> dist(graph.size(), graph.size());
    auto start = std::chrono::high_resolution_clock::now();
    seq_bfs(graph, dist);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int test_time_par(const std::vector<std::vector<int>> &graph) {
    std::vector<int> dist(graph.size(), graph.size());
    auto start = std::chrono::high_resolution_clock::now();
    par_bfs(graph, dist);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    const int t = 5;
    const int dimensions = 3;
    const int size_base = 500;
    std::vector<std::vector<int>> graph;
    gen_hypercube_graph(size_base, dimensions, graph);
    int sum_seq = 0;
    int sum_par = 0;
    std::cout << "start\n";
    for (int i = 0; i < t; ++i) {
        int value_seq = test_time_seq(graph);
        int value_par = test_time_par(graph);
        sum_seq += value_seq;
        sum_par += value_par;
        std::cout << "launch " << i + 1 << " seq time: " << value_seq << " ms; par time: " << value_par << " ms\n";
    }
    std::cout << "seq average time: " << sum_seq / t << " ms; par average time: " << sum_par / t << " ms\n";
    return 0;
}