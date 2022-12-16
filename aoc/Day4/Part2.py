with open('input.txt') as file:
    data = [i for i in file.read().strip().split("\n")]

pairs = 0
for entry in data:
    first, second = entry.split(",")
    first = [int(i) for i in first.split("-")]
    second = [int(i) for i in second.split("-")]

    if not (first[1] < second[0] or first [0] > second[1]):
        pairs += 1


    # if first[0] in range(second[0], second[1]+1) or first[1] in range(second[0], second[1]+1):
        # pairs += 1
    # elif second[0] in range(first[0], first[1]+1) or second[1] in range(first[0], first[1]+1):
        # pairs += 1


print("Answer to part 2:", pairs)
