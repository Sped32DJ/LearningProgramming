def hashed(key):
    return hash(key) % 11

def second_hash(key, i):
    return (hashed(key) + i * (5 - key % 5)) % 11

key = input("Key: ")

print("Hash: ", hashed(key))

# for i in range(5):
    # result = second_hash(key, i)
    # print(f"Iteration {i+1}: {result}")

