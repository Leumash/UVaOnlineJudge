#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double n, p;

    while (cin >> n >> p)
    {
        cout << (int) round(pow(p, 1.0 / n)) << endl;
    }

    return 0;
}

