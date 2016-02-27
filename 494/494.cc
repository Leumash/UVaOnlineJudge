#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool IsWord(const string &word)
{
    for (const char &letter : word)
    {
        if (isalpha(letter))
        {
            return true;
        }
    }

    return false;
}

string ConvertNonLettersToSpaces(string line)
{
    for (char &letter : line)
    {
        if (!isalpha(letter))
        {
            letter = ' ';
        }
    }

    return line;
}

int GetWordCount(string line)
{
    int count = 0;
    stringstream ss;
    string word;

    line = ConvertNonLettersToSpaces(line);

    ss << line;

    while (ss >> word)
    {
        if (IsWord(word))
        {
            ++count;
        }
    }

    return count;
}

int main()
{
    string line;

    while (getline(cin, line))
    {
        cout << GetWordCount(line) << endl;
    }

    return 0;
}

