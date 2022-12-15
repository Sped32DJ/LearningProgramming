#!/bin/python3

# Git data
with open("input.txt") as file:
    round = [i for i in file.read().strip().split("\n")]

# print(round)

desired_outcomes = {
        "A X":3, "A Y":4, "A Z":8,
        "B X":1, "B Y":5, "B Z":9,
        "C X":2, "C Y":6, "C Z":7
        }

total_points_p2 = 0
for round in round:
    total_points_p2 += desired_outcomes[round]

# Ans
print("Part 2 ans: ", total_points_p2)
