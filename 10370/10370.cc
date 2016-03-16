/*

10370 Above Average

It is said that 90% of frosh expect to be above average in their class. You are to provide a reality check.

Input

The first line of standard input contains an integer C, the number of test cases. C data sets follow. Each data set begins with an integer, N, the number of people in the class (1 ≤ N ≤ 1000). N integers follow, separated by spaces or newlines, each giving the final grade (an integer between 0 and 100) of a student in the class.

Output

For each case you are to output a line giving the percentage of students whose grade is above average, rounded to 3 decimal places.

Sample Input

5
5 50 50 70 80 100
7 100 95 90 80 70 60 50
3 70 90 80
3 70 90 81
9 100 99 98 97 96 95 94 93 91

Sample Output

40.000%
57.143%
33.333%
66.667%
55.556%

*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

double GetAverage(const vector<int> &finalGrades)
{
    int total = 0;

    for (int grade : finalGrades)
    {
        total += grade;
    }

    return total * 1.0 / finalGrades.size();
}

int GetStudentsAboveAverage(const vector<int> &finalGrades, double average)
{
    int count = 0;

    for (int grade : finalGrades)
    {
        if (grade > average)
        {
            ++count;
        }
    }

    return count;
}

double GetPercentageOfStudentsWhoseGradeIsAboveAverage(const vector<int> &finalGrades)
{
    double average = GetAverage(finalGrades);

    int studentsAboveAverage = GetStudentsAboveAverage(finalGrades, average);

    return studentsAboveAverage * 100.0 / finalGrades.size();
}

int main()
{
    int C;
    int N;

    cin >> C;

    for (int i=0; i<C; ++i)
    {
        cin >> N;

        vector<int> finalGrades(N);

        for (int j=0; j<N; ++j)
        {
            cin >> finalGrades[j];
        }

        cout << fixed << setprecision(3) << GetPercentageOfStudentsWhoseGradeIsAboveAverage(finalGrades) << "%" << endl;
    }

    return 0;
}

