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

double GetDistanceBetweenPointAndLine(Point p0, Point p1, Point p2)
{
    return abs((p2.y - p1.y)* p0.x - (p2.x - p1.x) * p0.y + p2.x * p1.y - p2.y * p1.x)
        / sqrt(pow(p2.y - p1.y,2) + pow(p2.x - p1.x,2));
}

double GetFurtherestDistanceFromLine(const vector<Point> &convexHull, Point a, Point b)
{
    double furtherestDistancePointToLine;

    for (Point p : convexHull)
    {
        double distance = GetDistanceBetweenPointAndLine(p, a, b);

        if (distance > furtherestDistancePointToLine)
        {
            furtherestDistancePointToLine = distance;
        }
    }

    return furtherestDistancePointToLine;
}

double GetDistance(Point a, Point b)
{
    return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
}

Point GetClosestPointOnLine(Point p, Point a, Point b)
{
    Point toReturn;

    if (a.x == b.x)
    {
        toReturn.x = a.x;
        toReturn.y = p.y;

        return toReturn;
    }
    else if (a.y == b.y)
    {
        toReturn.y = a.y;
        toReturn.x = p.x;

        return toReturn;
    }

    // y = Ax + C, y = Bx + D
    // Line equation
    double A = (a.y - b.y) / (a.x - b.x);
    double C = a.y - a.x * A;
    double B = -1 / A;
    double D = p.y - p.x * B;

    toReturn.x = (D - C) / (A - B);
    toReturn.y = (A * D - B * C) / (A - B);

    return toReturn;
}

vector<Point> GetClosestPointsOnLine(const vector<Point> &convexHull, Point a, Point b)
{
    vector<Point> closestPointsOnLine;

    for (Point p : convexHull)
    {
        Point closestPoint = GetClosestPointOnLine(p, a, b);

        closestPointsOnLine.push_back(closestPoint);
    }

    return closestPointsOnLine;
}

double GetLongestDistanceBetweenTwoPointsAlongLine(const vector<Point> &convexHull, Point a, Point b)
{
    vector<Point> pointsOnLine = GetClosestPointsOnLine(convexHull, a, b);

    sort(pointsOnLine.begin(), pointsOnLine.end());

    return GetDistance(pointsOnLine[0], pointsOnLine[pointsOnLine.size() - 1]);
}

double GetRectangleArea(const vector<Point> &convexHull, Point a, Point b)
{
    double furtherestDistancePointToLine = GetFurtherestDistanceFromLine(convexHull, a, b);
    double longestDistanceBetweenTwoPointsAlongLine = 
        GetLongestDistanceBetweenTwoPointsAlongLine(convexHull, a, b);

    return furtherestDistancePointToLine * longestDistanceBetweenTwoPointsAlongLine;
}

double GetAreaOfSmallestBoundingRectangle(vector<Point> points)
{
    set<Point> unique;

    for (Point p : points)
    {
        unique.insert(p);
    }

    points = vector<Point>();

    for (Point p : unique)
    {
        points.push_back(p);
    }

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

