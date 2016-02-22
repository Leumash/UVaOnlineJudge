/*

10135 - Herding Frosh

One day, a lawn in the centre of campus became infested with Frosh. In an effort to beautify the campus, one of our illustrious senior classmen decided to round them up using a length of pink silk.

Your job is to compute how much silk was required to complete the task.

The senior classman tied the silk to a telephone post, and walked around the perimeter of the area containing the Frosh, drawing the silk taught so as to encircle all of them. He then returned to the telephone post. The senior classman used the minimum amount of silk necessary to encircle all the frosh plus one extra metre at each end to tie it.

You may assume that the telephone post is at coordinates (0,0), where the first dimension is North/South and the second dimension is East/West. The coordinates of the Frosh are given in metres relative to the post. There are no more than 1000 Frosh.

Input

The input begins with a single positive integer on a line by itself indicating the number of the cases following, each of them as described below. This line is followed by a blank line, and there is also a blank line between two consecutive inputs.

The input consists of a line specifying the number of Frosh, followed by one line per Frosh with two real numbers his or her position.

Output

For each test case, the output must follow the description below. The outputs of two consecutive cases will be separated by a blank line.

The output consists of a single number - the length of silk in metres, to two decimal places.

Sample Input

1

4
1.0 1.0
-1.0 1.0
-1.0 -1.0
1.0 -1.0

Sample Output

10.83

*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>

#define EPSILON 0.000000001
#define PI 3.14159265359

using namespace std;

struct Vector2d
{
    double x;
    double y;

    Vector2d() {}
    Vector2d(double x, double y) : x(x), y(y) {};

    double dot(const Vector2d &other)
    {
        return x * other.x + y * other.y;
    }

    void normalize()
    {
        double magnitude = sqrt(pow(x,2) + pow(y,2));

        x /= magnitude;
        y /= magnitude;
    }
};

bool IsEqual(double a, double b)
{
    return abs(a - b) < EPSILON;
}

struct Point
{
    double x;
    double y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {};

    bool operator < (const Point &other) const
    {
        if (IsEqual(x, other.x))
        {
            if (IsEqual(y, other.y))
            {
                return false;
            }

            return y < other.y;
        }

        return x < other.x;
    }

    bool operator == (const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

vector<Point> RemoveDuplicates(const vector<Point> &points)
{
    set<Point> uniquePoints(points.begin(), points.end());

    return vector<Point>(uniquePoints.begin(), uniquePoints.end());
}

double GetCrossProduct(Point O, Point A, Point B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

bool DoesNotTurnCounterClockwise(const Point &p, const vector<Point> &hull)
{
    double crossProduct = GetCrossProduct(hull[hull.size()-2], hull[hull.size()-1], p);

    // If '=' is included, then points that lie on an edge are not included
    return crossProduct <= EPSILON;
}

vector<Point> GetConvexHull(vector<Point> points)
{
    sort(points.begin(), points.end());

    vector<Point> upperHull;
    vector<Point> lowerHull;

    for (int i=0; i<points.size(); ++i)
    {
        while (lowerHull.size() >= 2 && DoesNotTurnCounterClockwise(points[i], lowerHull))
        {
            lowerHull.pop_back();
        }

        lowerHull.push_back(points[i]);
    }

    for (int i=points.size()-1; i>=0; --i)
    {
        while (upperHull.size() >= 2 && DoesNotTurnCounterClockwise(points[i], upperHull))
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

double GetDistance(const Point &a, const Point &b)
{
    return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
}

bool IsOriginInConvexHull(const vector<Point> &convexHull)
{
    Point origin(0,0);

    for (Point p : convexHull)
    {
        if (p == origin)
        {
            return true;
        }
    }

    return false;
}

bool IsPointOnLine(Point a, Point l1, Point l2)
{
    double lengthOfLine = GetDistance(l1, l2);
    double lengthToTest = GetDistance(a, l1) + GetDistance(a, l2);


    return abs(lengthOfLine - lengthToTest) < EPSILON;
}

bool IsOriginOnEdgeOfConvexHull(const vector<Point> &convexHull)
{
    Point origin(0,0);

    for (int i=0; i<convexHull.size(); ++i)
    {
        if (IsPointOnLine(origin, convexHull[i], convexHull[(i+1) % convexHull.size()]))
        {
            return true;
        }
    }

    return false;
}

double GetPerimeter(const vector<Point> &convexHull)
{
    double perimeter = 0;

    for (int i=0; i<convexHull.size(); ++i)
    {
        double length = GetDistance(convexHull[i], convexHull[(i+1) % convexHull.size()]);

        perimeter += length;
    }

    return perimeter;
}

bool IsInsideTriangle(const Point &p0, const Point &p1, const Point &p2, const Point &p3)
{
    double denominator = ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));
    double a = ((p2.y - p3.y) * (p0.x - p3.x) + (p3.x - p2.x) * (p0.y - p3.y)) / denominator;
    double b = ((p3.y - p1.y) * (p0.x - p3.x) + (p1.x - p3.x) * (p0.y - p3.y)) / denominator;
    double c = 1 - a - b;

    return (0 - EPSILON) <= a && a <= (1 + EPSILON)
        && (0 - EPSILON) <= b && b <= (1 + EPSILON)
        && (0 - EPSILON) <= c && c <= (1 + EPSILON);
}

vector<Point> GetPointsInsideTriangle(const Point &p1, const Point &p2, const Point &p3, const vector<Point> &points)
{
    vector<Point> pointsInsideTriangle;

    for (Point p0 : points)
    {
        if (IsInsideTriangle(p0, p1, p2, p3))
        {
            pointsInsideTriangle.push_back(p0);
        }
    }

    return pointsInsideTriangle;
}

vector<Point> RemovePoint(vector<Point> points, Point toRemove)
{
    points.erase(remove(points.begin(), points.end(), toRemove), points.end());

    return points;
}

Vector2d Rotate(const Vector2d &v, double radians)
{
    Vector2d toReturn;

    toReturn.x = v.x * cos(radians) - v.y * sin(radians);
    toReturn.y = v.x * sin(radians) + v.y * cos(radians);

    return toReturn;
}

Vector2d GetNormalVector(const Vector2d &v)
{
    if (v.x == 0)
    {
        return Vector2d(1,0);
    }

    if (v.y == 0)
    {
        return Vector2d(0,1);
    }

    const double degrees = 90;

    return Rotate(v, degrees * PI / 180.0);
}

int GetSign(double x)
{
    if(x < -EPSILON)
    {
        return -1;
    }
    else if(x > EPSILON)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void PartitionPointsWithLine(const Point &pointWithLine, const Point &pointOnLine, const vector<Point> &pointsToPartition, vector<Point> &pointsWithLine, vector<Point> &pointsWithoutLine)
{
    Point origin(0,0);

    Vector2d line(pointOnLine.x, pointOnLine.y);
    Vector2d normal = GetNormalVector(line);
    normal.normalize();
    Vector2d signVector(pointWithLine.x, pointWithLine.y);
    signVector.normalize();

    int normalSign = GetSign(normal.dot(signVector));

    for (Point p : pointsToPartition)
    {
        Vector2d pointVector(p.x - pointOnLine.x, p.y - pointOnLine.y);
        pointVector.normalize();

        int pointSign = GetSign(normal.dot(pointVector));

        if (pointSign == 0 || normalSign == pointSign)
        {
            pointsWithLine.push_back(p);
        }
        else
        {
            pointsWithoutLine.push_back(p);
        }
    }
}

double GetMinimumSilkLengthIfOriginMustBeVisited(const Point &a, const Point &b, const vector<Point> &points)
{
    vector<double> silkLengths;
    vector<Point> pointsInsideTriangle = GetPointsInsideTriangle(a, b, Point(0,0), points);

    pointsInsideTriangle = RemovePoint(pointsInsideTriangle, a);
    pointsInsideTriangle = RemovePoint(pointsInsideTriangle, b);
    pointsInsideTriangle = RemovePoint(pointsInsideTriangle, Point(0,0));

    for (Point p : pointsInsideTriangle)
    {
        vector<Point> pointsOnSideAWithLine, pointsOnSideBWithoutLine;
        vector<Point> pointsOnSideAWithoutLine, pointsOnSideBWithLine;

        PartitionPointsWithLine(a, p, pointsInsideTriangle,
            pointsOnSideAWithLine, pointsOnSideBWithoutLine);
        PartitionPointsWithLine(b, p, pointsInsideTriangle, 
            pointsOnSideBWithLine, pointsOnSideAWithoutLine);

        pointsOnSideAWithLine.push_back(Point(0,0));
        pointsOnSideAWithoutLine.push_back(Point(0,0));
        pointsOnSideBWithLine.push_back(Point(0,0));
        pointsOnSideBWithoutLine.push_back(Point(0,0));

        pointsOnSideAWithLine.push_back(a);
        pointsOnSideAWithoutLine.push_back(a);
        pointsOnSideBWithLine.push_back(b);
        pointsOnSideBWithoutLine.push_back(b);

        vector<Point> convexHullAWithLine = GetConvexHull(pointsOnSideAWithLine);
        vector<Point> convexHullAWithoutLine = GetConvexHull(pointsOnSideAWithoutLine);
        vector<Point> convexHullBWithLine = GetConvexHull(pointsOnSideBWithLine);
        vector<Point> convexHullBWithoutLine = GetConvexHull(pointsOnSideBWithoutLine);

        double lengthOfHalfHullAWithLine = GetPerimeter(convexHullAWithLine) - GetDistance(Point(0,0), a);
        double lengthOfHalfHullAWithoutLine = GetPerimeter(convexHullAWithoutLine) - GetDistance(Point(0,0), a);
        double lengthOfHalfHullBWithLine = GetPerimeter(convexHullBWithLine) - GetDistance(Point(0,0), b);
        double lengthOfHalfHullBWithoutLine = GetPerimeter(convexHullBWithoutLine) - GetDistance(Point(0,0), b);

        silkLengths.push_back(lengthOfHalfHullAWithLine + lengthOfHalfHullBWithoutLine);
        silkLengths.push_back(lengthOfHalfHullAWithoutLine + lengthOfHalfHullBWithLine);
    }

    if (silkLengths.size() > 0)
    {
        return *min_element(silkLengths.begin(), silkLengths.end());
    }
    else
    {
        return GetDistance(Point(0,0), a) + GetDistance(Point(0,0), b);
    }
}

vector< pair<double,double> > GetEdgeLengthAndReplacements(const vector<Point> &convexHull, const vector<Point> &points)
{
    vector< pair<double,double> > edgeLengthAndReplacements;

    for (int i=0; i<convexHull.size(); ++i)
    {
        double lengthOfEdge = GetDistance(convexHull[i], convexHull[(i+1) % convexHull.size()]);
        double lengthIfOriginIsVisited = GetMinimumSilkLengthIfOriginMustBeVisited(
            convexHull[i],
            convexHull[(i+1) % convexHull.size()],
            points);

        edgeLengthAndReplacements.push_back(make_pair(lengthOfEdge, lengthIfOriginIsVisited));
    }

    return edgeLengthAndReplacements;
}

pair<double,double> GetMinimumDistance(const vector< pair<double,double> > &edgeLengthAndReplacements)
{
    double minimum = numeric_limits<double>::max();
    pair<double,double> currentMinPair;

    for (auto edgeLengthAndReplacement : edgeLengthAndReplacements)
    {
        double extraDistance = edgeLengthAndReplacement.second - edgeLengthAndReplacement.first;

        if (extraDistance < minimum)
        {
            minimum = extraDistance;

            currentMinPair = edgeLengthAndReplacement;
        }
    }

    return currentMinPair;
}

double GetPerimeterWithOriginInsideConvexHull(const vector<Point> &convexHull, const vector<Point> &points)
{
    vector< pair<double,double> > edgeLengthAndReplacements =
        GetEdgeLengthAndReplacements(convexHull, points);

    pair<double,double> minimum = GetMinimumDistance(edgeLengthAndReplacements);

    double convexHullPerimeter = GetPerimeter(convexHull);

    return convexHullPerimeter - minimum.first + minimum.second;
}

double GetPerimeter(const vector<Point> &convexHull, const vector<Point> &points)
{
    if (IsOriginInConvexHull(convexHull) || IsOriginOnEdgeOfConvexHull(convexHull))
    {
        return GetPerimeter(convexHull);
    }

    return GetPerimeterWithOriginInsideConvexHull(convexHull, points);
}

double GetLengthOfSilk(vector<Point> points)
{
    // Insert in the starting pole (0,0)
    points.push_back(Point(0,0));

    points = RemoveDuplicates(points);

    vector<Point> convexHull = GetConvexHull(points);

    const double extraSilkToTie = 2;
    double perimeter = GetPerimeter(convexHull, points);

    return perimeter + extraSilkToTie;
}

int main()
{
    int T, N;

    cin >> T;

    for (int i=0; i<T; ++i)
    {
        cin >> N;

        vector<Point> points(N);

        for (int j=0; j<N; ++j)
        {
            cin >> points[j].x >> points[j].y;
        }

        cout << fixed << setprecision(2) << GetLengthOfSilk(points) << endl;

        if (i < T-1)
        {
            cout << endl;
        }
    }

    return 0;
}

