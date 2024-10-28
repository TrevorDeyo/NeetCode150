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
from typing import List
import random

# Test Case Generator
def generator():
    # Test Params
    numberofBatches = 5
    startingTestsPerBatch = 10
    rateofTestsPerBatchIncrease = 2
    maxIntValue = 99
    
    previousBatchSize = 0
    testBatches = []
    for batchNum in range(numberofBatches):
        if batchNum == 0:
            batchSize = startingTestsPerBatch
        else:
            batchSize = previousBatchSize * rateofTestsPerBatchIncrease
        
        # build the batch
        testBatch = []
        for _ in range(batchSize):
            testBatch.append(random.randint(0, int(maxIntValue))) 
        testBatches.append(testBatch)            

        previousBatchSize = batchSize
        return testBatches        

# %%
# Hashset Solution
def hasDuplicateHashset(nums: List[int]) -> bool:
    seen = set()
    
    for n in nums:
        if n in seen:
            return True
        seen.add(n)
    return False

# %%
def main():
    


