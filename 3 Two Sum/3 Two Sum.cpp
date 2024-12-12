#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

struct TestCase {
    vector<int> nums;      // Input numbers
    int target;            // Target Sum
    vector<int> expected;  // expected output
};

vector<int> twoSum(vector<int>& nums, int target);

int main()
{
    vector<TestCase> TestCases = {
        {{3,4,5,6}, 7, {0,1}},
        {{4,5,6}, 10, {0,2}},
        {{5,5}, 10, {0,1}}
    }

    for (case: TestCases) {
        ;
    }
    
    return 0;
}

// PLACEHOLDER
vector<int> twoSum(vector<int>& nums, int target) {
    return {};
}