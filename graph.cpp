#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <climits>
using namespace std;

class Graph {
    int V;
    bool directed;
    unordered_map<int, vector<int>> adj;

public:
    Graph(int vertices, bool isDirected = false)
        : V(vertices), directed(isDirected) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    void bfs(int start) {
        unordered_set<int> visited;
        queue<int> q;

        visited.insert(start);
        q.push(start);

        cout << "BFS from " << start << ": ";
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    void dfsHelper(int node, unordered_set<int>& visited) {
        visited.insert(node);
        cout << node << " ";
        for (int neighbor : adj[node]) {
            if (!visited.count(neighbor))
                dfsHelper(neighbor, visited);
        }
    }

    void dfs(int start) {
        unordered_set<int> visited;
        cout << "DFS from " << start << ": ";
        dfsHelper(start, visited);
        cout << "\n";
    }

    void dfsIterative(int start) {
        unordered_set<int> visited;
        stack<int> st;
        st.push(start);

        cout << "DFS (iterative) from " << start << ": ";
        while (!st.empty()) {
            int node = st.top(); st.pop();
            if (visited.count(node)) continue;
            visited.insert(node);
            cout << node << " ";
            for (int neighbor : adj[node])
                if (!visited.count(neighbor))
                    st.push(neighbor);
        }
        cout << "\n";
    }

    bool hasCycleUndirected() {
        unordered_set<int> visited;

        function<bool(int, int)> dfs = [&](int node, int parent) -> bool {
            visited.insert(node);
            for (int neighbor : adj[node]) {
                if (!visited.count(neighbor)) {
                    if (dfs(neighbor, node)) return true;
                } else if (neighbor != parent) {
                    return true;
                }
            }
            return false;
        };

        for (auto& [node, _] : adj)
            if (!visited.count(node))
                if (dfs(node, -1)) return true;

        return false;
    }

    // Topological sort (only for DAGs)
    void topoSortHelper(int node, unordered_set<int>& visited, stack<int>& st) {
        visited.insert(node);
        for (int neighbor : adj[node])
            if (!visited.count(neighbor))
                topoSortHelper(neighbor, visited, st);
        st.push(node);
    }

    void topologicalSort() {
        unordered_set<int> visited;
        stack<int> st;

        for (auto& [node, _] : adj)
            if (!visited.count(node))
                topoSortHelper(node, visited, st);

        cout << "Topological order: ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << "\n";
    }

    void printAdjList() {
        cout << "Adjacency List:\n";
        for (auto& [node, neighbors] : adj) {
            cout << "  " << node << " -> ";
            for (int n : neighbors) cout << n << " ";
            cout << "\n";
        }
    }
};

// Weighted graph for Dijkstra
class WeightedGraph {
    int V;
    unordered_map<int, vector<pair<int,int>>> adj; // {neighbor, weight}

public:
    WeightedGraph(int vertices) : V(vertices) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dijkstra(int src) {
        unordered_map<int, int> dist;
        for (auto& [node, _] : adj) dist[node] = INT_MAX;
        dist[src] = 0;

        // min-heap: {dist, node}
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();

            if (d > dist[u]) continue;

            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Dijkstra from " << src << ":\n";
        for (auto& [node, d] : dist)
            cout << "  " << src << " -> " << node << " : " << d << "\n";
    }
};

int main() {
    cout << "=== Undirected Graph ===\n";
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    g.printAdjList();
    g.bfs(0);
    g.dfs(0);
    g.dfsIterative(0);
    cout << "Has cycle: " << (g.hasCycleUndirected() ? "yes" : "no") << "\n";

    cout << "\n=== Directed Graph (DAG) - Topological Sort ===\n";
    Graph dag(6, true);
    dag.addEdge(5, 2);
    dag.addEdge(5, 0);
    dag.addEdge(4, 0);
    dag.addEdge(4, 1);
    dag.addEdge(2, 3);
    dag.addEdge(3, 1);
    dag.topologicalSort();

    cout << "\n=== Weighted Graph - Dijkstra ===\n";
    WeightedGraph wg(5);
    wg.addEdge(0, 1, 4);
    wg.addEdge(0, 2, 1);
    wg.addEdge(2, 1, 2);
    wg.addEdge(1, 3, 1);
    wg.addEdge(2, 3, 5);
    wg.addEdge(3, 4, 3);
    wg.dijkstra(0);

    return 0;
}
