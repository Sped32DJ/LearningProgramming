print("What is today's weather?")
print()
print("snowy | cold | rainy | warm | hot | very hot")
print()

tomorrow = input("Insert weather: ")

if tomorrow == "warm":
    print("Pants and shirt day")
elif tomorrow == "hot":
    print("Sunscreen and don't forget water")
elif tomorrow == "very hot":
    print("Sunscreen and go get some ice cream")
elif tomorrow == "snowy":
    print("Thicc jacket, and don't forget the boots")
elif tomorrow == "cold":
    print("Get a jacket, pants, and you good")
else:
    print( '"' +  tomorrow + '"'+ " is not an answer -_-")
