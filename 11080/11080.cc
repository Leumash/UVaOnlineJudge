#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
    public:
        void addVertex(int v);
        void addEdge(int u, int v);
        const unordered_set<int>& getEdges(int v) const;
        vector<int> getVertices() const;
    private:
        unordered_map<int, unordered_set<int>> adjacencyList;
};

void Graph::addVertex(int v) {
    if (adjacencyList.count(v) == 0) {
        adjacencyList[v];
    }
}

void Graph::addEdge(int u, int v) {
    addVertex(u);
    addVertex(v);

    adjacencyList[u].insert(v);
}

const unordered_set<int>& Graph::getEdges(int v) const {
    return adjacencyList.at(v);
}

vector<int> Graph::getVertices() const {
    vector<int> verticies;
    for (const auto vertexToNeighbors : adjacencyList) {
        verticies.push_back(vertexToNeighbors.first);
    }
    return verticies;
}

Graph readGraph() {
    Graph graph;
    int u, v;
    int numVertices, numEdges;

    cin >> numVertices >> numEdges;
    for (int i=0; i<numVertices; ++i) {
        graph.addVertex(i);
    }
    for (int i=0; i<numEdges; ++i) {
        cin >> u >> v;
        graph.addEdge(u, v);
        graph.addEdge(v, u);
    }
    return graph;
}

bool partition(const Graph &graph, int s, unordered_set<int> &visited, unordered_set<int> &left, unordered_set<int> &right) {
    if (visited.count(s) > 0) {
        return true;
    }
    visited.insert(s);
    left.insert(s);

    for (int neighbor : graph.getEdges(s)) {
        // Self loop
        if (s == neighbor) {
            continue;
        }
        // Non-bipartite graph
        if (left.count(neighbor) > 0) {
            return false;
        }
        if (!partition(graph, neighbor, visited, right, left)) {
            return false;
        }
    }
    return true;
}

int getMinimumNumberOfGuards(const Graph &graph) {
    int minNumOfGuards = 0;
    vector<int> vertices = graph.getVertices();
    unordered_set<int> visited;
    for (int vertex : graph.getVertices()) {
        if (visited.count(vertex) == 0) {
            unordered_set<int> left, right;
            if (!partition(graph, vertex, visited, left, right)) {
                return -1;
            } else {
                int minPartition = min(left.size(), right.size());
                // Need at least 1 guard
                minNumOfGuards += max(minPartition, 1);
            }
        }
    }
    return minNumOfGuards;
}

int main() {
    int T;
    cin >> T;
    for (int i=0; i<T; ++i) {
        Graph graph = readGraph();
        cout << getMinimumNumberOfGuards(graph) << endl;
    }
}

