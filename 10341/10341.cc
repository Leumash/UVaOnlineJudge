/*
10341 Solve It

Solve the equation:

p * e ^ −x + q * sin(x) + r * cos(x) + s * tan(x) + t * x ^ 2 + u = 0

where 0 ≤ x ≤ 1.

Input

Input consists of multiple test cases and terminated by an EOF. Each test case consists of 6 integers in a single line: p, q, r, s, t and u (where 0 ≤ p, r ≤ 20 and −20 ≤ q, s, t ≤ 0). There will be maximum 2100 lines in the input file.

Output

For each set of input, there should be a line containing the value of x, correct up to 4 decimal places, or the string ‘No solution’, whichever is applicable.

Sample Input

0 0 0 0 -2 1
1 0 0 0 -1 2
1 -1 1 -1 -1 1

Sample Output

0.7071
No solution
0.7554

*/

/*

0 ≤ p, r ≤ 20

−20 ≤ q, s, t ≤ 0

p * e ^ −x + q * sin(x) + r * cos(x) + s * tan(x) + t * x ^ 2 + u = 0

f'(x) = -p*e^-x + q * cos(x) - r * sin(x) + s / (cos ^ 2 (x)) + t * 2 * x <= 0

Because f'(x) <= 0, the f(x) is a non-increasing function

*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

#define EPSILON 0.000001
#define EULERS_NUMBER 2.71828182846

using namespace std;

bool IsZero(double num)
{
    return abs(num) < EPSILON;
}

double SolveEquation(int p, int q, int r, int s, int t, int u, double x)
{
    return p * pow(EULERS_NUMBER, -x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

bool GetX(int p, int q, int r, int s, int t, int u, double &x)
{
    if (SolveEquation(p,q,r,s,t,u,0) * SolveEquation(p,q,r,s,t,u,1) > 0)
    {
        return false;
    }

    double low = 0;
    double high = 1;

    double median = 0.5;
    double fx = SolveEquation(p,q,r,s,t,u,median);

    while (!IsZero(fx))
    {

        if (fx > 0)
        {
            low = median;
        }
        else
        {
            high = median;
        }

        median = (high-low) / 2 + low;
        fx = SolveEquation(p,q,r,s,t,u,median);
    }

    x = median;

    return true;
}

int main()
{
    int p, q, r, s, t, u;
    double x;
    string line;

    while (getline(cin, line))
    {
        stringstream ss;

        ss << line;

        ss >> p >> q >> r >> s >> t >> u;

        if (GetX(p,q,r,s,t,u,x))
        {
            cout << fixed << setprecision(4) << x << endl;
        }
        else
        {
            cout << "No solution" << endl;
        }
    }

    return 0;
}

