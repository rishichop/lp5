#include <iostream>
#include <vector>
#include <queue>
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

    void parallelBFS(int start, int target) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Parallel BFS starting from node " << start << ":\n";

        bool found = false;

        while (!q.empty() && !found) {
            int levelSize = q.size();
            vector<int> currentLevel;

            // Process current level
            for (int i = 0; i < levelSize; i++) {
                int node = q.front(); q.pop();
                cout << node << " ";

                if (node == target) {
                    found = true;
                    break;
                }

                currentLevel.push_back(node);
            }

            // Parallel exploration of neighbors
            #pragma omp parallel for shared(found)
            for (int i = 0; i < currentLevel.size(); i++) {
                if (found) continue; // Skip work if already found

                int node = currentLevel[i];
                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                q.push(neighbor);
                            }
                        }
                    }
                }
            }
        }

        if (found)
            cout << "\nTarget node " << target << " found!\n";
        else
            cout << "\nTarget node " << target << " not found in BFS traversal.\n";
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
    cout << "Enter starting node for BFS: ";
    cin >> start;

    cout << "Enter target node to search: ";
    cin >> target;

    g.parallelBFS(start, target);

    return 0;
}