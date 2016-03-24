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

#define NUMER_OF_COLORS 101

using namespace std;

struct Cube
{
    int front;
    int back;
    int left;
    int right;
    int top;
    int bottom;
    int weight;
};

struct CubeData
{
    int weight;
    string sideOnTop;
    CubeData(int w, string s) : weight(w), sideOnTop(s) {}
};

bool LargestVector(const vector<CubeData> &a, const vector<CubeData> &b)
{
    return a.size() < b.size();
}

void UpdateColorStacks(const vector<int> &colorStackSizes, const vector<vector<CubeData>> &colorStackData, vector<int> &tempColorStackSizes, vector<vector<CubeData>> &tempColorStackData, int weight, int top, int bottom, string sideOnTop)
{
    if (colorStackSizes[bottom] + 1 > colorStackSizes[top]
        && colorStackSizes[bottom] + 1 > tempColorStackSizes[top])
    {
        vector<CubeData> temp;
        CubeData cubeData(weight, sideOnTop);
        temp.push_back(cubeData);
        temp.insert(temp.end(), colorStackData[bottom].begin(), colorStackData[bottom].end());

        tempColorStackData[top] = temp;

        tempColorStackSizes[top] = colorStackSizes[bottom] + 1;
    }
}

void AddCubeToColorStacks(vector<int> &colorStackSizes, vector<vector<CubeData>> &colorStackData, const Cube &cube)
{
    vector<int> tempColorStackSizes = colorStackSizes;
    vector<vector<CubeData>> tempColorStackData = colorStackData;

    UpdateColorStacks(colorStackSizes, colorStackData, tempColorStackSizes, tempColorStackData, cube.weight, cube.front, cube.back, "front");
    UpdateColorStacks(colorStackSizes, colorStackData, tempColorStackSizes, tempColorStackData, cube.weight, cube.back, cube.front, "back");

    UpdateColorStacks(colorStackSizes, colorStackData, tempColorStackSizes, tempColorStackData, cube.weight, cube.top, cube.bottom, "top");
    UpdateColorStacks(colorStackSizes, colorStackData, tempColorStackSizes, tempColorStackData, cube.weight, cube.bottom, cube.top, "bottom");

    UpdateColorStacks(colorStackSizes, colorStackData, tempColorStackSizes, tempColorStackData, cube.weight, cube.left, cube.right, "left");
    UpdateColorStacks(colorStackSizes, colorStackData, tempColorStackSizes, tempColorStackData, cube.weight, cube.right, cube.left, "right");

    colorStackSizes = tempColorStackSizes;
    colorStackData = tempColorStackData;
}

vector<CubeData> GetLargestStackOfCubes(const vector<Cube> &cubes)
{
    vector<int> colorStackSizes(NUMER_OF_COLORS, 0);
    vector<vector<CubeData>> colorStackData(NUMER_OF_COLORS);

    // Placing cubes on top of each other. So the Cubes have to be evaluated from the bottom up
    for (int i=cubes.size() - 1; i >= 0; --i)
    {
        AddCubeToColorStacks(colorStackSizes, colorStackData, cubes[i]);
    }

    return *max_element(colorStackData.begin(), colorStackData.end(), LargestVector);
}

int main()
{
    int N;
    int caseNumber = 1;

    cin >> N;

    while (true)
    {
        vector<Cube> cubes(N);

        for (int i=0; i<N; ++i)
        {
            cubes[i].weight = i;

            cin >> cubes[i].front >> cubes[i].back >> cubes[i].left >> cubes[i].right >> cubes[i].top >> cubes[i].bottom;
        }

        vector<CubeData> stackOfCubes = GetLargestStackOfCubes(cubes);

        cout << "Case #" << caseNumber << endl;
        cout << stackOfCubes.size() << endl;

        for (const auto cubeData : stackOfCubes)
        {
            cout << cubeData.weight + 1 << ' ' << cubeData.sideOnTop << endl;
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

