class DoubleProbingHashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def hash1(self, key):
        return key % self.size

    def hash2(self, key):
        return (5 - key % 5) % self.size

    def insert(self, key, value):
        index = self.hash1(key)

        i = 0
        while True:
            new_index = (index + i * self.hash2(key)) % self.size

            if self.table[new_index] is None:
                # Found an empty slot, insert the key-value pair
                self.table[new_index] = (key, value)
                break

            i += 1

    def display_table(self):
        print("Hash Table:")
        for i, entry in enumerate(self.table):
            if entry is not None:
                print(f"Bucket {i}: {entry}")
            else:
                print(f"Bucket {i} is empty")

# Example usage:
valsTable = DoubleProbingHashTable(11)

# User input for key-value pairs
num_values = int(input("Enter the number of key-value pairs to insert: "))

for _ in range(num_values):
    key = int(input("Enter key: "))
    value = int(input("Enter value: "))
    valsTable.insert(key, value)

# Display the hash table
valsTable.display_table()

