/*

10152 ShellSort

He made each turtle stand on another one’s back
And he piled them all up in a nine-turtle stack.
And then Yertle climbed up. He sat down on the pile.
What a wonderful view! He could see ’most a mile!

King Yertle wishes to rearrange his turtle throne to place his highest-ranking nobles and closest advisors nearer to the top. A single operation is available to change the order of the turtles in the stack: a turtle can crawl out of its position in the stack and climb up over the other turtles to sit on the top.

Given an original ordering of a turtle stack and a required ordering for the same turtle stack, your job is to determine a minimal sequence of operations that rearranges the original stack into the required stack.

Input

The first line of the input consists of a single integer K giving the number of test cases. Each test case consist on an integer n giving the number of turtles in the stack. The next n lines specify the original ordering of the turtle stack. Each of the lines contains the name of a turtle, starting with the turtle on the top of the stack and working down to the turtle at the bottom of the stack. Turtles have unique names, each of which is a string of no more than eighty characters drawn from a character set consisting of the alphanumeric characters, the space character and the period (‘.’). The next n lines in the input gives the desired ordering of the stack, once again by naming turtles from top to bottom. Each test case consists of exactly 2n + 1 lines in total. The number of turtles (n) will be less than or equal to two hundred.

Output

For each test case, the output consists of a sequence of turtle names, one per line, indicating the order in which turtles are to leave their positions in the stack and crawl to the top. This sequence of operations should transform the original stack into the required stack and should be as short as possible. If more than one solution of shortest length is possible, any of the solutions may be reported.

Print a blank line after each test case.

Sample Input

2
3
Yertle
Duke of Earl
Sir Lancelot
Duke of Earl
Yertle
Sir Lancelot
9
Yertle
Duke of Earl
Sir Lancelot
Elizabeth Windsor
Michael Eisner
Richard M. Nixon
Mr. Rogers
Ford Perfect
Mack
Yertle
Richard M. Nixon
Sir Lancelot
Duke of Earl
Elizabeth Windsor
Michael Eisner
Mr. Rogers
Ford Perfect
Mack

Sample Output

Duke of Earl

Sir Lancelot
Richard M. Nixon
Yertle

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool IsSorted(vector< pair<int,string> > &toCheck)
{
    for (int i=0; i<toCheck.size()-1; ++i)
    {
        if (toCheck[i].first > toCheck[i+1].first)
        {
            return false;
        }
    }

    return true;
}

vector< pair<int,string> > GetExpectedAndPos(vector<string> &expected)
{
    vector< pair<int,string> > toReturn;

    for (int i=0; i<expected.size(); ++i)
    {
        toReturn.push_back(make_pair(i, expected[i]));
    }

    return toReturn;
}

vector< pair<int,string> > GetInitialAndPos(vector<string> &initial, vector<string> &expected)
{
    vector< pair<int,string> > expectedAndPos = GetExpectedAndPos(expected);
    vector< pair<int,string> > initialAndPos;

    for (string name : initial)
    {
        for (pair<int,string> p : expectedAndPos)
        {
            if (p.second == name)
            {
                initialAndPos.push_back(p);
                break;
            }
        }
    }

    return initialAndPos;
}

void PrintMoves(vector<string> &moves)
{
    for (string move : moves)
    {
        cout << move << endl;
    }
}

void DoSomething(vector<string> &initial, vector<string> &expected)
{
    vector< pair<int,string> > initialAndPos = GetInitialAndPos(initial, expected);

    vector<string> moves;

    while (!IsSorted(initialAndPos))
    {
        int largestSeenSoFar = initialAndPos[0].first;
        int largestOutOfPositionElement = 0;
        int elementToMove = 0;

        for (int i=1; i<initialAndPos.size(); ++i)
        {
            int currentElementPos = initialAndPos[i].first;

            if (currentElementPos < largestSeenSoFar)
            {
                if (currentElementPos >= largestOutOfPositionElement)
                {
                    largestOutOfPositionElement = currentElementPos;
                    elementToMove = i;
                }
            }

            largestSeenSoFar = max(largestSeenSoFar, currentElementPos);
        }

        pair<int,string> toMove = initialAndPos[elementToMove];

        initialAndPos.erase(initialAndPos.begin() + elementToMove);

        initialAndPos.insert(initialAndPos.begin(), toMove);

        moves.push_back(toMove.second);
    }

    PrintMoves(moves);
}

int main()
{
    int T, N;

    cin >> T;
    string temp;

    for (int t=0; t<T; ++t)
    {
        cin >> N;

        vector<string> initial(N);
        vector<string> expected(N);

        getline(cin, temp);

        for (int i=0; i<N; ++i)
        {
            getline(cin, initial[i]);
        }

        for (int i=0; i<N; ++i)
        {
            getline(cin, expected[i]);
        }

        DoSomething(initial, expected);

        cout << endl;
    }

    return 0;
}

