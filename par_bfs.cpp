#include <algorithm>
#include <atomic>
#include <iostream>
#include <parlay/delayed_sequence.h>
#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>
#include <random>
#include <vector>

#include "par_bfs.hpp"

static void bfs(const std::vector<std::vector<int>> &graph, std::vector<int> &dist) {
    int size = graph.size();
    dist[0] = 0;
    std::vector<std::atomic_int> used(size);
    used[0].store(1);
    parlay::parallel_for(1, size, [&](int i) {
        used[i].store(0);
    });
    parlay::sequence<int> cur_frontier{0};
    parlay::sequence<int> next_frontier;
    parlay::sequence<int> degs_pref;
    while (!cur_frontier.empty()) {
        int frontier_size = cur_frontier.size();
        degs_pref.resize(frontier_size);
        parlay::parallel_for(0, frontier_size, [&](int i) {
            degs_pref[i] = graph[cur_frontier[i]].size();
        });
        if (degs_pref.empty()) {
            break;
        }
        parlay::scan_inplace(degs_pref);
        next_frontier.clear();
        next_frontier.resize(degs_pref.back() + static_cast<int>(graph[cur_frontier.back()].size()), -1);
        parlay::parallel_for(0, frontier_size, [&](int v_ind) {
            int v = cur_frontier[v_ind];
            for (int u_ind = 0; u_ind < graph[v].size(); ++u_ind) {
                int u = graph[v][u_ind];
                int value = 0;
                if (used[u].compare_exchange_strong(value, 1)) {
                    dist[u] = dist[v] + 1;
                    next_frontier[degs_pref[v_ind] + u_ind] = u;
                }
            }
        });
        cur_frontier = parlay::filter(next_frontier, [](int val) {
            return val >= 0;
        });
    }
}

void par_bfs(const std::vector<std::vector<int>> &graph, std::vector<int> &dist) {
    if (!graph.empty()) {
        bfs(graph, dist);
    }
}