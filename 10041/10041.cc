/*
10041 Vito’s family

The world-known gangster Vito Deadstone is moving to New York. He has a very big family there, all of them living in Lamafia Avenue. Since he will visit all his relatives very often, he is trying to find a house close to them.

Vito wants to minimize the total distance to all of them and has blackmailed you to write a program that solves his problem.

Input

The input consists of several test cases. The first line contains the number of test cases.

For each test case you will be given the integer number of relatives r (0 < r < 500) and the street numbers (also integers) s1, s2, . . . , si , . . . , sr where they live (0 < si < 30000 ). Note that several relatives could live in the same street number.

Output

For each test case your program must write the minimal sum of distances from the optimal Vito’s house to each one of his relatives. The distance between two street numbers si and sj is dij = |si − sj |.

Sample Input

2
2 2 4
3 2 4 6

Sample Output

2
4
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<int,int> GetAddressToResidents(const vector<int> &streetNumbers)
{
    unordered_map<int,int> toReturn;

    for (int num : streetNumbers)
    {
        if (toReturn.count(num) == 0)
        {
            toReturn[num] = 1;
        }
        else
        {
            ++toReturn[num];
        }
    }

    return toReturn;
}

int GetStartCost(int pos, const vector<int> &streetNumbers)
{
    int totalCost = 0;

    for (int num : streetNumbers)
    {
        totalCost += num - pos;
    }

    return totalCost;
}

int GetMinimalSumOfDistances(const vector<int> &streetNumbers)
{
    unordered_map<int,int> addressToResidents = GetAddressToResidents(streetNumbers);
    auto minmax = minmax_element(streetNumbers.begin(), streetNumbers.end());

    int start = *minmax.first - 1;
    int end = *minmax.second;

    int currentCost = GetStartCost(start, streetNumbers);
    int minCost = currentCost;

    int left = 0;
    int middle = 0;
    int right = streetNumbers.size();

    for (int pos = start + 1; pos <= end; ++pos)
    {
        left += middle;
        middle = addressToResidents[pos];
        right -= middle;

        currentCost += left;
        currentCost -= (middle + right);

        if (currentCost < minCost)
        {
            minCost = currentCost;
        }
    }

    return minCost;
}

int main()
{
    int T;
    int numRelatives;
    int temp;

    cin >> T;

    for (int i=0; i<T; ++i)
    {
        cin >> numRelatives;

        vector<int> streetNumbers;

        for (int j=0; j<numRelatives; ++j)
        {
            cin >> temp;
            streetNumbers.push_back(temp);
        }

        cout << GetMinimalSumOfDistances(streetNumbers) << endl;
    }

    return 0;
}

