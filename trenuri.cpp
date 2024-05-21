#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

int main(void) {
    ifstream fin("trenuri.in");
    ofstream fout("trenuri.out");

    string start, destination;
    fin >> start >> destination;

    int m;
    fin >> m;

    unordered_map <string, vector<string>> graph;
    unordered_map<string, int> in_degree;
    unordered_map<string, int> dp;
    unordered_map<string, bool> visited;

    string x, y;
    for (int i = 0; i < m; ++i) {
        fin >> x >> y;

        // Construct the graph as adjacency list
        graph[x].push_back(y);

        // Count in-degree for each node
        in_degree[y]++;

        // Mark all cities as visited in the input (exists in the graph)
        visited[x] = false;
        visited[y] = false;
    }

    // Topological sorting using Kahn's Algorithm
    queue <string> q;

    // Find all nodes with zero in-degree to start topological sort
    for (auto &kv : visited) {
        if (in_degree[kv.first] == 0) {
            q.push(kv.first);
        }
    }

    vector <string> topo_order;
    // Perform topological sorting
    while (!q.empty()) {
        string node = q.front();
        q.pop();
        topo_order.push_back(node);
        for (const string &neighbor : graph[node]) {
            // Reduce in-degree of each neighbor
            in_degree[neighbor]--;

            // If in-degree becomes zero, enqueue the node
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Dynamic Programming to find the longest path from start to destination
    // Initialize DP table with start city having 1 (visited)
    dp[start] = 1;

    for (const string &node : topo_order) {
        // Process only reachable nodes
        if (dp.count(node)) {  // If there's a path to this node
            for (const string &neighbor : graph[node]) {
                // Update DP table:
                dp[neighbor] = max(dp[neighbor], dp[node] + 1);
            }
        }
    }

    // Output the result
    fout << dp[destination] << endl;

    fin.close();
    fout.close();
    return 0;
}
