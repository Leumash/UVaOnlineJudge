/*

A problem that is simple to solve in one dimension is often much more difficult to solve in more than one dimension. Consider satisfying a boolean expression in conjunctive normal form in which each conjunct consists of exactly 3 disjuncts. This problem (3-SAT) is NP-complete. The problem 2-SAT is solved quite efficiently, however. In contrast, some problems belong to the same complexity class regardless of the dimensionality of the problem.

Given a 2-dimensional array of positive and negative integers, find the sub-rectangle with the largest sum. The sum of a rectangle is the sum of all the elements in that rectangle. In this problem the subrectangle with the largest sum is referred to as the maximal sub-rectangle.
A sub-rectangle is any contiguous sub-array of size 1 x 1 or greater located within the whole array. As an example, the maximal sub-rectangle of the array:

 0 -2 -7  0
 9  2 -6  2
-4  1 -4  1
-1  8  0 -2

is in the lower-left-hand corner:

 9  2
-4  1
-1  8

and has the sum of 15.

Input

The input consists of an N x N array of integers.

The input begins with a single positive integer N on a line by itself indicating the size of the square two dimensional array. This is followed by N^2 integers separated by white-space (newlines and spaces). These N^2 integers make up the array in row-major order (i.e., all numbers on the first row, left-to-right, then all numbers on the second row, left-to-right, etc.). N may be as large as 100. The numbers in the array will be in the range [-127, 127].

Output

The output is the sum of the maximal sub-rectangle.

Sample Input

4
0 -2 -7 0 9 2 -6 2
-4 1 -4 1 -1
8 0 -2

Sample Output

15

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> getPrefixSumMatrix(const vector<vector<int>> &matrix, int N) {
    vector<vector<int>> prefixSumMatrix(N, vector<int>(N,0));

    // Set initial column value
    for (int i=0; i<N; ++i) {
        prefixSumMatrix[i][0] = matrix[i][0];
    }

    // Fill out prefix sum array
    for (int row=0; row<N; ++row) {
        for (int col=1; col<N; ++col) {
            prefixSumMatrix[row][col] = prefixSumMatrix[row][col-1] + matrix[row][col];
        }
    }

    return prefixSumMatrix;
}

vector<int> getSumsInRange(const vector<vector<int>> &prefixSumMatrix, int a, int b, int N) {
    vector<int> sumOfRange(N);

    for (int i=0; i<N; ++i) {
        int toSubtract = a == 0 ? 0 : prefixSumMatrix[i][a-1];
        sumOfRange[i] = prefixSumMatrix[i][b] - toSubtract;
    }
    return sumOfRange;
}

int getMaximumSumOfSubArray(const vector<int> &arr) {
    int currentMax = 0;
    int totalMax = 0;
    for (int i=0; i<arr.size(); ++i) {
        currentMax = currentMax + arr[i];
        if (currentMax < 0) {
            currentMax = 0;
        }
        totalMax = max(totalMax, currentMax);
    }
    return totalMax;
}

int getSumOfMaximalSubRectangle(const vector<vector<int>> &matrix, int N) {
    vector<vector<int>> prefixSumMatrix = getPrefixSumMatrix(matrix, N);

    int maximum = 0;
    for (int a=0; a<N; ++a) {
        for (int b = a; b<N; ++b) {
            vector<int> arr = getSumsInRange(prefixSumMatrix, a, b, N);
            int currentMax = getMaximumSumOfSubArray(arr);
            maximum = max(maximum, currentMax);
        }
    }
    return maximum;
}

int main() {
    int N;
    cin >> N;
    vector<vector<int>> matrix(N, vector<int>(N,0));

    for (unsigned int row=0; row<matrix.size(); ++row) {
        for (unsigned int col=0; col<matrix[row].size(); ++col) {
             cin >> matrix[row][col];
        }
    }

    cout << getSumOfMaximalSubRectangle(matrix, N) << endl;
}

