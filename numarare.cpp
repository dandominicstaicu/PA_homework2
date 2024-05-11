#include <fstream>
#include <vector>
#include <queue>
#include <set>

#define MOD 1000000007

using namespace std;

// Topologically sort a Directed Acyclic Graphs (DAG)
vector<int> topological_sort(int n, const vector <vector<int>> &adj) {
    vector<int> in_degree(n + 1, 0);  // Vector to store the in-degree of each node
    vector<int> sorted_nodes; // Vector to store nodes in topologically sorted order
    queue<int> q; // Queue to manage nodes with in-degree of 0 during sorting

    // Compute the internal degree for each node
    for (int u = 1; u <= n; ++u) {
        for (int v: adj[u]) {
            in_degree[v]++;
        }
    }

    // Add the nodes with 0 degree in a queue
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    // Process the nodes in topological order
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        sorted_nodes.push_back(node); // Add to the result list

        // Decrement in-degree of neighbors and enqueue if in-degree becomes zero
        for (int neighbor: adj[node]) {
            --in_degree[neighbor];
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Return the list of topologically sorted nodes
    return sorted_nodes;
}

// Compute the number of elementary ways
int count_common_paths(int n, vector <pair<int, int>> &edges1, vector <pair<int, int>> &edges2) {
    vector <set<int>> adj1(n + 1); // Adjacency list for the first graph
    vector <vector<int>> adj_common(n + 1); // Adjacency list for the intersection of the graphs
    vector<int> dp(n + 1, 0); // Dynamic programming table to store the number of paths to each node

    // Build the adjacency list for the 1st graph
    for (auto &edge: edges1) {
        adj1[edge.first].insert(edge.second);
    }

    // Build the adjacency list for the intersection of the two graphs
    for (auto &edge: edges2) {
        if (adj1[edge.first].count(edge.second)) {
            adj_common[edge.first].push_back(edge.second);
        }
    }

    // Get nodes in topological order
    vector<int> sorted_nodes = topological_sort(n, adj_common);

    // Set dp[1] = 1 because there is only one way from 1 to 1
    dp[1] = 1;

    // Calculate the number of paths to each node using the topologically sorted list
    for (int node: sorted_nodes) {
        for (int neighbor: adj_common[node]) {
            dp[neighbor] = (dp[neighbor] + dp[node]) % MOD; // Update the path count using modulo operation
        }
    }

    // Return the number of paths from node 1 to node n
    return dp[n];
}

int main(void) {
    ifstream fin("numarare.in");
    ofstream fout("numarare.out");

    int n, m;
    fin >> n >> m;

    // Vectors to store edges for the two graphs
    vector <pair<int, int>> edges1(m), edges2(m);

    for (int i = 0; i < m; i++) {
        fin >> edges1[i].first >> edges1[i].second;
    }

    for (int i = 0; i < m; i++) {
        fin >> edges2[i].first >> edges2[i].second;
    }

    fout << count_common_paths(n, edges1, edges2) << endl;

    fin.close();
    fout.close();
    return 0;
}
