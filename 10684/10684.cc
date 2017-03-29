#include <iostream>
#include <vector>

using namespace std;

int kadaneAlgorithm(const vector<int> &nums) {
    int localMax = 0;
    int globalMax = 0;
    for (int num : nums) {
        localMax += num;
        if (localMax <= 0) {
            localMax = 0;
        }
        if (localMax > globalMax) {
            globalMax = localMax;
        }
    }
    return globalMax;
}

void printOutput(int maximumSubarraySum) {
    if (maximumSubarraySum == 0) {
        cout << "Losing streak." << endl;
    } else {
        cout << "The maximum winning streak is " << maximumSubarraySum << "." << endl;
    }
}

int main() {
    int num;
    int N;
    cin >> N;
    do {
        vector<int> nums;
        for (int i=0; i<N; ++i) {
            cin >> num;
            nums.push_back(num);
        }
        int maximumSubarraySum = kadaneAlgorithm(nums);
        printOutput(maximumSubarraySum);
        cin >> N;
    } while (N > 0);
}

