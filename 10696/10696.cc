#include <iostream>

using namespace std;

int f91(int N)
{
    if (N <= 100)
    {
        return f91(f91(N+11));
    }
    else
    {
        return N - 10;
    }
}

int main()
{
    int number;

    while (cin >> number)
    {
        if (number == 0)
        {
            break;
        }

        cout << "f91(" << number << ") = " << f91(number) << endl;
    }

    return 0;
}

