/*

https://uva.onlinejudge.org/external/101/10126.pdf

10126 Zipf’s Law

Harvard linguistics professor George Kingsley Zipf (1902-1950) observed that the frequency of the k-th most common word in a text is roughly proportional to 1/k. He justified his observations in a book titled Human behavior and the principle of least effort published in 1949. While Zipf’s rationale has largely been discredited, the principle still holds, and others have afforded it a more sound mathematical basis.

You are to find all the words occurring n times in an English text. A word is a sequence of letters. Words are separated by non-letters.  Capitalization should be ignored. A word can be of any length that an English word can be.

Input

Input consists of several test cases. The first line of each case contains a single positive integer n.  Several lines of text follow which will contain no more than 10000 words. The text for each case is terminated by a single line containing EndOfText. EndOfText does not appear elsewhere in the input and is not considered a word.

Output

For each test case, output the words which occur n times in the input text, one word per line, lower case, in alphabetical order. If there are no such words in input, output the following line:

There is no such word.

    Leave a blank line between cases.

Sample Input

2

In practice, the difference between theory and practice is always
greater than the difference between theory and practice in theory.
    - Anonymous
Man will occasionally stumble over the truth, but most of the
time he will pick himself up and continue on.
        - W. S. L. Churchill
EndOfText

Sample Output

between
difference
in
will

*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<string> ToLowerCase(vector<string> words)
{
    for (auto &word : words)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
    }

    return words;
}

vector<string> RemovePrependingAndTrailingPunctuation(vector<string> words)
{
    string letters = "abcdefghijklmnopqrstuvwxyz";
    for (auto &word : words)
    {
        int first = word.find_first_of(letters);
        int last = word.find_last_of(letters);

        word = word.substr(first, (last-first+1));
    }

    return words;
}

bool DoesContainLetter(const string &word)
{
    for (auto &letter : word)
    {
        if (isalpha(letter))
        {
            return true;
        }
    }

    return false;
}

vector<string> RemoveNonWords(const vector<string> &words)
{
    vector<string> toReturn;

    for (auto &word : words)
    {
        if (DoesContainLetter(word))
        {
            toReturn.push_back(word);
        }
    }

    return toReturn;
}

vector<string> RemovePunctuationAndAddWords(vector<string> words)
{
    vector<string> toReturn;

    for (auto &word : words)
    {
        for (auto &letter : word)
        {
            if (!isalpha(letter))
            {
                letter = ' ';
            }
        }

        stringstream ss;

        ss << word;

        string tempWord;

        while (ss >> tempWord)
        {
            toReturn.push_back(tempWord);
        }
    }

    return toReturn;
}

vector<string> GetNthFrequencyWords(int N, vector<string> input)
{
    input = RemoveNonWords(input);
    input = ToLowerCase(input);
    input = RemovePrependingAndTrailingPunctuation(input);
    input = RemovePunctuationAndAddWords(input);

    unordered_map<string,int> wordToFrequency;

    for (auto &word : input)
    {
        if (wordToFrequency.count(word) == 0)
        {
            wordToFrequency[word] = 0;
        }

        ++wordToFrequency[word];
    }

    vector<string> toReturn;

    for (auto &keyValue : wordToFrequency)
    {
        if (keyValue.second == N)
        {
            toReturn.push_back(keyValue.first);
        }
    }

    return toReturn;
}

int main()
{
    int N;
    string word;

    cin >> N;

    while (true)
    {
        vector<string> input;

        while (cin >> word)
        {
            if (word == "EndOfText")
            {
                break;
            }

            input.push_back(word);
        }

        vector<string> nthFrequencyWords = GetNthFrequencyWords(N, input);

        if (nthFrequencyWords.size() == 0)
        {
            cout << "There is no such word." << endl;
        }
        else
        {
            sort(nthFrequencyWords.begin(), nthFrequencyWords.end());

            for (auto &s : nthFrequencyWords)
            {
                cout << s << endl;
            }
        }

        // TODO may have to not output this

        if (cin >> N)
        {
            cout << endl;
        }
        else
        {
            break;
        }
    }

    return 0;
}

