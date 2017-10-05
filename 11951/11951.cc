#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> makePrefixSum(const vector<vector<int>> &prefixSumMatrix, int colA, int colB, int N) {
    vector<int> rowSums = vector<int>(N);
    for (int i=0; i<N; ++i) {
        int toSubtract = colA == 0 ? 0 : prefixSumMatrix[i][colA - 1];
        rowSums[i] = prefixSumMatrix[i][colB] - toSubtract;
    }
    for (int i=1; i<N; ++i) {
        rowSums[i] += rowSums[i-1];
    }
    return rowSums;
}

pair<int,int> getLargestAreaWithLowestCost(const vector<vector<int>> &matrix, int N, int M, int K) {
    vector<vector<int>> prefixSumMatrix = vector<vector<int>>(N, vector<int>(M));
    for (int i=0; i<N; ++i) {
        prefixSumMatrix[i][0] = matrix[i][0];
    }
    for (int i=0; i<N; ++i) {
        for (int j=1; j<M; ++j) {
            prefixSumMatrix[i][j] = prefixSumMatrix[i][j-1] + matrix[i][j];
        }
    }
    int maxArea = 0;
    int minCost = 0;
    for (int colB=0; colB<M; ++colB) {
        for (int colA=0; colA <= colB; ++colA) {
            vector<int> prefixSum = makePrefixSum(prefixSumMatrix, colA, colB, N);
            for (int rowB=0; rowB<N; ++rowB) {
                for (int rowA=0; rowA <= rowB; ++rowA) {
                    int toSubtract = rowA == 0 ? 0 : prefixSum[rowA - 1];
                    int cost = prefixSum[rowB] - toSubtract;
                    int area = (rowB - rowA + 1) * (colB - colA + 1);
                    if (cost <= K) {
                        if (area > maxArea) {
                            maxArea = area;
                            minCost = cost;
                        } else if (area == maxArea) {
                            minCost = min(minCost, cost);
                        }
                    }
                }
            }
        }
    }
    return make_pair(maxArea, minCost);
}

int main() {
    int T, N, M, K;
    int temp;
    cin >> T;
    for (int i=0; i<T; ++i) {
        cin >> N >> M >> K;
        vector<vector<int>> matrix;
        for (int j=0; j<N; ++j) {
            vector<int> row;
            for (int k=0; k<M; ++k) {
                cin >> temp;
                row.push_back(temp);
            }
            matrix.push_back(row);
        }
        pair<int,int> sizeAndCost = getLargestAreaWithLowestCost(matrix, N, M, K);
        cout << "Case #" << i + 1 << ": " << sizeAndCost.first << ' ' << sizeAndCost.second << endl;
    }
}

