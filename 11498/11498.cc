#include <iostream>
#include <string>

using namespace std;

string GetCountry(int N, int M, int X, int Y)
{
    if (N == X || M == Y)
    {
        return "divisa";
    }

    if (X > N)
    {
        if (Y > M)
        {
            return "NE";
        }
        else
        {
            return "SE";
        }
    }
    else
    {
        if (Y > M)
        {
            return "NO";
        }
        else
        {
            return "SO";
        }
    }
}

int main()
{
    int K;
    int N, M;
    int X, Y;

    while (true)
    {
        cin >> K;

        if (K == 0)
        {
            break;
        }

        cin >> N >> M;

        for (int i=0; i<K; ++i)
        {
            cin >> X >> Y;

            cout << GetCountry(N, M, X, Y) << endl;
        }
    }

    return 0;
}

