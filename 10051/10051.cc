/*

10051 Tower of Cubes

In this problem you are given N colorful cubes each having a distinct weight. Each face of a cube is colored with one color. Your job is to build a tower using the cubes you have subject to the following restrictions:

    • Never put a heavier cube on a lighter one.
    • The bottom face of every cube (except the bottom cube, which is lying on the floor) must have the same color as the top face of the cube below it.
    • Construct the tallest tower possible.

Input

The input may contain multiple test cases. The first line of each test case contains an integer N (1 ≤ N ≤ 500) indicating the number of cubes you are given. The i th (1 ≤ i ≤ N) of the next N lines contains the description of the i th cube. A cube is described by giving the colors of its faces in the following order: front, back, left, right, top and bottom face. For your convenience colors are identified by integers in the range 1 to 100. You may assume that cubes are given in the increasing order of their weights, that is, cube 1 is the lightest and cube N is the heaviest.
The input terminates with a value 0 for N.

Output

For each test case in the input first print the test case number on a separate line as shown in the sample output. On the next line print the number of cubes in the tallest tower you have built. From the next line describe the cubes in your tower from top to bottom with one description per line. Each description contains an integer (giving the serial number of this cube in the input) followed by a single white space character and then the identification string (front, back, left, right, top or bottom) of the top face of the cube in the tower. Note that there may be multiple solutions and any one of them is acceptable.

Print a blank line between two successive test cases.

Sample Input

3
1 2 2 2 1 2
3 3 3 3 3 3
3 2 1 1 1 1
10
1 5 10 3 6 5
2 6 7 3 6 9
5 7 3 2 1 9
1 3 3 5 8 10
6 6 2 2 4 4
1 2 3 4 5 6
10 9 8 7 6 5
6 1 2 3 4 7
1 2 3 3 2 1
3 2 1 1 2 3
0

Sample Output

Case #1
2
2 front
3 front

Case #2
8
1 bottom
2 back
3 right
4 left
6 top
8 front
9 front
10 top

*/

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <utility>

using namespace std;

class Graph
{
    public:
        void AddVertex(int v);
        void AddEdge(int u, int v);
        const vector<int>& GetEdges(int v) const;
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

const vector<int>& Graph::GetEdges(int v) const
{
    return adjacencyList.at(v);
}

vector<int> Graph::GetVertices() const
{
    vector<int> vertices;

    for (const auto &vertexToNeighbors : adjacencyList)
    {
        vertices.push_back(vertexToNeighbors.first);
    }

    return vertices;
}

struct Cube
{
    int weight;
    int front;
    int back;
    int left;
    int right;
    int top;
    int bottom;
};

struct CubeData
{
    int weight;
    string topOfCube;
};

vector<pair<int,string>> GetLargestStackOfCubes(vector<int> &verticesOfLongestPath, const unordered_map<int,CubeData> &vertexToCubeData)
{
    vector<pair<int,string>> largestStackOfCubes;

    reverse(verticesOfLongestPath.begin(), verticesOfLongestPath.end());

    for (int vertex : verticesOfLongestPath)
    {
        CubeData vertexCubeData = vertexToCubeData.at(vertex);

        largestStackOfCubes.push_back(make_pair(vertexCubeData.weight, vertexCubeData.topOfCube));
    }

    return largestStackOfCubes;
}

vector<int> TopologicalSort(const Graph &graph)
{
    vector<int> vertices = graph.GetVertices();

    sort(vertices.begin(), vertices.end());

    return vertices;
}

int GetIndexOfMaxWeight(const vector<pair<int,int>> &maxWeightAndParent)
{
    int indexOfMaxWeight = 0;
    int maxWeight = 0;

    for (unsigned int i=0; i<maxWeightAndParent.size(); ++i)
    {
        if (maxWeightAndParent[i].first > maxWeight)
        {
            maxWeight = maxWeightAndParent[i].first;
            indexOfMaxWeight = i;
        }
    }

    return indexOfMaxWeight;
}

vector<int> GetVerticesOfLongestPath(const vector<pair<int,int>> &maxWeightAndParent)
{
    int indexOfMax = GetIndexOfMaxWeight(maxWeightAndParent);

    vector<int> verticesOfLongestPath;

    int i;

    for (i=indexOfMax; i != maxWeightAndParent[i].second; i = maxWeightAndParent[i].second)
    {
        verticesOfLongestPath.push_back(i);
    }

    verticesOfLongestPath.push_back(i);

    return verticesOfLongestPath;
}

vector<pair<int,int>> GetMaxWeightAndParents(const vector<int> &topologicalSorting, const Graph &graph)
{
    vector<pair<int,int>> maxWeightAndParents;

    for (int vertex : topologicalSorting)
    {
        maxWeightAndParents.push_back(make_pair(1,vertex));
    }

    for (unsigned int i=0; i<maxWeightAndParents.size(); ++i)
    {
        int currentWeight = maxWeightAndParents[i].first;

        vector<int> neighbors = graph.GetEdges(i);

        for (int neighbor : neighbors)
        {
            if (maxWeightAndParents[neighbor].first < currentWeight + 1)
            {
                maxWeightAndParents[neighbor] = make_pair(currentWeight + 1, i);
            }
        }
    }

    return maxWeightAndParents;
}

vector<pair<int,string>> GetLargestStackOfCubes(const Graph &graph, const unordered_map<int,CubeData> &vertexToCubeData)
{
    vector<int> topologicalSorting = TopologicalSort(graph);

    vector<pair<int,int>> maxWeightAndParent = GetMaxWeightAndParents(topologicalSorting, graph);

    vector<int> verticesOfLongestPath = GetVerticesOfLongestPath(maxWeightAndParent);

    return GetLargestStackOfCubes(verticesOfLongestPath, vertexToCubeData);
}

Graph MakeGraph(const vector<Cube> &cubes, unordered_map<int,CubeData> &vertexToCubeData)
{
    Graph graph;

    vertexToCubeData[0] = CubeData();

    graph.AddVertex(0);
    return graph;
}

vector<pair<int,string>> GetLargestStackOfCubes(const vector<Cube> &cubes)
{
    unordered_map<int,CubeData> vertexToCubeData;

    Graph graph = MakeGraph(cubes, vertexToCubeData);

    return GetLargestStackOfCubes(graph, vertexToCubeData);
}

int main()
{
    return 0;
    int N;
    int caseNumber = 1;

    cin >> N;

    while (true)
    {
        vector<Cube> cubes(N);

        for (int i=0; i<N; ++i)
        {
            cubes[i].weight = i+1;

            cin >> cubes[i].front >> cubes[i].back >> cubes[i].left >> cubes[i].right >> cubes[i].top >> cubes[i].bottom;
        }

        vector<pair<int,string>> stackOfCubes = GetLargestStackOfCubes(cubes);

        cout << "Case #" << caseNumber << endl;
        cout << stackOfCubes.size() << endl;

        for (const auto weightAndSide : stackOfCubes)
        {
            cout << weightAndSide.first << ' ' << weightAndSide.second << endl;
        }

        cin >> N;

        if (N == 0)
        {
            break;
        }
        else
        {
            cout << endl;
        }

        ++caseNumber;
    }

    return 0;
}

