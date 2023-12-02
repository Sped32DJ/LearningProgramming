# Day 3: Rucksack Reorganization
from string import ascii_letters

# Git data
with open("input.txt") as file:
    data = [i for i in file.read().strip().split("\n")]

# print(data) # proof

# iterate throught the data
totalSum = 0
for rucksack in data:
    # Split data in half, len is like /bin/wc , then //2 divs then round
    half = len(rucksack)//2

    left = set(rucksack[:half])     # set() orders objects(although randomly)..
    right = set(rucksack[half:])    # ..+ remove dupes(is it a bug or feature?)

    print(rucksack,("->"), left,(" | "), right) # easier to see raw data (proof)

    for priority, char in enumerate(ascii_letters):
        if char in left and char in right:
            totalSum += priority + 1            # +1 because a = 0 (starts counting in zero lol)

print("Part 1: ", totalSum)

# Part 2
j = 3
totalSum = 0 # setting it back to 0
for i in range(0, len(data), 3):
    rucksacks = data[i:j]
    j += 3
#    print(rucksacks)

    for priority, char in enumerate(ascii_letters):
        if char in rucksacks[0] and char in rucksacks[1] and char in rucksacks[2]:
            totalSum += priority + 1


# Enumerating, displays what chars turn into numbs (proof)
# for key, char in enumerate(ascii_letters):
    # print(key, char)

#print("Part 1: ", totalSum)
print("Part 2: ", totalSum)
