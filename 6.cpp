//Задание 1
#include <iostream>
#include <vector>
#include <limits>

const int numCampuses = 5; // Количество кампусов

// Функция для нахождения индекса вершины с наименьшим весом, которая еще не включена в остовное дерево
int findMinWeightVertex(const std::vector<double>& weights, const std::vector<bool>& included) {
    double minWeight = std::numeric_limits<double>::max();
    int minIndex = -1;

    for (int i = 0; i < numCampuses; i++) {
        if (!included[i] && weights[i] < minWeight) {
            minWeight = weights[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Функция для вывода маршрута с минимальной общей длиной
void printMinRoute(const std::vector<int>& parent, const std::vector<std::vector<double>>& distances) {
    std::cout << "The route with the minimum total length: " << std::endl;
    for (int i = 1; i < numCampuses; i++) {
        std::cout << "Campus " << i+1 << " -> Campus " << parent[i]+1 << ": " << distances[i][parent[i]] << std::endl;
    }
}

void findMinRouteUsingPrim(const std::vector<std::vector<double>>& distances) {
    std::vector<int> parent(numCampuses); // Массив для хранения родительских вершин
    std::vector<double> weights(numCampuses, std::numeric_limits<double>::max()); // Массив для хранения весов вершин
    std::vector<bool> included(numCampuses, false); // Массив для отслеживания включенных вершин

    // Вес первой вершины равен 0
    weights[0] = 0;
    parent[0] = -1; // У первой вершины нет родителя

    // Поиск минимального остовного дерева
    for (int i = 0; i < numCampuses - 1; i++) {
        int minIndex = findMinWeightVertex(weights, included);
        included[minIndex] = true;

        for (int j = 0; j < numCampuses; j++) {
            if (distances[minIndex][j] != 0 && !included[j] && distances[minIndex][j] < weights[j]) {
                parent[j] = minIndex;
                weights[j] = distances[minIndex][j];
            }
        }
    }

    printMinRoute(parent, distances);
}

int main() {
    // Инициализация расстояний между кампусами
    std::vector<std::vector<double>> distances = {
            {0, 1.97, 21.6, 10.7, 22.3},
            {1.97, 0, 22.3, 11.4, 23},
            {21.6, 22.3, 0, 11.5, 5.2},
            {10.7, 11.4, 11.5, 0, 13.4},
            {22.3, 23, 5.2, 13.4, 0.68}
    };

    findMinRouteUsingPrim(distances);

    return 0;
}
//Задание 2
//a)
#include <iostream>
#include <vector>

int findConnectivity(const std::vector<std::vector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    std::vector<bool> visited(numVertices, false);
    int connectivity = 0;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            connectivity++;
            visited[i] = true;

            std::vector<int> stack;
            stack.push_back(i);

            while (!stack.empty()) {
                int vertex = stack.back();
                stack.pop_back();

                for (int j = 0; j < numVertices; j++) {
                    if (adjacencyMatrix[vertex][j] && !visited[j]) {
                        visited[j] = true;
                        stack.push_back(j);
                    }
                }
            }
        }
    }

    return connectivity;
}

int main() {
    std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 1, 0, 0, 0, 0},
            {1, 0, 0, 1, 1, 0, 0},
            {1, 0, 0, 1, 0, 1, 0},
            {0, 1, 1, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 0, 1},
            {0, 0, 1, 1, 0, 0, 1},
            {0, 0, 0, 0, 1, 1, 0}
    };

    int connectivity = findConnectivity(adjacencyMatrix);

    std::cout << "Number of connectivity of a graph: " << connectivity << std::endl;

    return 0;
}
//б)
#include <iostream>
#include <vector>

int findConnectivity(const std::vector<std::vector<int>>& incidenceMatrix) {
    int numVertices = incidenceMatrix.size();
    int numEdges = incidenceMatrix[0].size();
    std::vector<bool> visited(numVertices, false);
    int connectivity = 0;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            connectivity++;
            visited[i] = true;

            std::vector<int> stack;
            stack.push_back(i);

            while (!stack.empty()) {
                int vertex = stack.back();
                stack.pop_back();

                for (int j = 0; j < numEdges; j++) {
                    if (incidenceMatrix[vertex][j] && !visited[j]) {
                        visited[j] = true;
                        stack.push_back(j);
                    }
                }
            }
        }
    }

    return connectivity;
}

int main() {
    std::vector<std::vector<int>> incidenceMatrix = {
            {1, 1, 0, 0, 0, 0, 0},
            {1, 0, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 1, 1},
            {0, 0, 1, 0, 1, 0, 1},
            {0, 0, 0, 0, 1, 1, 1}
    };

    int connectivity = findConnectivity(incidenceMatrix);

    std::cout << "The number of connectivity of a graph: " << connectivity << std::endl;

    return 0;
}
//Задание 3

#include <iostream>
#include <vector>
#include <climits>

int findMinWeightVertex(const std::vector<int>& weights, const std::vector<bool>& visited) {
    int minWeight = INT_MAX;
    int minWeightVertex = -1;
    int numVertices = weights.size();

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && weights[i] < minWeight) {
            minWeight = weights[i];
            minWeightVertex = i;
        }
    }

    return minWeightVertex;
}

std::vector<int> findSuboptimalTSP(const std::vector<std::vector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    std::vector<bool> visited(numVertices, false);
    std::vector<int> tspPath;
    tspPath.push_back(0); // Начинаем с вершины 0
    visited[0] = true;

    for (int i = 0; i < numVertices - 1; i++) {
        int currentVertex = tspPath.back();
        int minWeight = INT_MAX;
        int nextVertex = -1;

        for (int j = 0; j < numVertices; j++) {
            if (!visited[j] && adjacencyMatrix[currentVertex][j] < minWeight) {
                minWeight = adjacencyMatrix[currentVertex][j];
                nextVertex = j;
            }
        }

        tspPath.push_back(nextVertex);
        visited[nextVertex] = true;
    }

    return tspPath;
}

int main() {
    std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 2, 9, 10, 5, 4, 7},
            {2, 0, 6, 4, 8, 7, 3},
            {9, 6, 0, 3, 7, 6, 5},
            {10, 4, 3, 0, 6, 5, 7},
            {5, 8, 7, 6, 0, 2, 9},
            {4, 7, 6, 5, 2, 0, 8},
            {7, 3, 5, 7, 9, 8, 0}
    };

    std::vector<int> tspPath = findSuboptimalTSP(adjacencyMatrix);

    std::cout << "The Suboptimal Commie Way: ";
    for (int vertex : tspPath) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    return 0;
}