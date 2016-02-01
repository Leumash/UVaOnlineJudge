#include <iostream>
#include <vector>

using namespace std;

bool FoundN(vector< vector<char> > &matrix, string word, int row, int col)
{
    if (row - (((int)word.size())-1) < 0)
    {
        return false;
    }

    for (int i=0; i<word.size(); ++i)
    {
        if (matrix[row - i][col] != word[i])
        {
            return false;
        }
    }

    return true;
}

bool FoundNE(vector< vector<char> > &matrix, string word, int row, int col)
{
    if (row - (((int)word.size())-1) < 0)
    {
        return false;
    }

    if (col + (((int)word.size())-1) >= matrix[0].size())
    {
        return false;
    }

    for (int i=0; i<word.size(); ++i)
    {
        if (matrix[row - i][col + i] != word[i])
        {
            return false;
        }
    }

    return true;
}

bool FoundE(vector< vector<char> > &matrix, string word, int row, int col)
{
    if (col + (((int)word.size())-1) >= matrix[0].size())
    {
        return false;
    }

    for (int i=0; i<word.size(); ++i)
    {
        if (matrix[row][col + i] != word[i])
        {
            return false;
        }
    }

    return true;
}

bool FoundSE(vector< vector<char> > &matrix, string word, int row, int col)
{
    if (row + (((int)word.size())-1) >= matrix.size())
    {
        return false;
    }

    if (col + (((int)word.size())-1) >= matrix[0].size())
    {
        return false;
    }

    for (int i=0; i<word.size(); ++i)
    {
        if (matrix[row + i][col + i] != word[i])
        {
            return false;
        }
    }

    return true;
}

bool FoundS(vector< vector<char> > &matrix, string word, int row, int col)
{
    if (row + (((int)word.size())-1) >= matrix.size())
    {
        return false;
    }

    for (int i=0; i<word.size(); ++i)
    {
        if (matrix[row + i][col] != word[i])
        {
            return false;
        }
    }

    return true;
}

bool FoundSW(vector< vector<char> > &matrix, string word, int row, int col)
{
    if (col - (((int)word.size())-1) < 0)
    {
        return false;
    }

    if (row + (((int)word.size())-1) >= matrix.size())
    {
        return false;
    }

    for (int i=0; i<word.size(); ++i)
    {
        if (matrix[row + i][col - i] != word[i])
        {
            return false;
        }
    }

    return true;
}

bool FoundW(vector< vector<char> > &matrix, string word, int row, int col)
{
    if (col - (((int)word.size())-1) < 0)
    {
        return false;
    }

    for (int i=0; i<word.size(); ++i)
    {
        if (matrix[row][col - i] != word[i])
        {
            return false;
        }
    }

    return true;
}

bool FoundNW(vector< vector<char> > &matrix, string word, int row, int col)
{
    if (row - (((int)word.size())-1) < 0)
    {
        return false;
    }

    if (col - (((int)word.size())-1) < 0)
    {
        return false;
    }

    for (int i=0; i<word.size(); ++i)
    {
        if (matrix[row - i][col - i] != word[i])
        {
            return false;
        }
    }

    return true;
}

bool FoundWord(vector< vector<char> > &matrix, string word, int row, int col)
{
    // Check 8 Directions

    return FoundN(matrix, word, row, col) || FoundNE(matrix, word, row, col)
            || FoundE(matrix, word, row, col) || FoundSE(matrix, word, row, col)
            || FoundS(matrix, word, row, col) || FoundSW(matrix, word, row, col)
            || FoundW(matrix, word, row, col) || FoundNW(matrix, word, row, col);
}

void DoIt(vector< vector<char> > &matrix, vector<string> words)
{
    for (string word : words)
    {
        for (int row=0; row<matrix.size(); ++row)
        {
            for (int col=0; col<matrix[0].size(); ++col)
            {
                if (matrix[row][col] == word[0])
                {
                    if (FoundWord(matrix, word, row, col))
                    {
                        cout << row + 1 << ' ' << col + 1 << endl;
                        goto BREAK;
                    }
                }
            }
        }

        BREAK:;
    }
}

int main()
{
    int T;
    int row, col;

    cin >> T;

    for (int i=0; i<T; ++i)
    {
        cin >> row >> col;

        vector< vector<char> > matrix;

        for (int r=0; r<row; ++r)
        {
            matrix.push_back(vector<char>());

            for (int c=0; c<col; ++c)
            {
                char temp;

                cin >> temp;

                matrix[r].push_back(tolower(temp));
            }
        }

        int numberOfWords;

        cin >> numberOfWords;

        string temp;
        vector<string> words;

        for (int n=0; n<numberOfWords; ++n)
        {
            cin >> temp;

            for (auto &c : temp)
            {
                c = tolower(c);
            }

            words.push_back(temp);
        }

        DoIt(matrix, words);

        if (i + 1 < T)
        {
            cout << endl;
        }
    }

    return 0;
}
