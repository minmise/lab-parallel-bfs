#include <iostream>

#include "test_generator.hpp"

void add_edge(std::vector<std::vector<int>> &graph, int v1, int v2) {
    graph[v1].emplace_back(v2);
    graph[v2].emplace_back(v1);
}

void gen_hypercube_graph(int size_base, int dimensions, std::vector<std::vector<int>> &graph) {
    int size = 1;
    for (int i = 0; i < dimensions; ++i) {
        size *= size_base;
    }
    graph.resize(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0, cur_diff = 1; j < dimensions; ++j, cur_diff *= size_base) {
            if (i + cur_diff < size && (i + cur_diff) / (cur_diff * size_base) == i / (cur_diff * size_base)) {
                add_edge(graph, i, i + cur_diff);
            }
        }
    }
}

void gen_hypercube_graph_with_dist(int size_base, int dimensions, std::vector<std::vector<int>> &graph, std::vector<int> &dist) {
    int size = 1;
    for (int i = 0; i < dimensions; ++i) {
        size *= size_base;
    }
    graph.resize(size);
    dist.resize(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0, cur_diff = 1; j < dimensions; ++j, cur_diff *= size_base) {
            if (i + cur_diff < size && (i + cur_diff) / (cur_diff * size_base) == i / (cur_diff * size_base)) {
                add_edge(graph, i, i + cur_diff);
            }
            dist[i] += (i % (cur_diff * size_base)) / cur_diff;
        }
    }
}