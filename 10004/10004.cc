/*

10004 Bicoloring

In 1976 the “Four Color Map Theorem” was proven with the assistance of a computer. This theorem states that every map can be colored using only four colors, in such a way that no region is colored using the same color as a neighbor region.

Here you are asked to solve a simpler similar problem. You have to decide whether a given arbitrary connected graph can be bicolored. That is, if one can assign colors (from a palette of two) to the nodes in such a way that no two adjacent nodes have the same color. To simplify the problem you can assume:

• no node will have an edge to itself.
• the graph is nondirected. That is, if a node a is said to be connected to a node b, then you must assume that b is connected to a.
• the graph will be strongly connected. That is, there will be at least one path from any node to any other node.

Input

The input consists of several test cases. Each test case starts with a line containing the number n (1 < n < 200) of different nodes. The second line contains the number of edges l. After this, l lines will follow, each containing two numbers that specify an edge between the two nodes that they represent.

A node in the graph will be labeled using a number a (0 ≤ a < n).

An input with n = 0 will mark the end of the input and is not to be processed.

Output

You have to decide whether the input graph can be bicolored or not, and print it as shown below.

Sample Input

3
3
0 1
1 2
2 0
3
2
0 1
1 2
9
8
0 1
0 2
0 3
0 4
0 5
0 6
0 7
0 8
0

Sample Output

NOT BICOLORABLE.
BICOLORABLE.
BICOLORABLE.

*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Graph
{
    public:
        void AddVertex(int);
        void AddEdge(int,int);
        vector<int> GetVertices() const;
        vector<int> GetEdges(int) const;
    private:
        unordered_map<int,vector<int>> adjacencyList;
};

vector<int> Graph::GetVertices() const
{
    vector<int> vertices;

    for (const auto &vertexToNeighbors : adjacencyList)
    {
        vertices.push_back(vertexToNeighbors.first);
    }

    return vertices;
}

vector<int> Graph::GetEdges(int v) const
{
    if (adjacencyList.count(v) > 0)
    {
        return adjacencyList.at(v);
    }

    return vector<int>();
}

void Graph::AddVertex(int u)
{
    if (adjacencyList.count(u) == 0)
    {
        adjacencyList[u] = vector<int>();
    }
}

void Graph::AddEdge(int u,int v)
{
    AddVertex(u);
    AddVertex(v);

    if (adjacencyList.count(u) > 0)
    {
        adjacencyList[u].push_back(v);
    }
}

bool IsSameColor(int u, int v, const unordered_map<int,bool> &vertexColor)
{
    return vertexColor.at(u) == vertexColor.at(v);
}

bool IsBipartite(const Graph &graph)
{
    queue<int> toVisit;
    unordered_map<int,bool> vertexColor;
    vector<int> vertices = graph.GetVertices();

    if (vertices.size() == 0)
    {
        return true;
    }

    int start = vertices[0];

    vertexColor[start] = false;
    toVisit.push(start);

    while (!toVisit.empty())
    {
        int currentVertex = toVisit.front();
        toVisit.pop();

        for (int neighbor : graph.GetEdges(currentVertex))
        {
            if (vertexColor.count(neighbor) > 0)
            {
                if ((currentVertex != neighbor) && IsSameColor(currentVertex, neighbor, vertexColor))
                {
                    return false;
                }
            }
            else
            {
                vertexColor[neighbor] = !vertexColor[currentVertex];
                toVisit.push(neighbor);
            }
        }
    }

    return true;
}

int main()
{
    int n, l, u, v;

    while (cin >> n)
    {
        Graph graph;

        if (n == 0)
        {
            break;
        }

        cin >> l;

        for (int i=0; i<l; ++i)
        {
            cin >> u >> v;

            graph.AddVertex(u);
            graph.AddVertex(v);

            graph.AddEdge(u,v);
            graph.AddEdge(v,u);
        }

        if (IsBipartite(graph))
        {
            cout << "BICOLORABLE." << endl;
        }
        else
        {
            cout << "NOT BICOLORABLE." << endl;
        }
    }

    return 0;
}

