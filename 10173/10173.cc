/*

Given the Cartesian coordinates of n (> 0) 2-dimensional points, write a program that computes the area of their smallest bounding rectangle (smallest rectangle containing all the given points).

Input

The input file may contain multiple test cases. Each test case begins with a line containing a positive integer n (< 1001) indicating the number of points in this test case. Then follows n lines each containing two real numbers giving respectively the x- and y-coordinates of a point. The input terminates with a test case containing a value 0 for n which must not be processed.

Output

For each test case in the input print a line containing the area of the smallest bounding rectangle rounded to the 4th digit after the decimal point.

Sample Input

3
-3.000 5.000
7.000 9.000
17.000 5.000
4
10.000 10.000
10.000 20.000
20.000 20.000
20.000 10.000
0

Sample Output

80.0000
100.0000

*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

struct Point
{
    double x;
    double y;

    bool operator < (const Point &p) const
    {
        return x != p.x ? x < p.x : y < p.y;
    }
};

double GetCrossProduct(Point O, Point A, Point B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

bool DoesNotMakeCounterClockwiseTurn(Point p, const vector<Point> &hull)
{
    double crossProduct = GetCrossProduct(hull[hull.size()-2], hull[hull.size()-1], p);

    return crossProduct <= 0;
}

vector<Point> GetConvexHull(vector<Point> points)
{
    sort(points.begin(), points.end());

    vector<Point> upperHull;
    vector<Point> lowerHull;

    for (int i=0; i<points.size(); ++i)
    {
        while (lowerHull.size() >= 2 && DoesNotMakeCounterClockwiseTurn(points[i], lowerHull))
        {
            lowerHull.pop_back();
        }

        lowerHull.push_back(points[i]);
    }

    for (int i=points.size()-1; i >= 0; --i)
    {
        while (upperHull.size() >= 2 && DoesNotMakeCounterClockwiseTurn(points[i], upperHull))
        {
            upperHull.pop_back();
        }

        upperHull.push_back(points[i]);
    }

    lowerHull.pop_back();
    upperHull.pop_back();

    vector<Point> convexHull(lowerHull);
    convexHull.insert(convexHull.end(), upperHull.begin(), upperHull.end());

    return convexHull;
}

double GetAngle(Point a, Point b)
{
    double x = a.x - b.x;
    double y = a.y - b.y;

    return atan(y/x);
}

Point RotatePoint(Point p, double angle)
{
    /*
        Rotation Matrix:

        [ x']   [ cos(θ) -sin(θ) ] [ x ]
        |   | = |                | |   |
        [ y']   [ sin(θ)  cos(θ) ] [ y ]

    */

    Point rotatedPoint;

    double xPrime = cos(angle) * p.x + -1 * sin(angle) * p.y;
    double yPrime = sin(angle) * p.x + cos(angle) * p.y;

    rotatedPoint.x = xPrime;
    rotatedPoint.y = yPrime;

    return rotatedPoint;
}

vector<Point> RotateConvexHull(const vector<Point> &convexHull, double angle)
{
    vector<Point> rotatedConvexHull;

    for (Point p : convexHull)
    {
        Point rotatedPoint = RotatePoint(p, angle);

        rotatedConvexHull.push_back(rotatedPoint);
    }

    return rotatedConvexHull;
}

double GetRectangleArea(const vector<Point> &convexHull, Point a, Point b)
{
    double angle = GetAngle(a, b);

    vector<Point> rotatedConvexHull = RotateConvexHull(convexHull, -1 * angle);

    double xMin = numeric_limits<double>::max();
    double xMax = numeric_limits<double>::lowest();
    double yMin = numeric_limits<double>::max();
    double yMax = numeric_limits<double>::lowest();

    for (Point p : rotatedConvexHull)
    {
        xMin = min(xMin, p.x);
        xMax = max(xMax, p.x);
        yMin = min(yMin, p.y);
        yMax = max(yMax, p.y);
    }

    return (xMax - xMin) * (yMax - yMin);
}

vector<Point> GetUniquePoints(vector<Point> points)
{
    set<Point> unique;

    for (Point p : points)
    {
        unique.insert(p);
    }

    vector<Point> uniquePoints;

    for (Point p : unique)
    {
        uniquePoints.push_back(p);
    }

    return uniquePoints;
}

double GetAreaOfSmallestBoundingRectangle(vector<Point> points)
{
    points = GetUniquePoints(points);

    if (points.size() <= 2)
    {
        return 0;
    }

    vector<Point> convexHull = GetConvexHull(points);
    vector<double> areas;

    for (int i=0; i<convexHull.size(); ++i)
    {
        double area = GetRectangleArea(convexHull, convexHull[i], convexHull[(i + 1) % convexHull.size()]);

        areas.push_back(area);
    }

    return *min_element(areas.begin(), areas.end());
}

int main()
{
    int N;

    cin >> N;

    while (N != 0)
    {
        vector<Point> points(N);

        for (int i=0; i<N; ++i)
        {
            cin >> points[i].x >> points[i].y;
        }

        double areaOfSmallestBoundingRectangle = GetAreaOfSmallestBoundingRectangle(points);

        cout << fixed << setprecision(4) << areaOfSmallestBoundingRectangle << endl;

        cin >> N;
    }

    return 0;
}

