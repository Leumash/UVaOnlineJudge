#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> squashWeightsToIndices(const vector<int> &nums) {
    unordered_map<int,int> numberToIndex;
    vector<int> sorted(nums);
    sort(sorted.begin(), sorted.end());
    for (int i=0; i<sorted.size(); ++i) {
        numberToIndex[sorted[i]] = i;
    }
    vector<int> squashed;
    for (int num : nums) {
        squashed.push_back(numberToIndex[num]);
    }
    return squashed;
}

vector<int> getMaxLengthFromIndexIncreasing(const vector<int> &indicies) {
    int n = indicies.size();
    vector<vector<int>> matrix = vector<vector<int>>(n, vector<int>(n, 0));
    for (int row = n - 1; row >= 0; --row) {
        for (int col = n - 1; col >= 0; --col) {
            int toAdd = indicies[row] == col ? 1 : 0;
            int down = (row != n - 1) ? matrix[row + 1][col] : 0;
            int right = (col != n - 1) ? matrix[row][col + 1] : 0;
            matrix[row][col] = max(down, right) + toAdd;
        }
    }
    vector<int> toReturn;
    for (int i=0; i<n; ++i) {
        toReturn.push_back(matrix[i][indicies[i]]);
    }
    return toReturn;
}

vector<int> getMaxLengthFromIndexDecreasing(const vector<int> &indicies) {
    int n = indicies.size();
    vector<vector<int>> matrix = vector<vector<int>>(n, vector<int>(n, 0));
    for (int row = n - 1; row >= 0; --row) {
        for (int col = 0; col < n; ++col) {
            int toAdd = indicies[row] == col ? 1 : 0;
            int down = (row != n - 1) ? matrix[row + 1][col] : 0;
            int left = (col != 0) ? matrix[row][col - 1] : 0;
            matrix[row][col] = max(down, left) + toAdd;
        }
    }
    vector<int> toReturn;
    for (int i=0; i<n; ++i) {
        toReturn.push_back(matrix[i][indicies[i]]);
    }
    return toReturn;

}

int findLongestTrain(const vector<int> &increasing, const vector<int> &decreasing) {
    int maxLength = 0;
    for (int i=0; i<increasing.size(); ++i) {
        int length = increasing[i] + decreasing[i] - 1;
        maxLength = max(length, maxLength);
    }
    return maxLength;
    return 0;
}

int getLongestTrain(const vector<int> &weights) {
    vector<int> indicies = squashWeightsToIndices(weights);
    vector<int> maxLengthFromIndexIncreasing = getMaxLengthFromIndexIncreasing(indicies);
    vector<int> maxLengthFromIndexDecreasing = getMaxLengthFromIndexDecreasing(indicies);
    return findLongestTrain(maxLengthFromIndexIncreasing, maxLengthFromIndexDecreasing);
}

int main() {
    int T;
    int n;
    cin >> T;
    for (int i=0; i<T; ++i) {
        vector<int> weights;
        cin >> n;
        for (int j=0; j<n; ++j) {
            int temp;
            cin >> temp;
            weights.push_back(temp);
        }
        cout << getLongestTrain(weights) << endl;
    }
}

