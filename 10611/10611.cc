/*

*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

string GetLess(int height, const set<int> &femaleChimpHeights)
{
    auto it = femaleChimpHeights.lower_bound(height);

    if (it == femaleChimpHeights.begin())
    {
        return "X";
    }

    return to_string(*prev(it));
}

string GetMore(int height, const set<int> &femaleChimpHeights)
{
    auto it = femaleChimpHeights.upper_bound(height);

    if (it == femaleChimpHeights.end())
    {
        return "X";
    }

    return to_string(*it);

}

pair<string,string> GetLessAndMore(int height, const set<int> &femaleChimpHeights)
{
    string less = GetLess(height, femaleChimpHeights);
    string more = GetMore(height, femaleChimpHeights);

    return make_pair(less, more);
}

int main()
{
    int N, Q;

    int temp;

    cin >> N;

    set<int> femaleChimpHeights;

    for (int i=0; i<N; ++i)
    {
        cin >> temp;

        femaleChimpHeights.insert(temp);
    }

    cin >> Q;

    vector<int> luchuHeights(Q);

    for (int i=0; i<Q; ++i)
    {
        cin >> luchuHeights[i];
    }

    for (int height : luchuHeights)
    {
        pair<string,string> lessAndMore = GetLessAndMore(height, femaleChimpHeights);

        cout << lessAndMore.first << ' ' << lessAndMore.second << endl;
    }

    return 0;
}

