#include <algorithm>
#include <iostream>
#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>
#include <random>
#include <vector>

#include "par_bfs.hpp"

static void bfs(const std::vector<std::vector<int>> &graph, std::vector<int> &dist) {

}

void par_bfs(const std::vector<std::vector<int>> &graph, std::vector<int> &dist) {
    if (!graph.empty()) {
        bfs(graph, dist);
    }
}