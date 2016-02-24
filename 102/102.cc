/*
 102 Ecological Bin Packing 

 Background

 Bin packing, or the placement of objects of certain weights into different bins subject to certain constraints, is an historically interesting problem. Some bin packing problems are NP-complete but are amenable to dynamic programming solutions or to approximately optimal heuristic solutions.

 In this problem you will be solving a bin packing problem that deals with recycling glass.

 The Problem

 Recycling glass requires that the glass be separated by color into one of three categories: brown glass, green glass, and clear glass. In this problem you will be given three recycling bins, each containing a specified number of brown, green and clear bottles. In order to be recycled, the bottles will need to be moved so that each bin contains bottles of only one color.

 The problem is to minimize the number of bottles that are moved. You may assume that the only problem is to minimize the number of movements between boxes.

 For the purposes of this problem, each bin has infinite capacity and the only constraint is moving the bottles so that each bin contains bottles of a single color. The total number of bottles will never exceed 2^31.

 The Input

 The input consists of a series of lines with each line containing 9 integers. The first three integers on a line represent the number of brown, green, and clear bottles (respectively) in bin number 1, the second three represent the number of brown, green and clear bottles (respectively) in bin number 2, and the last three integers represent the number of brown, green, and clear bottles (respectively) in bin number 3. For example, the line 10 15 20 30 12 8 15 8 31

 indicates that there are 20 clear bottles in bin 1, 12 green bottles in bin 2, and 15 brown bottles in bin 3.

 Integers on a line will be separated by one or more spaces. Your program should process all lines in the input file.

 The Output

 For each line of input there will be one line of output indicating what color bottles go in what bin to minimize the number of bottle movements. You should also print the minimum number of bottle movements.

 The output should consist of a string of the three upper case characters 'G', 'B', 'C' (representing the colors green, brown, and clear) representing the color associated with each bin.

 The first character of the string represents the color associated with the first bin, the second character of the string represents the color associated with the second bin, and the third character represents the color associated with the third bin.

 The integer indicating the minimum number of bottle movements should follow the string.

 If more than one order of brown, green, and clear bins yields the minimum number of movements then the alphabetically first string representing a minimal configuration should be printed.

 Sample Input

 1 2 3 4 5 6 7 8 9
 5 10 5 20 10 5 10 20 10

 Sample Output

 BCG 30
 CBG 50
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool MyComp(pair<string,long long> a, pair<string, long long> b)
{
    return a.second < b.second;
}

void BruteForce(long long brown1, long long brown2, long long brown3,
                long long green1, long long green2, long long green3,
                long long clear1, long long clear2, long long clear3)
{
    vector< pair<string, long long> > costs;

    // BCG
    pair<string, long long> BCG = make_pair("BCG", brown2 + brown3 + clear1 + clear3 + green1 + green2);

    // BGC
    pair<string, long long> BGC = make_pair("BGC", brown2 + brown3 + clear1 + clear2 + green1 + green3);

    // CBG
    pair<string, long long> CBG = make_pair("CBG", brown1 + brown3 + clear2 + clear3 + green1 + green2);

    // CGB
    pair<string, long long> CGB = make_pair("CGB", brown1 + brown2 + clear2 + clear3 + green1 + green3);

    // GBC
    pair<string, long long> GBC = make_pair("GBC", brown1 + brown3 + clear1 + clear2 + green2 + green3);

    // GCB
    pair<string, long long> GCB = make_pair("GCB", brown1 + brown2 + clear1 + clear3 + green2 + green3);

    costs.push_back(BCG);
    costs.push_back(BGC);
    costs.push_back(CBG);
    costs.push_back(CGB);
    costs.push_back(GBC);
    costs.push_back(GCB);

    sort(costs.begin(), costs.end(), MyComp);

    cout << costs[0].first << ' ' << costs[0].second;
}

int main()
{
    long long brown1, brown2, brown3;
    long long green1, green2, green3;
    long long clear1, clear2, clear3;

    string line;

    while (getline(cin, line))
    {
        stringstream ss;

        ss << line;

        ss >> brown1 >> green1 >> clear1;
        ss >> brown2 >> green2 >> clear2;
        ss >> brown3 >> green3 >> clear3;

        BruteForce(brown1, brown2, brown3, green1, green2, green3, clear1, clear2, clear3);

        cout << endl;
    }

    return 0;
}

