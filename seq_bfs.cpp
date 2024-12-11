#include <algorithm>
#include <queue>
#include <vector>

#include "seq_bfs.hpp"

static void bfs(const std::vector<std::vector<int>> &graph, std::vector<int> &dist) {
    int size = graph.size();
    dist[0] = 0;
    std::queue<int> queue;
    queue.emplace(0);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int u : graph[v]) {
            if (dist[u] == size) {
                dist[u] = dist[v] + 1;
                queue.emplace(u);
            }
        }
    }
}

void seq_bfs(const std::vector<std::vector<int>> &graph, std::vector<int> &dist) {
    if (!graph.empty()) {
        bfs(graph, dist);
    }
}