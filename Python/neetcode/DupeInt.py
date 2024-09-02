class Solution:
    def hasDuplicate(self, nums: List[int]) -> bool:
        #declare hashtable
        hashset = set()

        # Iterates through nums[]
        for n in nums:
            # If n is found in the hashset, True (dupe was found)
            if n in hashset:
                return True
            # no dupe was found -> keep adding to hash
            hashset.add(n)
        #Iterates through entire array, no dupes found
        return False
