/*

Children are taught to add multi-digit numbers from right-to-left one digit at a time. Many find the “carry” operation - in which a 1 is carried from one digit position to be added to the next - to be a significant challenge. Your job is to count the number of carry operations for each of a set of addition problems so that educators may assess their difficulty.

Input

Each line of input contains two unsigned integers less than 10 digits. The last line of input contains ‘0 0’.

Output

For each line of input except the last you should compute and print the number of carry operations that would result from adding the two numbers, in the format shown below.

Sample Input

123 456
555 555
123 594
0 0

Sample Output

No carry operation.
3 carry operations.
1 carry operation.

*/

#include <iostream>
#include <cmath>

using namespace std;

int GetLength(long long n)
{
    return floor(log10(n)) + 1;
}

long long GetCarryOperations(long long a, long long b)
{
    long long carryOpertions = 0;
    long long total = a + b;

    int totalLength = GetLength(total);
    int aLength = GetLength(a);
    int bLength = GetLength(b);

    if (totalLength > aLength && totalLength > bLength)
    {
        ++carryOpertions;
    }

    while (!(a == 0 && b == 0))
    {
        long long sum = total % 10;
        long long aPartial = a % 10;
        long long bPartial = b % 10;

        if (sum != (aPartial + bPartial) % 10)
        {
            ++carryOpertions;
        }

        total /= 10;
        a /= 10;
        b /= 10;
    }

    return carryOpertions;
}

void PrintCarryOperations(int carryOpertions)
{
    if (carryOpertions == 0)
    {
        cout << "No carry operation." << endl;
    }
    else if (carryOpertions == 1)
    {
        cout << "1 carry operation." << endl;
    }
    else
    {
        cout << carryOpertions << " carry operations." << endl;
    }
}

int main()
{
    long long a, b;

    while (cin >> a >> b)
    {
        if (a == 0 && b == 0)
        {
            break;
        }

        int carryOpertions = GetCarryOperations(a,b);

        PrintCarryOperations(carryOpertions);
    }

    return 0;
}

