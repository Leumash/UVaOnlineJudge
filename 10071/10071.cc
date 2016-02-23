#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int main()
{
    double v, t;
    string temp;

    while (getline(cin, temp))
    {
        stringstream ss;
        ss << temp;

        ss >> v >> t;

        if (t == 0)
        {
            cout << 0 << endl;
            continue;
        }

        double acceleration = v / t;

        t = t * 2;

        cout << 0.5 * acceleration * t * t << endl;
    }

    return 0;
}

