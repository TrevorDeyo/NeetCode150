# %% [markdown]
# Duplicate Integer
# Given an integer array nums, return true if any value appears more than once in the array, otherwise return false.
# 
# Example 1:
# Input: nums = [1, 2, 3, 3]
# Output: true
# 
# Example 2:
# Input: nums = [1, 2, 3, 4]
# Output: false
# 

# %%
from typing import List, Dict

class Solution:
    def hasDuplicate(self, nums: List[int]) -> bool:
        seen = set()
        
        for n in nums:
            if n in seen:
                return True
            seen.add(n)
        return False

# %% [markdown]
# Test Case Generator and Verifier.

# %%
class Testing:
    def testGenerator(self):
        # Test Params
        numberofbatches = 10
        testPerBatch = 10
        maxValue = 100
        rateofvalueincrease = 10

        


