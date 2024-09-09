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

