/*

 Triangle Wave 

 In this problem you are to generate a triangular wave form according to a specified pair of Amplitude and Frequency.

 Input and Output

 The input begins with a single positive integer on a line by itself indicating the number of the cases following, each of them as described below. This line is followed by a blank line, and there is also a blank line between two consecutive inputs.

 Each input set will contain two integers, each on a separate line. The first integer is the Amplitude; the second integer is the Frequency.

 For each test case, the output must follow the description below. The outputs of two consecutive cases will be separated by a blank line.

 For the output of your program, you will be printing wave forms each separated by a blank line. The total number of wave forms equals the Frequency, and the horizontal ``height'' of each wave equals the Amplitude. The Amplitude will never be greater than nine.

 The waveform itself should be filled with integers on each line which indicate the ``height'' of that line.

 NOTE: There is a blank line after each separate waveform, excluding the last one.

 Sample Input

 1

 3
 2
 Sample Output

 1
 22
 333
 22
 1

 1
 22
 333
 22
 1

*/

#include <iostream>

using namespace std;

int main()
{
    int N;
    int amplitude;
    int frequency;

    cin >> N;

    for (int i=0; i<N; ++i)
    {
        cin >> amplitude >> frequency;

        if (frequency == 0)
        {
            continue;
        }

        for (int j=0; j<frequency; ++j)
        {
            for (int k=1; k<=amplitude; ++k)
            {
                for (int l=0; l<k; ++l)
                {
                    cout << k;
                }

                cout << endl;
            }

            for (int k=amplitude-1; k>=1; --k)
            {
                for (int l=0; l<k; ++l)
                {
                    cout << k;
                }

                cout << endl;
            }

            if (j < frequency - 1 )
            {
                cout << endl;
            }
        }

        if (i < N - 1)
        {
            cout << endl;
        }
    }

    return 0;
}

