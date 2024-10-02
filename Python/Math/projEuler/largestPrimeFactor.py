def largest_prime_factor(n):
    # Initialize largestPrime
    largest = -1

    # Removes factors of 2
    while n % 2 == 0:
        largest = 2
        n //= 2

    # Removes factors of odd numbers 3 -> n
    factor = 3
    while factor * factor <= n:
        while n % factor == 0:
            largest = factor
            n //= factor
        factor += 2

    # n is a prime number greater than 2
    if n > 2:
        largest = n
    return largest

number = 600851475143
print(largest_prime_factor(number))
