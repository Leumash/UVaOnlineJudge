/*

10082 WERTYU

A common typing error is to place the hands on the keyboard one row to the right of the correct position. So ‘Q’ is typed as ‘W’ and ‘J’ is typed as ‘K’ and so on. You are to decode a message typed in this manner.

Input

Input consists of several lines of text. Each line may contain digits, spaces, upper case letters (except Q, A, Z), or punctuation shown above [except back-quote (`)]. Keys labelled with words [Tab, BackSp, Control, etc.] are not represented in the input.

Output

You are to replace each letter or punction symbol by the one immediately to its left on the ‘QWERTY’ keyboard shown above. Spaces in the input should be echoed in the output.

Sample Input

O S, GOMR YPFSU/

Sample Output

I AM FINE TODAY.

*/

/*
Possible input:
Capital Letters
- = [ ] \ ; ' , . /
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char,char> GetMap()
{
    unordered_map<char,char> toReturn;

    toReturn['1'] = '`';
    toReturn['2'] = '1';
    toReturn['3'] = '2';
    toReturn['4'] = '3';
    toReturn['5'] = '4';
    toReturn['6'] = '5';
    toReturn['7'] = '6';
    toReturn['8'] = '7';
    toReturn['9'] = '8';
    toReturn['0'] = '9';
    toReturn['-'] = '0';
    toReturn['='] = '-';
    toReturn['W'] = 'Q';
    toReturn['E'] = 'W';
    toReturn['R'] = 'E';
    toReturn['T'] = 'R';
    toReturn['Y'] = 'T';
    toReturn['U'] = 'Y';
    toReturn['I'] = 'U';
    toReturn['O'] = 'I';
    toReturn['P'] = 'O';
    toReturn['['] = 'P';
    toReturn[']'] = '[';
    toReturn['\\'] = ']';
    toReturn['S'] = 'A';
    toReturn['D'] = 'S';
    toReturn['F'] = 'D';
    toReturn['G'] = 'F';
    toReturn['H'] = 'G';
    toReturn['J'] = 'H';
    toReturn['K'] = 'J';
    toReturn['L'] = 'K';
    toReturn[';'] = 'L';
    toReturn['\''] = ';';
    toReturn['X'] = 'Z';
    toReturn['C'] = 'X';
    toReturn['V'] = 'C';
    toReturn['B'] = 'V';
    toReturn['N'] = 'B';
    toReturn['M'] = 'N';
    toReturn[','] = 'M';
    toReturn['.'] = ',';
    toReturn['/'] = '.';
    toReturn[' '] = ' ';

    return toReturn;
}

char GetCharacterToLeft(char c)
{
    static unordered_map<char,char> keyToKeyOnLeft = GetMap();

    return keyToKeyOnLeft[c];
}

int main()
{
    string line;

    while (getline(cin, line))
    {
        for (char c : line)
        {
            cout << GetCharacterToLeft(c);
        }

        cout << endl;
    }

    return 0;
}

