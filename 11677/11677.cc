#include <iostream>

#define MINUTES_IN_DAY 24*60

using namespace std;

struct Time
{
    int hour;
    int minute;
    bool operator<(const Time &other)
    {
        return hour == other.hour ? minute < other.minute : hour < other.hour;
    }
};

int GetMinuteDifference(Time time1, Time time2)
{
    bool swapped = false;

    if (time2 < time1)
    {
        Time temp = time1;

        time1 = time2;
        time2 = temp;

        swapped = true;
    }

    int answer = 0;

    if (time2.minute < time1.minute)
    {
        time2.minute += 60;
        time2.hour -= 1;
    }

    answer += 60 * (time2.hour - time1.hour);
    answer += time2.minute - time1.minute;
    
    if (swapped)
    {
        return MINUTES_IN_DAY - answer;
    }

    return answer;
}

int main()
{
    int H1, M1, H2, M2;
    Time time1, time2;

    while (true)
    {
        cin >> time1.hour >> time1.minute >> time2.hour >> time2.minute;

        if (time1.hour == 0 && time1.minute == 0 && time2.hour == 0 && time2.minute == 0)
        {
            break;
        }

        cout << GetMinuteDifference(time1, time2) << endl;
    }

    return 0;
}

