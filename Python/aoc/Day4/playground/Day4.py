# Day 4

# Git data
with open("other.txt") as file:
    data = [i for i in file.read().strip().split("\n")]

# print(data)

pairs = 0
for entry in data:
    first, second = entry.split(",") # split between the comma
    # print(first, second)

    first = [int(i) for i in first.split("-")]
    second = [int(i) for i in second.split("-")]
    print(first, second)

    if first[0] <= second[0] and first[1] >= second[1]:
        pairs += 1
    elif second[0] <= first[0] and second[1] >= first[1]:
        pairs += 1

print()
print("Part 1: ", pairs)
