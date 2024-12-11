#ifndef TEST_GENERATOR_HPP_
#define TEST_GENERATOR_HPP_

#include <vector>

void add_edge(std::vector<std::vector<int>> &graph, int v1, int v2);

void gen_hypercube_graph(int size_base, int dimensions, std::vector<std::vector<int>> &graph);

void gen_hypercube_graph_with_dist(int size_base, int dimensions, std::vector<std::vector<int>> &graph, std::vector<int> &dist);

#endif