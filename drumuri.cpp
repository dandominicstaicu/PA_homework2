#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef long long ll;
typedef pair<ll, int> plli; // pair of ll and int
const ll INF = numeric_limits<ll>::max();

// Function to perform Dijkstra's algorithm to find the shortest path from
// a source node in a weighted graph
vector <ll> dijkstra(int source, vector <vector<plli>> &graph, int n) {
    // Distance vector initialized with infinity
    vector <ll> dist(n + 1, INF);

    // Min-heap priority queue to manage the next node to process
    priority_queue <plli, vector<plli>, greater<plli>> pq;


    dist[source] = 0; // Starting node has distance 0 to itself
    pq.push({0, source}); // Push the src node with distance 0 into the queue

    while (!pq.empty()) {
        // Get the node with the smallest distance
        auto [current_distance, u] = pq.top();
        pq.pop();

        // If the distance in the priority queue is greater than the current
        // known distance, skip processing
        if (current_distance > dist[u])
            continue;

        // Relax edges outgoing from node u
        for (auto &[cost, v] : graph[u]) {
            ll distance = current_distance + cost;

            // If the new calculated distance is smaller,
            // update it and push to the queue
            if (distance < dist[v]) {
                dist[v] = distance;
                pq.push({distance, v});
            }
        }
    }

    // Return the distance vector containing the shortest paths
    // from source to all other nodes
    return dist;
}

int main() {
    ifstream fin("drumuri.in");
    ofstream fout("drumuri.out");

    int n, m;
    fin >> n >> m;

    // Graph and reverse graph representation
    vector <vector<plli>> graph(n + 1);
    vector <vector<plli>> reverse_graph(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;

        // Read each edge with cost
        fin >> a >> b >> c;

        // Add edge to the graph.
        graph[a].push_back({c, b});

        // Add edge to the reverse graph
        reverse_graph[b].push_back({c, a});
    }

    int x, y, z;
    fin >> x >> y >> z;

    // Perform Dijkstra's algorithm from x, y on graph
    vector <ll> dist_from_x = dijkstra(x, graph, n);
    vector <ll> dist_from_y = dijkstra(y, graph, n);

    // ... and from z on the reversed graph
    vector <ll> dist_to_z = dijkstra(z, reverse_graph, n);

    // Initialize the minimum cost as infinity
    ll min_cost = INF;

    // Calculate the minimum sum of distances that connects x, y to z
    // through any node v
    for (int v = 1; v <= n; ++v) {
        if (dist_from_x[v] != INF &&
            dist_from_y[v] != INF &&
            dist_to_z[v] != INF) {
            ll total_cost = dist_from_x[v] + dist_from_y[v] + dist_to_z[v];

            // Update the minimum cost if a new lower cost is found
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
