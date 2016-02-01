/*
10038 Jolly Jumpers

A sequence of n > 0 integers is called a jolly jumper if the absolute values of the difference between successive elements take on all the values 1 through n − 1. For instance,

1 4 2 3

is a jolly jumper, because the absolutes differences are 3, 2, and 1 respectively. The definition implies that any sequence of a single integer is a jolly jumper. You are to write a program to determine whether or not each of a number of sequences is a jolly jumper.

Input

Each line of input contains an integer n ≤ 3000 followed by n integers representing the sequence.

Output

For each line of input, generate a line of output saying ‘Jolly’ or ‘Not jolly’.

Sample Input

4 1 4 2 3
5 1 4 2 -1 6

Sample Output

Jolly
Not jolly

*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int n;

    while (cin >> n)
    {
        vector<bool> seen(n, false);

        int previous;

        cin >> previous;

        for (int i=0; i<n-1; ++i)
        {
            int current;

            cin >> current;

            int difference = abs(current - previous);

            if (difference < n)
            {
                seen[difference] = true;
            }

            previous = current;
        }

        bool isJolly = true;

        if (seen[0] == true)
        {
            isJolly = false;
        }

        for (int i=1; i<seen.size(); ++i)
        {
            if (seen[i] == false)
            {
                isJolly = false;
            }
        }

        if (isJolly)
        {
            cout << "Jolly" << endl;
        }
        else
        {
            cout << "Not jolly" << endl;
        }
    }

    return 0;
}

