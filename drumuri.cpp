#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <limits>
#include <set>
#include <tuple>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;
const ll INF = numeric_limits<ll>::max();

vector <ll> dijkstra(int source, vector <vector<pii>> &graph) {
    int n = graph.size();
    vector <ll> dist(n, INF);
    priority_queue <pii, vector<pii>, greater<pii>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [current_distance, u] = pq.top();
        pq.pop();

        if (current_distance > dist[u]) continue;

        for (auto &[cost, v]: graph[u]) {
            ll distance = current_distance + cost;
            if (distance < dist[v]) {
                dist[v] = distance;
                pq.push({distance, v});
            }
        }
    }

    return dist;
}

int main() {
    ifstream fin("drumuri.in");
    ofstream fout("drumuri.out");

//    ifstream fin("/home/dominic/Documents/sem_4_facultate/PA/teme/tema2/public_tests/drumuri/input/0-drumuri.in");
//    ofstream fout("drumuri_test_py.out");



    int n, m;
    fin >> n >> m;

    vector <vector<pii>> graph(n + 1);
    vector <vector<pii>> reverse_graph(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        fin >> a >> b >> c;
        graph[a].push_back({c, b});
        reverse_graph[b].push_back({c, a});
    }

    int x, y, z;
    fin >> x >> y >> z;

    // Dijkstra from z on the reversed graph
    vector <ll> dist_from_z = dijkstra(z, reverse_graph);
    for (int node = 1; node <= n; ++node) {
        cout << "Distance from z to " << node << " = " << dist_from_z[node] << endl;
    }

// After computing distances from x and y in the original graph
    vector <ll> dist_from_x = dijkstra(x, graph);
    vector <ll> dist_from_y = dijkstra(y, graph);

    cout << "Distance from " << x << " to " << z << " = " << dist_from_z[x] << endl;
    cout << "Distance from " << y << " to " << z << " = " << dist_from_z[y] << endl;

// You can also print these to verify correctness immediately after calculation
    cout << "Distance from " << x << " to " << z << " = " << dist_from_x[z] << endl;
    cout << "Distance from " << y << " to " << z << " = " << dist_from_y[z] << endl;


    // We use sets to avoid duplicate edges and to sum the unique minimum costs
    set <tuple<int, int, ll>> min_cost_paths;

    for (int start: {x, y}) {
        vector <ll> dist = dijkstra(start, graph);

        // Check edges from the paths that are valid
        for (int u = 1; u <= n; ++u) {
            for (auto &[cost, v]: graph[u]) {
                // Ensure that using the edge (u, v) contributes to the shortest path from start to z
                if (dist[u] != INF && dist_from_z[v] != INF && dist[u] + cost + dist_from_z[v] == dist_from_z[start]) {
                    cout << "Edge (" << u << " -> " << v << ") with cost " << cost << " checked:" << endl;
                    cout << "  dist[" << u << "] = " << dist[u] << ", dist_from_z[" << v << "] = " << dist_from_z[v]
                         << endl;
                    cout << "  Sum: " << (dist[u] + cost + dist_from_z[v]) << " vs dist_from_z[start] = "
                         << dist_from_z[start] << endl;


                    min_cost_paths.insert({u, v, cost});
                }
            }
        }
    }

    ll min_cost_sum = 0;
    for (auto &[u, v, cost]: min_cost_paths) {
        cout << "Edge selected: " << u << " -> " << v << " with cost " << cost << endl;

        min_cost_sum += cost;
    }

    cout << "Minimum cost sum: " << min_cost_sum << endl;

    fout << min_cost_sum << endl;

    fin.close();
    fout.close();
    return 0;
}