#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int GetMinimumNumberOfMoves(vector<int> &wall)
{
    int totalBricks = 0;

    for (int stack : wall)
    {
        totalBricks += stack;
    }

    int desiredHeight = totalBricks / wall.size();

    int moves = 0;
    for (int stack : wall)
    {
        moves += abs(desiredHeight - stack);
    }

    return moves / 2;
}

int main()
{
    int N;
    int iteration = 1;

    cin >> N;

    while (N != 0)
    {
        vector<int> wall(N);

        for (int i=0; i<N; ++i)
        {
            cin >> wall[i];
        }

        cout << "Set #" << iteration << endl;
        cout << "The minimum number of moves is ";
        cout << GetMinimumNumberOfMoves(wall);
        cout << '.' << endl << endl;

        cin >> N;
        ++iteration;
    }

    return 0;
}

