/*

821 Page Hopping

It was recently reported that, on the average, only 19 clicks are necessary to move from any page on the World Wide Web to any other page. That is, if the pages on the web are viewed as nodes in a graph, then the average path length between arbitrary pairs of nodes in the graph is 19.

Given a graph in which all nodes can be reached from any starting point, your job is to find the average shortest path length between arbitrary pairs of nodes.  For example, consider the following graph. Note that links are shown as directed edges, since a link from page a to page b does not imply a link from page b to page a.

The length of the shortest path from node 1 to nodes 2, 3, and 4 is 1,1, and 2 respectively. From node 2 to nodes 1, 3 and 4, the shortest paths have lengths of 3, 2, and 1. From node 3 to nodes 1, 2, and 4, the shortest paths have lengths of 1, 2, and 3. Finally, from node 4 to nodes 1, 2, and 3 the shortest paths have lengths of 2, 3, and 1. The sum of these path lengths is 1 + 1 + 2 + 3 + 2 + 1 + 1 + 2 + 3 + 2 + 3 + 1 = 22. Since there are 12 possible pairs of nodes to consider, we obtain an average path length of 22/12, or 1.833 (accurate to three fractional digits).

Input

The input data will contain multiple test cases. Each test case will consist of an arbitrary number of pairs of integers, a and b, each representing a link from a page numbered a to a page numbered b. Page numbers will always be in the range 1 to 100. The input for each test case will be terminated with a pair of zeroes, which are not to be treated as page numbers. An additional pair of zeroes will follow the last test case, effectively representing a test case with no links, which is not to be processed. The graph will not include self-referential links (that is, there will be no direct link from a node to itself), and at least one path will exist from each node in the graph to every other node in the graph.

Output

For each test case, determine the average shortest path length between every pair of nodes, accurate to three fractional digits. Display this length and the test case identifier (theyffre numbered sequentially starting with 1) in a form similar to that shown in the sample output below.

Sample Input

1 2 2 4 1 3 3 1 4 3 0 0
1 2 1 4 4 2 2 7 7 1 0 0
0 0

Sample Output

Case 1: average length between pages = 1.833 clicks
Case 2: average length between pages = 1.750 clicks

*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Graph
{
    public:
        void AddVertex(int v);
        void AddEdge(int u, int v);
        const vector<int>& GetEdge(int v) const;
        vector<int> GetVertices() const;
    private:
        unordered_map<int,vector<int>> adjacencyList;
};

void Graph::AddVertex(int v)
{
    if (adjacencyList.count(v) == 0)
    {
        adjacencyList[v] = vector<int>();
    }
}

void Graph::AddEdge(int u, int v)
{
    AddVertex(u);
    AddVertex(v);

    adjacencyList[u].push_back(v);
}

const vector<int>& Graph::GetEdge(int v) const
{
    return adjacencyList.at(v);
}

vector<int> Graph::GetVertices() const
{
    vector<int> vertices;

    for (const auto vertexToNeighbors : adjacencyList)
    {
        vertices.push_back(vertexToNeighbors.first);
    }

    return vertices;
}

Graph MakeGraph(const vector<pair<int,int>> &edges)
{
    Graph graph;

    for (const auto &edge : edges)
    {
        graph.AddEdge(edge.first, edge.second);
    }

    return graph;
}

int GetTotal(const unordered_map<int,int> &m)
{
    int total = 0;

    for (const auto &a : m)
    {
        total += a.second;
    }

    return total;
}

int GetSumOfLengths(const Graph &graph, int s)
{
    unordered_map<int,int> vertexToDistanceFromStart;

    vertexToDistanceFromStart[s] = 0;

    unordered_set<int> visited;
    queue<int> toVisit;
    visited.insert(s);
    toVisit.push(s);

    while (!toVisit.empty())
    {
        int currentVertex = toVisit.front();
        toVisit.pop();

        for (int neighbor : graph.GetEdge(currentVertex))
        {
            if (visited.count(neighbor) == 0)
            {
                visited.insert(neighbor);
                toVisit.push(neighbor);
                vertexToDistanceFromStart[neighbor] = vertexToDistanceFromStart[currentVertex] + 1;
            }
        }
    }

    return GetTotal(vertexToDistanceFromStart);
}

double GetAverageLengthBetweenVertices(const Graph &graph)
{
    double total = 0;

    vector<int> vertices = graph.GetVertices();

    for (int vertex : vertices)
    {
        total += GetSumOfLengths(graph, vertex);
    }

    return total / (vertices.size() * (vertices.size() - 1));
}

double GetAverageLengthBetweenPages(const vector<pair<int,int>> &edges)
{
    Graph graph = MakeGraph(edges);

    return GetAverageLengthBetweenVertices(graph);
}

int main()
{
    int i = 1;
    pair<int,int> input;

    while (true)
    {
        cin >> input.first >> input.second;

        if (input.first == 0 && input.second == 0)
        {
            break;
        }

        vector<pair<int,int>> edges;

        edges.push_back(input);

        while (true)
        {
            cin >> input.first >> input.second;

            if (input.first == 0 && input.second == 0)
            {
                break;
            }

            edges.push_back(input);
        }

        cout << "Case " << i << ": average length between pages = ";
        cout << fixed << setprecision(3) << GetAverageLengthBetweenPages(edges);
        cout << " clicks" << endl;

        ++i;
    }

    return 0;
}

