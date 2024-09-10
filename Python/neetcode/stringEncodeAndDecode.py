# An algorithm to encode and decode a list of strings to and from a single string
class Solution:
    def encode(self, strs: List[str]) -> str:
        estr = ""
        for s in strs:
            estr = str(len(s)) + '$' + s
        return estr


    def decode(self, s: str) -> List[str]:
        dStr = []
        i = 0

        while i < len(s):
            j = i
            while s[i] != '$':
                j += 1 # Holds the end of the string
            length = int(s[i:j])
            dStr.append(s[j + 1: i + length])
            i = j #Now they are in the same page
        return dStr
