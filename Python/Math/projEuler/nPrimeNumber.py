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
    if n == 2 or n == 3: return True
    if n < 2 or n % 2 == 0: return False
    if n < 9: return True
    if n % 3 == 0: return False
    # Prime numbers > 3 are in the form 6n -+ 1


n = 100001
nthPrime = nPrimeNumber(n)
print("\nnthPrime")
print(n)
