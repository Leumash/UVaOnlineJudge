/*
10018 Reverse and Add

The “reverse and add” method is simple: choose a number, reverse its digits and add it to the original.  If the sum is not a palindrome (which means, it is not the same number from left to right and right to left), repeat this procedure.

For example:

            195 Initial number
            591
            —–
            786
            687
            —–
            1473
            3741
            —–
            5214
            4125
            —–
            9339 Resulting palindrome

In this particular case the palindrome ‘9339’ appeared after the 4th addition. This method leads to palindromes in a few step for almost all of the long longegers. But there are long longeresting exceptions. 196 is the first number for which no palindrome has been found. It is not proven though, that there is no such a palindrome.

You must write a program that give the resulting palindrome and the number of iterations (additions) to compute the palindrome.

You might assume that all tests data on this problem:

• will have an answer ,
• will be computable with less than 1000 iterations (additions),
• will yield a palindrome that is not greater than 4,294,967,295.

Input

The first line will have a number N (0 < N ≤ 100) with the number of test cases, the next N lines will have a number P to compute its palindrome.

Output

For each of the N tests you will have to write a line with the following data : minimumnumberofiterations(additions)togettothepalindrome and theresultingpalindromeitself separated by one space.

Sample Input

3
195
265
750

Sample Output

4 9339
5 45254
3 6666

*/

#include <iostream>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;

bool IsPalindrome(long long n)
{
    string number = to_string(n);

    for (long long i=0; i<number.size()/2; ++i)
    {
        if (number[i] != number[number.size() - 1 - i])
        {
            return false;
        }
    }

    return true;
}

long long GetReverse(long long n)
{
    string number = to_string(n);

    reverse(number.begin(), number.end());

    return stoi(number);
}

pair<long long,long long> GetIterationsAndPalindrome(long long n)
{
    long long iterations = 0;

    do
    {
        long long reverse = GetReverse(n);

        n += reverse;
        ++iterations;
    } while (!IsPalindrome(n));

    return make_pair(iterations, n);
}

int main()
{
    long long N;
    long long P;

    cin >> N;

    for (long long i=0; i<N; ++i)
    {
        cin >> P;

        pair<long long,long long> iterationsAndPalindrome = GetIterationsAndPalindrome(P);

        cout << iterationsAndPalindrome.first << ' ' << iterationsAndPalindrome.second << endl;
    }

    return 0;
}

