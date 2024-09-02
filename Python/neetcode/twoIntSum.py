class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:

        # Why did I add the i , _ ?
        # Without it, the index iterator i is a tuple
        for i, _ in enumerate(nums):
            for j in range(i + 1, len(nums)):
                if nums[i] + nums[j] == target:
                    return [i,j]
        return []
