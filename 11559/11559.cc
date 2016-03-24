/*

11559 Event Planning

As you didn’t show up to the yearly general meeting of the Nordic Club of Pin Collectors, you were unanimously elected to organize this years excursion to Pin City. You are free to choose from a number of weekends this autumn, and have to find a suitable hotel to stay at, preferably as cheap as possible.

You have some constraints: The total cost of the trip must be within budget, of course. All participants must stay at the same hotel, to avoid last years catastrophe, where some members got lost in the city, never being seen again.

Input

The input file contains several test cases, each of them as described below.

The first line of input consists of four integers: 1 ≤ N ≤ 200, the number of participants, 1 ≤ B ≤ 500000, the budget, 1 ≤ H ≤ 18, the number of hotels to consider, and 1 ≤ W ≤ 13, the number of weeks you can choose between. Then follow two lines for each of the H hotels. The first gives 1 ≤ p ≤ 10000, the price for one person staying the weekend at the hotel. The second contains W integers, 0 ≤ a ≤ 1000, giving the number of available beds for each weekend at the hotel.

Output

For each test case, write to the output the minimum cost of the stay for your group, or “stay home” if nothing can be found within the budget, on a line by itself.

Sample Input

3 1000 2 3
200
0 2 2
300
27 3 20
5 2000 2 4
300
4 3 0 4
450
7 8 0 13

Sample Output

900
stay home

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, budget, hotels, weeks;
    int beds;
    int price;

    while (cin >> N >> budget >> hotels >> weeks)
    {
        vector<int> totalCosts;

        for (int i=0; i<hotels; ++i)
        {
            cin >> price;

            for (int j=0; j<weeks; ++j)
            {
                cin >> beds;

                if (beds >= N)
                {
                    if (budget >= price * N)
                    {
                        totalCosts.push_back(price * N);
                    }
                }
            }
        }

        if (totalCosts.size() > 0)
        {
            cout << *min_element(totalCosts.begin(), totalCosts.end()) << endl;
        }
        else
        {
            cout << "stay home" << endl;
        }
    }

    return 0;
}

