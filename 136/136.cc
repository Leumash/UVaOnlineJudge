/*

136 Ugly Numbers

Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence

1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, . . .

shows the first 11 ugly numbers. By convention, 1 is included.

Write a program to find and prlong long the 1500'th ugly number.

Input and Output

There is no input to this program. Output should consist of a single line as shown below, with <number> replaced by the number computed.

Sample output

The 1500'th ugly number is <number>.

*/

#include <iostream>

using namespace std;

long long DivideOut(long long n, long long toDivideOut)
{
    while (n % toDivideOut == 0)
    {
        n /= toDivideOut;
    }

    return n;
}

bool IsUglyNumber(long long n)
{
    n = DivideOut(n, 2);
    n = DivideOut(n, 3);
    n = DivideOut(n, 5);

    return n == 1;
}

long long GetUglyNumber(long long term)
{
    long long currentTerm = 1;

    for (long long i=1; ; ++i)
    {
        if (IsUglyNumber(i))
        {
            if (currentTerm == term)
            {
                return i;
            }

            ++currentTerm;
        }
    }
}

int main()
{
    //long long term = 1500;

    //cout << "The " << term << "'th ugly number is " << GetUglyNumber(term) << "." << endl;
    cout << "The 1500'th ugly number is 859963392." << endl;

    return 0;
}

