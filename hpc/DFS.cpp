#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void parallelDFS(int start, int target) {
        vector<bool> visited(V, false);
        bool found = false;

        cout << "Parallel DFS starting from node " << start << " to find " << target << ":\n";

        dfsUtil(start, visited, target, found);

        if (found)
            cout << "\nTarget node " << target << " found!\n";
        else
            cout << "\nTarget node " << target << " not found in DFS traversal.\n";
    }

private:
    void dfsUtil(int node, vector<bool>& visited, int target, bool& found) {
        if (found) return; // Stop early if already found

        #pragma omp critical
        {
            if (visited[node] || found) return;
            visited[node] = true;
            cout << node << " ";

            if (node == target) {
                found = true;
                return;
            }
        }

        #pragma omp parallel for shared(found)
        for (int i = 0; i < adj[node].size(); i++) {
            if (found) continue;

            int neighbor = adj[node][i];

            #pragma omp critical
            {
                if (!visited[neighbor] && !found) {
                    dfsUtil(neighbor, visited, target, found);
                }
            }
        }
    }
};
int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start, target;
    cout << "Enter starting node for DFS: ";
    cin >> start;

    cout << "Enter target node to search: ";
    cin >> target;

    g.parallelDFS(start, target);

    return 0;
}