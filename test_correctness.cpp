#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

#include "par_bfs.hpp"
#include "seq_bfs.hpp"

bool test_dist_is_correct(const std::vector<int> &dist, const std::vector<int> &dist_expected) {
    for (int i = 0; i < dist_expected.size(); ++i) {
        if (dist[i] != dist_expected[i]) {
            return false;
        }
    }
    return true;
}

void add_edge(std::vector<std::vector<int>> &graph, int v1, int v2) {
    graph[v1].emplace_back(v2);
    graph[v2].emplace_back(v1);
}

void test_bfses(const std::vector<std::vector<int>> &graph, const std::vector<int> &dist_expected) {
    std::vector<int> dist_seq(graph.size(), graph.size());
    seq_bfs(graph, dist_seq);
    assert(test_dist_is_correct(dist_seq, dist_expected));
    //std::vector<int> dist_par(graph.size(), graph.size());
    //par_bfs(graph, dist_par);
    //assert(test_dist_is_correct(dist_par, dist_expected));
}

void test_empty() {
    std::vector<std::vector<int>> graph;
    std::vector<int> dist_expected;
    test_bfses(graph, dist_expected);    
}

void test_one_vertex() {
    std::vector<std::vector<int>> graph(1);
    std::vector<int> dist_expected{0};
    test_bfses(graph, dist_expected);
}

void test_one_edge() {
    std::vector<std::vector<int>> graph(2);
    add_edge(graph, 0, 1);
    std::vector<int> dist_expected{0, 1};
    test_bfses(graph, dist_expected);
}

void test_hedgehog() {
    int size = 10;
    std::vector<std::vector<int>> graph(size);
    std::vector<int> dist_expected(size, 1);
    dist_expected[0] = 0;
    for (int i = 1; i < size; ++i) {
        add_edge(graph, 0, i);
    }
    test_bfses(graph, dist_expected);
}

void test_bamboo() {
    int size = 10;
    std::vector<std::vector<int>> graph(size);
    std::vector<int> dist_expected(size);
    std::iota(dist_expected.begin(), dist_expected.end(), 0);
    for (int i = 1; i < size; ++i) {
        add_edge(graph, i - 1, i);
    }
    test_bfses(graph, dist_expected);
}

void test_disconnected() {
    int size = 10;
    std::vector<std::vector<int>> graph(size);
    std::vector<int> dist_expected(size, size); // edge weight == 1 => size == INF
    dist_expected[0] = 0;
    test_bfses(graph, dist_expected);
}

int main() {
    test_empty();
    test_one_vertex();
    test_one_edge();
    test_bamboo();
    test_hedgehog();
    test_disconnected();
    std::cout << "Correct!\n";
    return 0;    
}