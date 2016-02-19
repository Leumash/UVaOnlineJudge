/*

158 Calendar

Most of us have a calendar on which we scribble details of important events in our lives--visits to the dentist, the Regent 24 hour book sale, Programming Contests and so on. However there are also the fixed dates: partner's birthdays, wedding anniversaries and the like; and we also need to keep track of these. Typically we need to be reminded of when these important dates are approaching--the more important the event, the further in advance we wish to have our memories jogged.

Write a program that will provide such a service. The input will specify the year for which the calendar is relevant (in the range 1901 to 1999). Bear in mind that, within the range specified, all years that are divisible by 4 are leap years and hence have an extra day (February 29th) added. The output will specify ''today's'' date, a list of forthcoming events and an indication of their relative importance.

Input

The first line of input will contain an integer representing the year (in the range 1901 to 1999). This will be followed by a series of lines representing anniversaries or days for which the service is requested.

An anniversary line will consist of the letter 'A'; three integer numbers (D, M, P) representing the date, the month and the importance of the event; and a string describing the event, all separated by one or more spaces. P will be a number between 1 and 7 (both inclusive) and represents the number of days before the event that the reminder service should start. The string describing the event will always be present and will start at the first non-blank character after the priority.

A date line will consist of the letter 'D' and the date and month as above.

All anniversary lines will precede any date lines. No line will be longer than 255 characters in total. The file will be terminated by a line consisting of a single #.

Output

Output will consist of a series of blocks of lines, one for each date line in the input. Each block will consist of the requested date followed by the list of events for that day and as many following days as necessary.

The output should specify the date of the event (D and M), right justified in fields of width 3, and the relative importance of the event. Events that happen today should be flagged as shown below, events that happen tomorrow should have P stars, events that happen the day after tomorrow should have P-1 stars, and so on. If several events are scheduled for the same day, order them by relative importance (number of stars).

If there is still a conflict, order them by their appearance in the input stream. Follow the format used in the example below. Leave 1 blank line between blocks.

Sample input

1993
A 23 12 5 Partner's birthday
A 25 12 7    Christmas
A 20 12 1 Unspecified Anniversary
D 20 12
#

Sample output

Today is: 20 12
 20 12 *TODAY* Unspecified Anniversary
 23 12 ***     Partner's birthday
 25 12 ***     Christmas

*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Date
{
    int day;
    int month;
};

struct Anniversary : Date
{
    int priority;
    string event;
};

string trim(string &s)
{
    int first= s.find_first_not_of(' ');
    int last = s.find_last_not_of(' ');
    return s.substr(first, (last - first + 1));
}

bool ComparePriority(Anniversary a, Anniversary b)
{
    return a.priority > b.priority;
}

int GetIndex(Date &date, bool isLeapYear)
{
    int index = 0;

    int month = date.month;
    int day = date.day;

    int arr[12];

    arr[0] = 0;
    arr[1] = 31;
    arr[2] = 59;
    arr[3] = 90;
    arr[4] = 120;
    arr[5] = 151;
    arr[6] = 181;
    arr[7] = 212;
    arr[8] = 243;
    arr[9] = 273;
    arr[10] = 304;
    arr[11] = 334;

    index += arr[month - 1];

    if (month > 2 && isLeapYear)
    {
        ++index;
    }

    index += (day - 1);

    return index;
}

void Process(vector<Anniversary> &anniversaries, vector<Date> &dates, int year)
{
    bool isLeapYear = year % 4 == 0;
    int size = isLeapYear ? 366 : 365;

    vector< vector<Anniversary> > data(size);

    for (auto a : anniversaries)
    {
        int index = GetIndex(a, isLeapYear);

        for (int i=0; i <=a.priority; ++i)
        {
            Anniversary temp = a;
            temp.priority = a.priority - i + 1;

            int dataIndex;

            if (index - i >= 0)
            {
                dataIndex = index - i;
            }
            else
            {
                int negativeIndex = abs(index - i);

                dataIndex = 365 - negativeIndex;

                if (isLeapYear)
                {
                    ++dataIndex;
                }
            }

            data[dataIndex].push_back(temp);
        }
    }

    for (int k=0; k<dates.size(); ++k)
    {
        auto d = dates[k];
        cout << "Today is:" << right << setw(3) << d.day << setw(3) << d.month << endl;

        int index = GetIndex(d, isLeapYear);

        auto temp = data[index];
        for (auto &a : temp)
        {
            int aIndex = GetIndex(a, isLeapYear);

            if (aIndex == index)
            {
                a.priority = 8;
            }
        }

        stable_sort(temp.begin(), temp.end(), ComparePriority);

        for (auto a : temp)
        {
            cout << right << setw(3) << a.day << setw(3) << a.month;

            if (a.priority == 8)
            {
                cout << " *TODAY* ";
            }
            else
            {
                stringstream ss;

                for (int i=0; i<a.priority; ++i)
                {
                    ss << '*';
                }

                string stars;

                ss >> stars;

                cout << ' ' << left << setw(7) << stars << ' ';
            }

            cout << a.event << endl;
        }

        if (k < dates.size() - 1)
        {
            cout << endl;
        }
    }
}

int main()
{
    int year;

    cin >> year;

    char event;

    cin >> event;

    vector<Anniversary> anniversaries;
    vector<Date> dates;

    while (event != '#')
    {
        if (event == 'A')
        {
            string temp;

            Anniversary a;
            cin >> a.day >> a.month >> a.priority;

            getline(cin, temp);
            a.event = trim(temp);

            anniversaries.push_back(a);
        }
        else if (event == 'D')
        {
            Date d;

            cin >> d.day >> d.month;

            dates.push_back(d);
        }

        cin >> event;
    }

    Process(anniversaries, dates, year);

    return 0;
}

