// 🧾 Sample Input:
// Enter number of vertices (max 10): 5
// Enter number of edges: 6

// EDGES (vertex1 vertex2 format):
// Edge 0: 0 1
// Edge 1: 0 2
// Edge 2: 1 3
// Edge 3: 2 3
// Edge 4: 3 4
// Edge 5: 1 4

// Enter starting vertex (0 to 4) for BFS: 0
// Enter starting vertex (0 to 4) for DFS: 0
//___________________________________________
#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 10;

// Graph representations
int adjMatrix[MAX][MAX];            // For DFS
int adjList[MAX][MAX];             // For BFS
int listSize[MAX];                 // To track size of each row in adjList

// Sample landmark names
char landmarks[MAX][20] = {
    "Library", "Canteen", "Lab", "Hostel", "Main Gate"
};

int n, m;

// DFS using adjacency matrix
void DFS(int start) {
    int visited[MAX] = {0};
    stack<int> s;

    s.push(start);
    visited[start] = 1;

    cout << "DFS traversal: ";
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        cout << landmarks[v] << " ";

        // Traverse neighbors
        for (int i = n - 1; i >= 0; i--) {
            if (adjMatrix[v][i] && !visited[i]) {
                s.push(i);
                visited[i] = 1;
            }
        }
    }
    cout << endl;
}

// BFS using adjacency list
void BFS(int start) {
    int visited[MAX] = {0};
    queue<int> q;

    q.push(start);
    visited[start] = 1;

    cout << "BFS traversal: ";
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << landmarks[v] << " ";

        for (int i = 0; i < listSize[v]; i++) {
            int neighbor = adjList[v][i];
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = 1;
            }
        }
    }
    cout << endl;
}

int main() {
    cout << "Enter number of vertices (max 10): ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    // Initialize
    memset(adjMatrix, 0, sizeof(adjMatrix));
    memset(adjList, 0, sizeof(adjList));
    memset(listSize, 0, sizeof(listSize));

    cout << "\nEDGES (vertex1 vertex2 format):\n";
    for (int k = 0; k < m; k++) {
        int u, v;
        cout << "Edge " << k << ": ";
        cin >> u >> v;

        // Adjacency matrix (for DFS)
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // Adjacency list (for BFS)
        adjList[u][listSize[u]++] = v;
        adjList[v][listSize[v]++] = u;
    }

    int start;
    cout << "\nEnter starting vertex (0 to " << n - 1 << ") for BFS: ";
    cin >> start;
    BFS(start);

    cout << "\nEnter starting vertex (0 to " << n - 1 << ") for DFS: ";
    cin >> start;
    DFS(start);

    return 0;
}
