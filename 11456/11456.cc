#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> getLongestIncreasingSubsequences(const vector<int> &nums) {
    vector<int> longestIncreasingSubsequences(nums.size(), 1);
    for (int right = nums.size() - 1; right >= 0; --right) {
        for (int left = right - 1; left >= 0; --left) {
            if (nums[left] < nums[right]) {
                longestIncreasingSubsequences[left] = max(longestIncreasingSubsequences[left], longestIncreasingSubsequences[right] + 1);
            }
        }
    }
    return longestIncreasingSubsequences;
}

vector<int> getLongestDecreasingSubsequences(const vector<int> &nums) {
    vector<int> longestDecreasingSubsequences(nums.size(), 1);
    for (int right = nums.size() - 1; right >= 0; --right) {
        for (int left = right - 1; left >= 0; --left) {
            if (nums[left] > nums[right]) {
                longestDecreasingSubsequences[left] = max(longestDecreasingSubsequences[left], longestDecreasingSubsequences[right] + 1);
            }
        }
    }
    return longestDecreasingSubsequences;
}

int findLongestTrain(const vector<int> &increasing, const vector<int> &decreasing) {
    int longest = 0;
    for (int i=0; i<increasing.size(); ++i) {
        longest = max(longest, increasing[i] + decreasing[i] - 1);
    }
    return longest;
}

int getLongestTrain(const vector<int> &weights) {
    vector<int> longestIncreasingSubsequences = getLongestIncreasingSubsequences(weights);
    vector<int> longestDecreasingSubsequences = getLongestDecreasingSubsequences(weights);
    return findLongestTrain(longestIncreasingSubsequences, longestDecreasingSubsequences);
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

