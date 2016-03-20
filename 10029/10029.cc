/*

10029 Edit Step Ladders

An edit step is a transformation from one word x to another word y such that x and y are words in the dictionary, and x can be transformed to y by adding, deleting, or changing one letter. So the transformation from dig to dog or from dog to do are both edit steps. An edit step ladder is a lexicographically ordered sequence of words w1, w2, . . . , wn such that the transformation from wi to wi+1 is an edit step for all i from 1 to n − 1.

For a given dictionary, you are to compute the length of the longest edit step ladder.

Input

The input to your program consists of the dictionary – a set of lower case words in lexicographic order – one per line. No word exceeds 16 letters and there are no more than 25000 words in the dictionary.

Output

The output consists of a single integer, the number of words in the longest edit step ladder.

Sample Input

cat
dig
dog
fig
fin
fine
fog
log
wine

Sample Output

5

*/ 

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Graph
{
    public:
        void AddVertex(string v);
        void AddEdge(string u, string v);
        vector<string> GetVertices() const;
        vector<string> GetEdges(string v) const;
    private:
        unordered_map<string,vector<string>> adjacencyList;
};

void Graph::AddVertex(string v)
{
    if (adjacencyList.count(v) == 0)
    {
        adjacencyList[v] = vector<string>();
    }
}

void Graph::AddEdge(string u, string v)
{
    if (adjacencyList.count(u) > 0)
    {
        adjacencyList[u].push_back(v);
    }
}

vector<string> Graph::GetVertices() const
{
    vector<string> vertices;

    for (const auto &vertexAndEdges : adjacencyList)
    {
        vertices.push_back(vertexAndEdges.first);
    }

    return vertices;
}

vector<string> Graph::GetEdges(string v) const
{
    if (adjacencyList.count(v) > 0)
    {
        return adjacencyList.at(v);
    }

    return vector<string>();
}

vector<string> GetLexicographicalNeighbors(const string &word, const unordered_set<string> &words)
{
    vector<string> lexicographicalNeighbors;

    // Check word where each letter is increased
    for (int i=0; i<word.size(); ++i)
    {
        string temp = word;

        for (char c = temp[i] + 1; c <= 'z'; ++c)
        {
            temp[i] = c;

            if (words.count(temp) > 0)
            {
                lexicographicalNeighbors.push_back(temp);
            }
        }
    }

    // Check word where a letter is inserted ahead of each letter
    for (int i=0; i<word.size(); ++i)
    {
        string temp = word;
        temp.insert(i, "a");

        for (char c = 'a'; c <= 'z'; ++c)
        {
            temp[i] = c;

            if (word < temp && words.count(temp) > 0)
            {
                lexicographicalNeighbors.push_back(temp);
            }
        }
    }

    // Check word where letter is appended to the end
    for (char c = 'a'; c <= 'z'; ++c)
    {
        string temp = word + c;

        if (words.count(temp) > 0)
        {
            lexicographicalNeighbors.push_back(temp);
        }
    }

    // Check word where a letter is removed
    for (int i=0; i<word.size(); ++i)
    {
        string temp = word;
        temp.erase(i, 1);

        if (word < temp && words.count(temp) > 0)
        {
            lexicographicalNeighbors.push_back(temp);
        }
    }

    return lexicographicalNeighbors;
}

Graph MakeLexicograpicalGraph(const unordered_set<string> &words)
{
    Graph graph;

    for (const string &word : words)
    {
        graph.AddVertex(word);
    }

    for (const string &word : words)
    {
        vector<string> neighbors = GetLexicographicalNeighbors(word, words);

        for (const string &neighbor : neighbors)
        {
            graph.AddEdge(word, neighbor);
        }
    }

    return graph;
}

unordered_map<string,int> GetWordToIndex(const vector<string> &words)
{
    unordered_map<string,int> wordToIndex;

    for (int i=0; i<words.size(); ++i)
    {
        wordToIndex[words.at(i)] = i;
    }

    return wordToIndex;
}

int GetLongestSequenceOfWords(const Graph &graph)
{
    vector<string> words = graph.GetVertices();

    sort(words.begin(), words.end());

    unordered_map<string,int> wordToIndex = GetWordToIndex(words);
    vector<int> longestSequence(words.size(), 1);

    for (const string &word : words)
    {
        for (const string &neighbor : graph.GetEdges(word))
        {
            longestSequence[wordToIndex[neighbor]] = max(longestSequence[wordToIndex[neighbor]], longestSequence[wordToIndex[word]] + 1);
        }
    }

    if (longestSequence.size() > 0)
    {
        return *max_element(longestSequence.begin(), longestSequence.end());
    }

    return 0;
}

int GetLengthOfLongestEditStepLadder(const unordered_set<string> &words)
{
    Graph graph = MakeLexicograpicalGraph(words);

    return GetLongestSequenceOfWords(graph);
}

int main()
{
    string word;
    unordered_set<string> words;

    while (cin >> word)
    {
        words.insert(word);
    }

    cout << GetLengthOfLongestEditStepLadder(words) << endl;

    return 0;
}

