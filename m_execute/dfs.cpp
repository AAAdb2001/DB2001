#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

// Function for parallel Depth First Search
void parallelDFS(const std::vector<std::vector<int>>& graph, int currentVertex, std::vector<bool>& visited) {
    visited[currentVertex] = true;
    std::cout << currentVertex << " ";

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < graph[currentVertex].size(); i++) {
            int neighbor = graph[currentVertex][i];
            if (!visited[neighbor]) {
                #pragma omp task
                parallelDFS(graph, neighbor, visited);
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
    std::cout << "Enter the starting vertex for DFS: ";
    std::cin >> startVertex;

    std::vector<bool> visited(numVertices, false);

    std::cout << std::endl;

    std::cout << "Parallel Depth First Search (DFS): ";
    parallelDFS(graph, startVertex, visited);
    std::cout << std::endl;

    return 0;
}

//input
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
// Enter the starting vertex for DFS: 0
// Parallel Depth First Search (DFS): 0 1 3 4 2

// Enter the number of vertices in the graph: 4
// Enter the neighbors for each vertex (separated by spaces):
// Enter the number of neighbors for vertex 0: 2 
// Enter the neighbors for vertex 0: 1 2
// Enter the number of neighbors for vertex 1: 1
// Enter the neighbors for vertex 1: 0
// Enter the number of neighbors for vertex 2: 2
// Enter the neighbors for vertex 2: 0 3
// Enter the number of neighbors for vertex 3: 1
// Enter the neighbors for vertex 3: 2
// Enter the starting vertex for DFS: 0

// Parallel Depth First Search (DFS): 0 2 3 1