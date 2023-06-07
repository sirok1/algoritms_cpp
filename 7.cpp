#include <iostream>
#include <vector>
#include <limits>

const int INF = std::numeric_limits<int>::max();

int findMinDistance(const std::vector<int>& distances, const std::vector<bool>& visited, int numVertices) {
    int minDistance = INF;
    int minIndex = -1;

    for (int v = 0; v < numVertices; ++v) {
        if (!visited[v] && distances[v] <= minDistance) {
            minDistance = distances[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void printShortestPath(const std::vector<int>& shortestPath, int destination) {
    if (shortestPath[destination] == -1) {
        std::cout << "No path to destination" << std::endl;
        return;
    }

    std::vector<int> path;
    int vertex = destination;
    while (vertex != -1) {
        path.push_back(vertex);
        vertex = shortestPath[vertex];
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}

void dijkstraShortestPath(const std::vector<std::vector<int>>& graph, int startVertex, int numVertices) {
    std::vector<int> distances(numVertices, INF);
    std::vector<bool> visited(numVertices, false);
    std::vector<int> shortestPath(numVertices, -1);

    distances[startVertex] = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        int currentVertex = findMinDistance(distances, visited, numVertices);
        visited[currentVertex] = true;

        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && graph[currentVertex][v] && distances[currentVertex] != INF &&
                distances[currentVertex] + graph[currentVertex][v] < distances[v]) {
                distances[v] = distances[currentVertex] + graph[currentVertex][v];
                shortestPath[v] = currentVertex;
            }
        }
    }

    for (int v = 0; v < numVertices; ++v) {
        if (v != startVertex) {
            std::cout << "Shortest path from " << startVertex << " to " << v << ": ";
            printShortestPath(shortestPath, v);
        }
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
            {0, 2, 4, 0, 0, 0},
            {2, 0, 1, 4, 2, 0},
            {4, 1, 0, 0, 3, 0},
            {0, 4, 0, 0, 3, 1},
            {0, 2, 3, 3, 0, 2},
            {0, 0, 0, 1, 2, 0}
    };

    int numVertices = graph.size();
    int startVertex = 0;

    dijkstraShortestPath(graph, startVertex, numVertices);

    return 0;
}