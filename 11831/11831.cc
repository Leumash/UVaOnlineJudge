/*

11831 Sticker Collector Robots

One of the favorite sports in RoboLand is the Robots Rally. This rally is practiced in a giant rectangular arena of square cells with dimensions N rows by M columns. Some cells are empty, some contain a sticker for the World Footbal Cup Album (much appreciated by artificial intelligences in RoboLand) and some are occupied by pillars which support the roof of the arena. During the rally the robots can occupy any cell in the arena, except those containing pillars, since they block the robot movement.  The path of the robot in the arena during the rally is determined by a sequence of instructions. Each instruction is represented by one of the following characters: ‘D’, ‘E’ and ‘F’, meaning, respectively, “turn 90 degrees to the right”, “turn 90 degrees to the left” and “move forward one cell”. Robots start the rally in some initial position in the arena and follow closely the sequence of instructions given (after all, they are robots!). Whenever a robot occupies a cell that contains a Cup sticker he collects it. Stickers are not replaced, that is, each sticker can be collected only once. When a robot tries to move into a cell which contains a pillar he stalls, remaining in the cell where he was, with the same orientation.  The same happens when a robot tries to leave the arena.

Given the map of the arena, describing the position of pillars and stickers, and the sequence of instructions of a robot, you must write a program to determine the number of stickers collected by the robot.

Input

The input contains several test cases. The first line of a test case contains three integers N, M and S (1 ≤ N, M ≤ 100, 1 ≤ S ≤ 5 × 10^4), separated by white spaces, indicating respectively the number of rows, the number of columns of the arena and the number of instructions to the robot. Each of the following N lines describes a cell line of the arena and contains a string with M characters. The first line to appear in the description of the arena is the one more to the North, the first column to appear in description of a cell line of the arena is the one more to the West.

Each cell in the arena is described by one of the following characters:

    • ‘.’ — normal cell;
    • ‘*’ — cell which contains a sticker;
    • ‘#’ — cell which contains a pillar;
    • ‘N’, ‘S’, ‘L’, ‘O’ — cell where the robot starts the rally (only one in the arena). The letter represents the initial robot orientation (North, South, East and West, respectively).

The last line in the input contains a sequence of S characters among ‘D’, ‘E’ and ‘F’, representing the instructions to the robot.

The last test case is followed by a line which contains only three numbers zero separated by a blank space.

Output

For each rally described in the input your program must print a single line containing a single integer indicating the number of stickers that the robot collected during the rally.

Sample Input

3 3 2
***
*N*
***
DE
4 4 5
...#
*#O.
*.*.
*.#.
FFEFF
10 10 20
....*.....
.......*..
.....*....
..*.#.....
...#N.*..*
...*......
..........
..........
..........
..........
FDFFFFFFEEFFFFFFEFDF
0 0 0

Sample Output

0
1
3

*/

#include <iostream>
#include <vector>

using namespace std;

enum Direction {NORTH, SOUTH, EAST, WEST};

void GetRobotPosition(const vector<vector<char>> &arena, int &rowPos, int &colPos)
{
    for (unsigned int row=0; row<arena.size(); ++row)
    {
        for (unsigned int col=0; col<arena[0].size(); ++col)
        {
            if (arena[row][col] == 'N' || arena[row][col] == 'S'
                || arena[row][col] == 'L' || arena[row][col] == 'O')
            {
                rowPos = row;
                colPos = col;

                return;
            }
        }
    }
}

Direction GetDirection(const vector<vector<char>> &arena, int rowPos, int colPos)
{
    char direction = arena[rowPos][colPos];

    if (direction == 'N')
    {
        return NORTH;
    }
    else if (direction == 'S')
    {
        return SOUTH;
    }
    else if (direction == 'L')
    {
        return EAST;
    }
    else if (direction == 'O')
    {
        return WEST;
    }
    else
    {
        cout << "Error!!!" << endl;
        exit(1);
    }
}

Direction TurnRight(Direction currentDirection)
{
    switch(currentDirection)
    {
        case NORTH:
            return EAST;
        case SOUTH:
            return WEST;
        case EAST:
            return SOUTH;
        default:
            return NORTH;
    }
}

Direction TurnLeft(Direction currentDirection)
{
    switch(currentDirection)
    {
        case NORTH:
            return WEST;
        case SOUTH:
            return EAST;
        case EAST:
            return NORTH;
        default:
            return SOUTH;
    }
}

void GetNewPosition(int row, int col, Direction direction, int &newRow, int &newCol)
{
    switch (direction)
    {
        case NORTH:
            --row;
            break;
        case SOUTH:
            ++row;
            break;
        case EAST:
            ++col;
            break;
        default:
            --col;
            break;
    }

    newRow = row;
    newCol = col;
}

bool IsInArena(const vector<vector<char>> &arena, int row, int col)
{
    if (row < 0 || col < 0 || row >= (int) arena.size() || col >= (int) arena[0].size())
    {
        return false;
    }

    return true;
}

void MoveForward(vector<vector<char>> &arena, int &rowPos, int &colPos, Direction robotDirection, int &numberOfStickers)
{
    int newRowPos, newColPos;

    GetNewPosition(rowPos, colPos, robotDirection, newRowPos, newColPos);

    if (!IsInArena(arena, newRowPos, newColPos))
    {
        return;
    }

    if (arena[newRowPos][newColPos] == '#')
    {
        return;
    }

    if (arena[newRowPos][newColPos] == '*')
    {
        arena[newRowPos][newColPos] = '.';
        ++numberOfStickers;
    }

    rowPos = newRowPos;
    colPos = newColPos;
}

int GetNumberOfStickersCollected(vector<vector<char>> &arena, const vector<char> &instructions)
{
    int numberOfStickers = 0;
    int rowPos, colPos;
    Direction robotDirection;

    GetRobotPosition(arena, rowPos, colPos);
    robotDirection = GetDirection(arena, rowPos, colPos);

    arena[rowPos][colPos] = '.';

    for (char instruction : instructions)
    {
        if (instruction == 'D')
        {
            robotDirection = TurnRight(robotDirection);
        }
        else if (instruction == 'E')
        {
            robotDirection = TurnLeft(robotDirection);
        }
        else
        {
            MoveForward(arena, rowPos, colPos, robotDirection, numberOfStickers);

        }
    }

    return numberOfStickers;
}

int main()
{
    int N, M, S;

    while (true)
    {
        cin >> N >> M >> S;

        if (N == 0 && M == 0 && S == 0)
        {
            break;
        }

        vector<vector<char>> arena(N, vector<char>(M));

        for (int row=0; row<N; ++row)
        {
            for (int col=0; col<M; ++col)
            {
                cin >> arena[row][col];
            }
        }

        vector<char> instructions(S);

        for (int i=0; i<S; ++i)
        {
            cin >> instructions[i];
        }

        cout << GetNumberOfStickersCollected(arena, instructions) << endl;
    }

    return 0;
}

