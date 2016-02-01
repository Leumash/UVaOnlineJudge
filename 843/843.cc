/*

843 Crypt Kicker

A common but insecure method of encrypting text is to permute the letters of the alphabet. That is, in the text, each letter of the alphabet is consistently replaced by some other letter. So as to ensure that the encryption is reversible, no two letters are replaced by the same letter.

Your task is to decrypt several encoded lines of text, assuming that each line uses a different set of replacements, and that all words in the decrypted text are from a dictionary of known words.

Input

The input consists of a line containing an integer n, followed by n lower case words, one per line, in alphabetical order. These n words comprise the dictionary of words which may appear in the decrypted text. Following the dictionary are several lines of input. Each line is encrypted as described above.

There are no more than 1000 words in the dictionary. No word exceeds 16 letters. The encrypted
lines contain only lower case letters and spaces and do not exceed 80 characters in length.

Output

Decrypt each line and print it to standard output. If there is more than one solution, any will do. If there is no solution, replace every letter of the alphabet by an asterisk.

Sample Input

6
and
dick
jane
puff
spot
yertle
bjvg xsb hxsn xsb qymm xsb rqat xsb pnetfn
xxxx yyy zzzz www yyyy aaa bbbb ccc dddddd

Sample Output

dick and jane and puff and spot and yertle
**** *** **** *** **** *** **** *** ******

*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <sstream>

using namespace std;

vector<string> GetWords(string line)
{
    vector<string> toReturn;
    stringstream ss;

    ss << line;

    string temp;

    while ( ss >> temp)
    {
        toReturn.push_back(temp);
    }

    return toReturn;
}

vector< pair<char,char> > GetToAdd(map<char,char> m, string original, string encrypted)
{
    vector< pair<char,char> > toReturn;

    toReturn.push_back(make_pair(' ',' '));

    for (int i=0; i < original.size(); ++i)
    {
        char b = original[i];
        char a = encrypted[i];

        if (m.count(a) == 0)
        {
            m[a] = b;
            toReturn.push_back(make_pair(a,b));
        }
        else
        {
            if (m[a] != b)
            {
                return vector< pair<char,char> >();
            }
        }
    }

    return toReturn;
}

void AddToMap(vector< pair<char,char> > toAdd, map<char,char> &m)
{
    for (int i=0; i<toAdd.size(); ++i)
    {
        m[toAdd[i].first] = toAdd[i].second;
    }
}

void RemoveFromMap(vector< pair<char,char> > toRemove, map<char,char> &m)
{
    for (int i=0; i<toRemove.size(); ++i)
    {
        m.erase(toRemove[i].first);
    }
}

bool GetSolution(map<char,char> &m, vector<string> dictionary, vector<string> encrypted, int index)
{
    if (index > encrypted.size() - 1)
    {
        return true;
    }

    string current = encrypted[index];

    for (int i=0; i<dictionary.size(); ++i)
    {
        if (current.size() != dictionary[i].size())
        {
            continue;
        }

        vector< pair<char,char> > toAdd = GetToAdd(m, dictionary[i], current);

        if (toAdd.size() > 0)
        {
            AddToMap(toAdd, m);

            if (GetSolution(m, dictionary, encrypted, index + 1))
            {
                return true;
            }

            RemoveFromMap(toAdd, m);
        }
    }

    return false;
}

map<char,char> Process(vector<string> dictionary, vector<string> encrypted)
{
    map<char,char> toReturn;

    if (GetSolution(toReturn, dictionary, encrypted, 0))
    {
        return toReturn;
    }
    else
    {
        for (int i=0; i<26; ++i)
        {
            toReturn[i + 'a'] = '*';
        }
    }

    return toReturn;
}

string GetDecryption(string line, map<char,char> decryption)
{
    string toReturn;

    decryption[' '] = ' ';

    for (int i=0; i<line.size(); ++i)
    {
        toReturn += decryption[line[i]];
    }

    return toReturn;
}

int main()
{
    int n;

    cin >> n;

    string temp;
    vector<string> dictionary;

    for (int i=0; i<n; ++i)
    {
        cin >> temp;

        dictionary.push_back(temp);
    }

    string line;

    getline(cin, line);

    while(getline(cin, line))
    {
        vector<string> encrypted = GetWords(line);

        map<char,char> decryption = Process(dictionary, encrypted);

        cout << GetDecryption(line, decryption) << endl;
    }

    return 0;
}

