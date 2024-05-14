#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

struct Edge {
    int node;
    long long cost;
};

vector<long long> dijkstra(int n, const vector<vector<Edge>>& graph, int start) {
    vector<long long> dist(n + 1, INF);
    dist[start] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.node;
            long long weight = edge.cost;
            long long distance = current_dist + weight;
            if (distance < dist[v]) {
                dist[v] = distance;
                pq.push({distance, v});
            }
        }
    }

    return dist;
}

void solve(const string& filename_in, const string& filename_out) {
    ifstream infile(filename_in);
    ofstream outfile(filename_out);

    int N, M;
    infile >> N >> M;

    vector<vector<Edge>> graph(N + 1);
    vector<vector<Edge>> reverse_graph(N + 1);

    for (int i = 0; i < M; ++i) {
        int a, b;
        long long c;
        infile >> a >> b >> c;
        graph[a].push_back({b, c});
        reverse_graph[b].push_back({a, c});
    }

    int x, y, z;
    infile >> x >> y >> z;

    vector<long long> dist_from_x = dijkstra(N, graph, x);
    vector<long long> dist_from_y = dijkstra(N, graph, y);
    vector<long long> dist_to_z = dijkstra(N, reverse_graph, z);

    long long min_cost = INF;

    for (int v = 1; v <= N; ++v) {
        if (dist_from_x[v] != INF && dist_from_y[v] != INF && dist_to_z[v] != INF) {
            long long total_cost = dist_from_x[v] + dist_from_y[v] + dist_to_z[v];
            if (total_cost < min_cost) {
                min_cost = total_cost;
            }
        }
    }

    outfile << min_cost << endl;
}

int main() {
    solve("drumuri.in", "drumuri.out");
    return 0;
}
