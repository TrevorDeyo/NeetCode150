#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TestCase {
    vector<int> nums;      // Input numbers
    int target;            // Target Sum
    vector<int> expected;  // Expected output
};

vector<int> twoSum(const vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return { static_cast<int>(i), static_cast<int>(j) };
            }
        }
    }
    return {}; // Return empty vector if no solution found
}

int main()
{
    vector<TestCase> testCases = {
        {{3, 4, 5, 6}, 7, {0, 1}},
        {{4, 5, 6}, 10, {0, 2}},
        {{5, 5}, 10, {0, 1}}
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        const TestCase& testCase = testCases[i];
        vector<int> result = twoSum(testCase.nums, testCase.target);

        // Print test case details
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Input: nums = [";
        for (size_t j = 0; j < testCase.nums.size(); ++j) {
            cout << testCase.nums[j] << (j + 1 < testCase.nums.size() ? ", " : "");
        }
        cout << "], target = " << testCase.target << "\n";

        cout << "Expected: [";
        for (size_t j = 0; j < testCase.expected.size(); ++j) {
            cout << testCase.expected[j] << (j + 1 < testCase.expected.size() ? ", " : "");
        }
        cout << "]\n";

        cout << "Output: [";
        for (size_t j = 0; j < result.size(); ++j) {
            cout << result[j] << (j + 1 < result.size() ? ", " : "");
        }
        cout << "]\n";

        if (result == testCase.expected) {
            cout << "Test Passed!\n\n";
        }
        else {
            cout << "Test Failed!\n\n";
        }
    }

    return 0;
}
