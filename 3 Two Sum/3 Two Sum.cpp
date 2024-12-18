#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

struct TestCase {
    vector<int> nums;
    int target;
};

// Brute Force Algorithm
vector<int> twoSumBruteForce(const vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return { static_cast<int>(i), static_cast<int>(j) };
            }
        }
    }
    return {};
}

// Sorting-Based Algorithm
vector<int> twoSumSorting(const vector<int>& nums, int target) {
    vector<pair<int, int>> indexedNums;
    for (size_t i = 0; i < nums.size(); ++i) {
        indexedNums.emplace_back(nums[i], i);
    }
    sort(indexedNums.begin(), indexedNums.end());
    size_t left = 0, right = nums.size() - 1;

    while (left < right) {
        int sum = indexedNums[left].first + indexedNums[right].first;
        if (sum == target) {
            return { indexedNums[left].second, indexedNums[right].second };
        }
        else if (sum < target) {
            ++left;
        }
        else {
            --right;
        }
    }
    return {};
}

// Hashmap Two-Pass Algorithm
vector<int> twoSumHashmapTwoPass(const vector<int>& nums, int target) {
    unordered_map<int, int> indices;
    for (size_t i = 0; i < nums.size(); ++i) {
        indices[nums[i]] = i;
    }
    for (size_t i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (indices.count(complement) && indices[complement] != static_cast<int>(i)) {
            return { static_cast<int>(i), indices[complement] };
        }
    }
    return {};
}

// Hashmap One-Pass Algorithm
vector<int> twoSumHashmapOnePass(const vector<int>& nums, int target) {
    unordered_map<int, int> indices;
    for (size_t i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (indices.count(complement)) {
            return { indices[complement], static_cast<int>(i) };
        }
        indices[nums[i]] = i;
    }
    return {};
}

// Generate Random Test Cases
vector<TestCase> generateRandomTestCases(int numCases, int arraySize, int valueRange) {
    vector<TestCase> testCases;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, valueRange);

    for (int i = 0; i < numCases; ++i) {
        vector<int> nums(arraySize);
        for (int& num : nums) {
            num = dist(gen);
        }
        int target = dist(gen);
        testCases.push_back({ nums, target });
    }
    return testCases;
}

// Measure Execution Time
void measureAndPrintExecutionTime(const string& algoName, const vector<TestCase>& testCases,
    vector<int>(*algo)(const vector<int>&, int)) {
    auto start = high_resolution_clock::now();

    for (const TestCase& testCase : testCases) {
        algo(testCase.nums, testCase.target);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << algoName << " took " << duration << " ms to complete.\n";
}

int main() {
    int numTestCases = 100000;
    int arraySize = 100;
    int valueRange = 100;

    vector<TestCase> testCases = generateRandomTestCases(numTestCases, arraySize, valueRange);

    cout << "Testing algorithms with " << numTestCases << " random test cases...\n";

    measureAndPrintExecutionTime("Brute Force", testCases, twoSumBruteForce);
    measureAndPrintExecutionTime("Sorting-Based", testCases, twoSumSorting);
    measureAndPrintExecutionTime("Hashmap Two-Pass", testCases, twoSumHashmapTwoPass);
    measureAndPrintExecutionTime("Hashmap One-Pass", testCases, twoSumHashmapOnePass);

    return 0;
}
