def sumSqaureDiff(n):

    # Find the sum sqares
    sumSquares = 0
    print("Entered function")
    # TODO  Some real iterative steps
    for i in n:
        sumSquares += i**2
    print(sumSquares) #debugging

    squareSum = 0
    for i in n:
        squareSum += i
    squareSum **= 2
    print(squareSum) # debugging

    # TODO  Make function return an int
    print(sumSquares - squareSum)
#    return sumSquares - squareSum

number = 10
print("The sumSquare difference of ")
print(number)
print(" is ")
sumSqaureDiff(number)
