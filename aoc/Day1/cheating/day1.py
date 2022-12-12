# Git data
with open('input.in') as file:
    data = [i for i in file.read().strip().split("\n")]

# print(data)

# Traversing strings into data
# Traversing def:
max  = 0
max1 = 0
max2 = 0

count = 0
for item in data:
    if item == '':
        count = 0
    else:
        num = int(item)
        count += num

    if count > max:
        max = count
    elif count > max1:
        max1 = count
    elif count > max2:
        max2 = count

print("P1 Ans: ", max, max1, max2)
print("sum: ",max +max1+max2)
