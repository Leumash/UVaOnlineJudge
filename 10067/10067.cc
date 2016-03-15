/*

10067 Playing with Wheels

In this problem we will be considering a game played with four wheels. Digits ranging from 0 to 9 are printed consecutively (clockwise) on the periphery of each wheel. The topmost digits of the wheels form a four-digit integer. For example, in the following figure the wheels form the integer 8056. Each wheel has two buttons associated with it. Pressing the button marked with a left arrow rotates the wheel one digit in the clockwise direction and pressing the one marked with the right arrow rotates it by one digit in the opposite direction.

The game starts with an initial configuration of the wheels. Say, in the initial configuration the topmost digits form the integer S1S2S3S4. You will be given some (say, n) forbidden configurations Fi1Fi2Fi3Fi4 (1 ≤ i ≤ n) and a target configuration T1T2T3T4. Your job will be to write a program that can calculate the minimum number of button presses required to transform the initial configuration to the target configuration by never passing through a forbidden one.

Input

The first line of the input contains an integer N giving the number of test cases to follow.

The first line of each test case contains the initial configuration of the wheels specified by 4 digits.  Two consecutive digits are separated by a space. The next line contains the target configuration. The third line contains an integer n giving the number of forbidden configurations. Each of the following n lines contains a forbidden configuration. There is a blank line between two consecutive input sets.  

Output

For each test case in the input print a line containing the minimum number of button presses required. If the target configuration is not reachable then print ‘-1’.

Sample Input

2
8 0 5 6
6 5 0 8
5
8 0 5 7
8 0 4 7
5 5 0 8
7 5 0 8
6 4 0 8
0 0 0 0
5 3 1 7
8
0 0 0 1
0 0 0 9
0 0 1 0
0 0 9 0
0 1 0 0
0 9 0 0
1 0 0 0
9 0 0 0

Sample Output

14
-1

*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Graph
{
    public:
        void AddVertex(int);
        void AddEdge(int,int);
        unordered_set<int> GetEdges(int) const;
    private:
        unordered_map<int,unordered_set<int>> adjacencyList;
};

void Graph::AddVertex(int vertex)
{
    if (adjacencyList.count(vertex) == 0)
    {
        adjacencyList[vertex] = unordered_set<int>();
    }
}

void Graph::AddEdge(int u,int v)
{
    AddVertex(u);
    AddVertex(v);

    adjacencyList[u].insert(v);
}

unordered_set<int> Graph::GetEdges(int vertex) const
{
    if (adjacencyList.count(vertex))
    {
        return adjacencyList.at(vertex);
    }

    return unordered_set<int>();
}

int GetDigitsFromInput()
{
    int toReturn = 0;

    for (int j=0; j<4; ++j)
    {
        int temp;
        cin >> temp;
        toReturn = toReturn * 10 + temp;
    }

    return toReturn;
}

int GetLengthOfPath(int s, int t, const unordered_map<int,int> &parents)
{
    int length = 0;

    for (int v=t; v != s; v = parents.at(v))
    {
        ++length;
    }

    return length;
}

bool BFS(const Graph &graph, int s, int t, unordered_map<int,int> &parents, const unordered_set<int> &forbiddenVertices)
{
    parents.clear();

    queue<int> toVisit;
    toVisit.push(s);

    unordered_set<int> visited;
    visited.insert(s);

    while (!toVisit.empty())
    {
        int currentVertex = toVisit.front();
        toVisit.pop();

        for (int neighbor : graph.GetEdges(currentVertex))
        {
            if (visited.count(neighbor) == 0 && forbiddenVertices.count(neighbor) == 0)
            {
                visited.insert(neighbor);
                toVisit.push(neighbor);
                parents[neighbor] = currentVertex;
            }
        }
    }

    return visited.count(t) > 0;
}

string MakeConfiguration(int configuration)
{
    string toReturn = to_string(configuration);

    while (toReturn.size() < 4)
    {
        toReturn = "0" + toReturn;
    }

    return toReturn;
}

char RotateClockwise(char digit)
{
    return digit == '0' ? '9' : digit - 1;
}

int RotateClockwise(int configuration, int pos)
{
    string config = MakeConfiguration(configuration);

    config[pos] = RotateClockwise(config[pos]);

    return stoi(config);
}

char RotateCounterClockwise(char digit)
{
    return digit == '9' ? '0' : digit + 1;
}

int RotateCounterClockwise(int configuration, int pos)
{
    string config = MakeConfiguration(configuration);

    config[pos] = RotateCounterClockwise(config[pos]);

    return stoi(config);
}

Graph MakeWheelGame()
{
    Graph graph;

    for (int vertex=0; vertex <= 9999; ++vertex)
    {
        graph.AddVertex(vertex);

        // Add 8 edges
        for (int pos=0; pos<4; ++pos)
        {
            graph.AddEdge(vertex, RotateClockwise(vertex, pos));
            graph.AddEdge(vertex, RotateCounterClockwise(vertex, pos));
        }
    }

    return graph;
}

int GetMinimumNumberOfButtonPressesRequired(int initialConfiguration, int targetConfiguration, const unordered_set<int> &forbiddenConfigurations)
{
    static Graph graph = MakeWheelGame();

    unordered_map<int,int> parents;

    if (BFS(graph, initialConfiguration, targetConfiguration, parents, forbiddenConfigurations))
    {
        return GetLengthOfPath(initialConfiguration, targetConfiguration, parents);
    }
    else
    {
        return -1;
    }
}

int main()
{
    int T;

    cin >> T;

    for (int i=0; i<T; ++i)
    {
        int initialConfiguration = GetDigitsFromInput();
        int targetConfiguration = GetDigitsFromInput();

        int numberOfForbiddenConfigurations;

        cin >> numberOfForbiddenConfigurations;

        unordered_set<int> forbiddenConfigurations;

        for (int j=0; j<numberOfForbiddenConfigurations; ++j)
        {
            int forbiddenConfiguration = GetDigitsFromInput();
            forbiddenConfigurations.insert(forbiddenConfiguration);
        }

        cout << GetMinimumNumberOfButtonPressesRequired(initialConfiguration, targetConfiguration, forbiddenConfigurations) << endl;
    }

    return 0;
}

