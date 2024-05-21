#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
const ll INF = numeric_limits<ll>::max();

vector <ll> dijkstra(int source, vector <vector<plli>> &graph, int n) {
    vector <ll> dist(n + 1, INF);
    priority_queue <plli, vector<plli>, greater<plli>> pq;


    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [current_distance, u] = pq.top();
        pq.pop();

        if (current_distance > dist[u]) continue;

        for (auto &[cost, v] : graph[u]) {
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

    int n, m;
    fin >> n >> m;

    vector <vector<plli>> graph(n + 1);
    vector <vector<plli>> reverse_graph(n + 1);

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
    vector <ll> dist_from_x = dijkstra(x, graph, n);
    vector <ll> dist_from_y = dijkstra(y, graph, n);
    vector <ll> dist_to_z = dijkstra(z, reverse_graph, n);

    ll min_cost = INF;

    for (int v = 1; v <= n; ++v) {
        if (dist_from_x[v] != INF &&
            dist_from_y[v] != INF &&
            dist_to_z[v] != INF) {
            ll total_cost = dist_from_x[v] + dist_from_y[v] + dist_to_z[v];
            if (total_cost < min_cost) {
                min_cost = total_cost;
            }
        }
    }

    fout << min_cost << '\n';

    fin.close();
    fout.close();
    return 0;
}
