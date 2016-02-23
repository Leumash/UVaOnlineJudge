/*

10100 Longest Match

A newly opened detective agency is struggling with their limited intelligence to find out a secret information passing technique among its detectives. Since they are new in this profession, they know well that their messages will easily be trapped and hence modified by other groups. They want to guess the intensions of other groups by checking the changed sections of messages. First they have to get the length of longest match. You are going to help them.

Input

The input file may contain multiple test cases. Each case will contain two successive lines of string.  Blank lines and non-letter printable punctuation characters may appear. Each Line of string will be no longer than 1000 characters. Length of each word will be less than 20 characters.

Output

For each case of input, you have to output a line starting with the case number right justified in a field width of two, followed by the longest match as shown in the sample output. In case of at least one blank line for each input output ‘Blank!’. Consider the non-letter punctuation characters as white-spaces.

Sample Input

This is a test.
test
Hello!

The document provides late-breaking information
late breaking.

Sample Output

 1. Length of longest match: 1
 2. Blank!
 3. Length of longest match: 2

*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

string Trim(string line)
{
    int pos = line.find_last_not_of(" ");

    return line.substr(0, pos+1);
}

string Sanitize(string line)
{
    for (char &c : line)
    {
        if (!isalpha(c) && !isdigit(c))
        {
            c = ' ';
        }
    }

    return Trim(line);
}

vector<string> GetSequence(const string &line)
{
    vector<string> sequence;

    stringstream ss;
    string temp;

    ss << line;

    while (ss >> temp)
    {
        sequence.push_back(temp);
    }

    return sequence;
}

int GetLengthOfLongestCommonSubsequence(const vector<string> &sequence1, const vector<string> &sequence2)
{
    int matrix[sequence1.size()+1][sequence2.size()+1] = {0};

    // Fill Top row
    for (int i=0; i<sequence2.size()+1; ++i)
    {
        matrix[0][i] = 0;
    }

    // Fill Left column
    for (int i=0; i<sequence1.size()+1; ++i)
    {
        matrix[i][0] = 0;
    }

    // Fill matrix
    for (int row=1; row<sequence1.size()+1; ++row)
    {
        for (int col=1; col<sequence2.size()+1; ++col)
        {
            int toAdd = 0;

            if (sequence1[row-1] == sequence2[col-1])
            {
                toAdd = 1;
            }

            matrix[row][col] = max({matrix[row-1][col-1] + toAdd, matrix[row-1][col], matrix[row][col-1]});
        }
    }

    return matrix[sequence1.size()][sequence2.size()];
}

string GetLengthOfLongestMatch(string &input, string &toMatch)
{
    if (input == "" || toMatch == "")
    {
        return "Blank!";
    }

    input = Sanitize(input);
    toMatch = Sanitize(toMatch);

    vector<string> sequence1 = GetSequence(input);
    vector<string> sequence2 = GetSequence(toMatch);

    if (input.size() == 0 || toMatch.size() == 0)
    {
        return "Length of longest match: 0";
    }

    return "Length of longest match: " + to_string(GetLengthOfLongestCommonSubsequence(sequence1, sequence2));
}

int main()
{
    string input;
    string toMatch;

    int testCase = 1;

    while (getline(cin, input))
    {
        getline(cin, toMatch);

        cout << setw(2) << right << testCase << ". ";
        cout << GetLengthOfLongestMatch(input, toMatch);
        cout << endl;

        ++testCase;
    }

    return 0;
}

