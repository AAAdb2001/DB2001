#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

void parallelBFS(const std::vector<std::vector<int>>& graph, int startVertex) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> bfsQueue;

    visited[startVertex] = true;
    bfsQueue.push(startVertex);

    while (!bfsQueue.empty()) {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();

        std::cout << currentVertex << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph[currentVertex].size(); i++) {
            int neighbor = graph[currentVertex][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        bfsQueue.push(neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    int numVertices;
    std::cout << "Enter the number of vertices in the graph: ";
    std::cin >> numVertices;

    std::vector<std::vector<int>> graph(numVertices);

    std::cout << "Enter the neighbors for each vertex (separated by spaces):" << std::endl;
    for (int i = 0; i < numVertices; i++) {
        int numNeighbors;
        std::cout << "Enter the number of neighbors for vertex " << i << ": ";
        std::cin >> numNeighbors;

        graph[i].resize(numNeighbors);

        std::cout << "Enter the neighbors for vertex " << i << ": ";
        for (int j = 0; j < numNeighbors; j++) {
            std::cin >> graph[i][j];
        }
    }

    int startVertex;
    std::cout << "Enter the starting vertex for BFS: ";
    std::cin >> startVertex;

    std::vector<bool> visited(numVertices, false);

    std::cout << "Parallel Breadth First Search (BFS): ";
    parallelBFS(graph, startVertex);
    std::cout << std::endl;
    return 0;
}

// Enter the number of vertices in the graph: 4
// Enter the neighbors for each vertex (separated by spaces):
// Enter the number of neighbors for vertex 0: 2
// Enter the neighbors for vertex 0: 1 2
// Enter the number of neighbors for vertex 1: 2
// Enter the neighbors for vertex 1: 0 3
// Enter the number of neighbors for vertex 2: 2
// Enter the neighbors for vertex 2: 0 3
// Enter the number of neighbors for vertex 3: 2
// Enter the neighbors for vertex 3: 1 2
// Enter the starting vertex for BFS and DFS: 0
// Parallel Breadth First Search (BFS): 0 2 1 3

// Enter the number of vertices in the graph: 5
// Enter the neighbors for each vertex (separated by spaces):
// Enter the number of neighbors for vertex 0: 2
// Enter the neighbors for vertex 0: 1 2
// Enter the number of neighbors for vertex 1: 3
// Enter the neighbors for vertex 1: 0 3 4
// Enter the number of neighbors for vertex 2: 1
// Enter the neighbors for vertex 2: 0
// Enter the number of neighbors for vertex 3: 1
// Enter the neighbors for vertex 3: 1
// Enter the number of neighbors for vertex 4: 1
// Enter the neighbors for vertex 4: 1
// Enter the starting vertex for BFS: 0
// Parallel Breadth First Search (BFS): 0 1 2 4 3