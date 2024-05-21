# Tema 1 Proiectarea Algoritmilor - Politisti, Programatori si Scandal
**Staicu Dan-Dominic 321CA 2024**

## 1. COUNT (Numarare)

### Solution Description

The program aims to find the number of distinct elementary paths from node 1 to node N that are common to two given Directed Acyclic Graphs (DAGs).
Each graph consists of N nodes and M directed edges.
An elementary path is defined as a sequence of nodes where each consecutive node pair has an edge between them, starting from node 1 and ending at node N, without repeating any node in the path.

### Approach

1. **Reading Input**: The program reads two sets of edges defining two DAGs from an input file.
2. **Graph Intersection**: Constructs a new adjacency list representing the intersection of the two graphs. This means including an edge from node A to B only if it appears in both graphs.
3. **Topological Sorting**: Performs a topological sort on the intersection graph to ensure that nodes are processed in a linear order without precedents.
4. **Dynamic Programming (DP)**: Uses a DP approach to count the number of ways to reach each node starting from node 1, leveraging the order provided by topological sorting. The count for each node is based on the sum of ways to reach its predecessors.
5. **Result Output**: Writes the number of paths from node 1 to node N to an output file.


### Complexity

- **Time Complexity**: The dominant factor is the graph construction and the topological sort, each of which operates in O(N + M) time for each graph. The DP computation also runs in O(N + M). Thus, the overall complexity is approximately O(N + M).
- **Space Complexity**: Space is mainly used by the adjacency lists and the DP array, both sized proportionally to N and M, leading to a space complexity of O(N + M).


### How does this work?

1. **Intersecting Graphs**: By constructing the adjacency list only for edges that exist in both input graphs, the program effectively filters out paths that aren't common to both graphs.
2. **Topological Sort**: Since we're dealing with DAGs, a topological sort allows us to process each node after all its dependencies (predecessors) have been processed, ensuring that when we calculate the number of paths to a node, all paths leading to it have been accounted for.
3. **Dynamic Programming**: Starting from the initial node (node 1), which we know can be reached in exactly one way (from itself), the program iteratively calculates the number of ways to reach every other node by summing up the ways to reach each of its predecessors.
4. **Modulo Operation**: Since the results are required modulo 10^9 + 7, each addition operation within the DP array uses a modulo to ensure that numbers do not overflow and remain within manageable bounds.

By integrating these methods, the program efficiently calculates the desired count of paths, which are common in both graphs, from node 1 to node N.

## 2. TRAINS (Trenuri)

### Solution Description

The program aims to determine the maximum number of distinct cities that Bogdan can visit on his journey from a given start city to a destination city.
This is achieved by calculating the longest path through a directed graph that represents cities and direct train connections between them.

### Approach

1. **Reading and Graph Construction**: The program reads city pairs representing direct train routes and constructs a directed graph.
2. **Topological Sorting**: Implements Kahn's Algorithm for topological sorting of the directed graph to ensure that nodes are processed in a linear order without circular dependencies.
3. **Dynamic Programming (DP)**: Utilizes dynamic programming to determine the longest path from the start city to the destination city based on the topologically sorted nodes. This approach maximizes the number of cities visited by considering each node in the order and updating the maximum reachable cities from it.
4. **Output the Maximum Path Length**: The number of distinct cities visited on the longest path is printed as the result.

### Complexity

- **Time Complexity**: The most computationally demanding tasks are constructing the graph and performing the topological sort, both of which require O(M) time, where M is the number of direct train connections. The dynamic programming step also runs in O(N + M) time, where N is the number of cities.
- **Space Complexity**: Space consumption is mainly due to the graph storage and the dynamic programming table, both scaled by O(N + M).

### How does this work?

1. **Graph Representation**: The graph is represented using adjacency lists, which efficiently store outgoing edges for each city. This structure supports the direct mapping needed for topological sorting and dynamic programming.
2. **Topological Sorting (Kahn's Algorithm)**: This sorting is crucial because it provides a way to process each city in a sequence that respects the direction of the train routes. Without such sorting, calculating the longest path accurately would not be possible in the presence of directed edges.
3. **Dynamic Programming**: Starting from the initial city, which is counted as visited (hence starts from 1), the DP algorithm iterates over each city in the topological order. For each city, it updates the count of the maximum cities visited for each of its neighbors based on the maximum paths leading to it.
4. **Output**: The result, which is stored in the DP table at the destination city key, represents the maximum number of distinct cities that can be visited from the start to the destination city.


## 3. MANDATORY ROADS (Drumuri Obligatorii)

### Solution Description

The program aims to determine the minimum sum of a subset of edges in a directed graph with weights that allows at least one path from node `x` to node `z` and one path from node `y` to node `z`.
The graph consists of `n` nodes and `m` directed edges, with each edge having an associated cost.

### Approach - Used Algorithms

1. **Graph Setup**: Two representations of the graph are maintained: the original directed graph and its reverse. This setup is crucial to calculate shortest paths to and from node `z`.
2. **Dijkstra's Algorithm**:
    - Compute the shortest paths from `x` to all nodes (`dist_from_x`).
    - Compute the shortest paths from `y` to all nodes (`dist_from_y`).
    - Compute the shortest paths from `z` to all nodes on the reversed graph (`dist_to_z`), effectively calculating the shortest path from all nodes to `z` in the original graph.
3. **Edge Selection**:
    - Evaluate each node `v` and compute the sum of `dist_from_x[v]`, `dist_from_y[v]`, and `dist_to_z[v]`. This sum represents the minimum total cost to travel from `x` and `y` to `z` via `v`.
    - The minimum of these sums across all nodes gives the required answer.


### Complexity

- **Time Complexity**: O(M log N) for each Dijkstra's execution, leading to O(3 * M log N) due to three separate runs of the algorithm. This complexity stems from the use of priority queues in Dijkstra's algorithm, where each edge is relaxed potentially multiple times.
- **Space Complexity**: O(N + M) due to storage requirements for the graph and auxiliary data structures like distances and priority queues.


### How does this work?

1. **Graph Construction**: The graph is stored using adjacency lists, where each list contains pairs representing the cost and destination node for each outgoing edge. The reverse graph is similarly constructed but with edges reversed, aiding the computation of shortest paths to `z`.
2. **Dijkstra's Implementation**: Each execution of Dijkstra's starts by setting the distance to the source node as zero and pushing it into a priority queue. The algorithm then repeatedly extracts the node with the smallest known distance, updating the shortest paths to its neighbors.
3. **Optimal Subset Calculation**: After obtaining the shortest path arrays, the algorithm iterates over all nodes. For each node, it checks if it is reachable from `x`, `y`, and can reach `z`. It sums the costs from the three shortest path calculations to get the total minimum cost involving that node.
4. **Output the Result**: The minimum of all valid node sums is outputted, representing the least cost to fulfill the problem's requirements.


