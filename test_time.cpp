#include <chrono>
#include <iostream>
#include <vector>

#include "seq_bfs.hpp"
#include "par_bfs.hpp"

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
    /*const int t = 5;
    const int size = 500 * 500 * 500;
    int sum_seq = 0;
    int sum_par = 0;
    for (int i = 0; i < t; ++i) {
        int *arr = new int[size];
        gen_test_random(arr, size);
        int *arr_copy = new int[size];
        for (int j = 0; j < size; ++j) {
            arr_copy[j] = arr[j];
        }
        int value_seq = test_time_seq(arr, size);
        int value_par = test_time_par(arr_copy, size);
        delete[] arr;
        delete[] arr_copy;
        sum_seq += value_seq;
        sum_par += value_par;
        std::cout << "test " << i + 1 << " seq time: " << value_seq << " ms; par time: " << value_par << " ms\n";
    }
    std::cout << "seq average time: " << sum_seq / t << " ms; par average time: " << sum_par / t << " ms\n";
    return 0;*/
}