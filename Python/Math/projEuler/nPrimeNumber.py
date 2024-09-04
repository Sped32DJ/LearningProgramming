# TODO  Make this recursive
# NOTE  Broken rn
# I am quite sure this is a brute force method...
#   But I don't believe there's a formula for prime numbers
def nPrimeNumber(n):
    currNum = 0
    nthPrime = 0 # iterates until nthPrime
    while nthPrime <= n:
        if isPrime(currNum):
            nthPrime += 1;
        currNum += 1
    # Exits the loop once i <= n
    print(currNum)
    return currNum

def isPrime(n):
    if n % 2 != 0 or n % 3 != 0:
        return True
    return False

n = 100001
nthPrime = nPrimeNumber(n)
print("\nnthPrime")
print(n)
