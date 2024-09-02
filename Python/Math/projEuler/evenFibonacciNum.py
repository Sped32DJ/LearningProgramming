a, b = 1,2
sumEven = 0

while a <= 4000000:
    if a % 2 == 0:
        sumEven += a
    a, b = b, a + b # Iterator
print(sumEven)
