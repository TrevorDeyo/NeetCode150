#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

struct TestCase {
    vector<int> nums;      // Input numbers
    int target;            // Target Sum
    vector<int> expected;  // expected output
    string explaination;   // Explanation on why.
};

vector<int> twoSum(vector<int>& nums, int target);

int main()
{
    vector<TestCase> TestCases = {
        {{3,4,5,6}, 7, {0,1}, "Explanation: nums[0] + nums[1] == 7, so we return [0, 1]." },
        {{4,5,6}, 7, {0,1}
    { {3,4,5,6}, 7 }
    { {3,4,5,6}, 7 }

    for (index )
    twoSum();

    cout << "Hello World!\n";
    return 0;
}

// PLACEHOLDER
vector<int> twoSum(vector<int>& nums, int target) {
    return {};
}