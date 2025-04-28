class Data:
    def __init__(self, key="", value=0):
        self.key = key
        self.value = value

    def set(self):
        self.key = input("Key: ")
        self.value = int(input("Value: "))


class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * size  # Stores actual data
        self.chain = [-1] * size    # Stores indices for chaining

    def hash(self, key):
        """Create a hash from the key and value."""
        return (hash(key) + hash(str(key))) % self.size

    def insert(self, d):
        i = self.hash(d.key)  # Hash based on key (not value)
        if self.find(d, True) != -1:
            print("Duplicate!")
            return
        
        if self.table[i] is None:
            self.table[i] = d
            print(f"Inserted at {i}")
        else:
            # Handle collision using open addressing (linear probing)
            j = i
            while self.chain[j] != -1:
                j = self.chain[j]
            k = (j + 1) % self.size
            while self.table[k] is not None:
                if k == i:
                    print("Full!")
                    return
                k = (k + 1) % self.size
            self.table[k] = d
            self.chain[j] = k
            print(f"Inserted at {k}, chained from {j}")

    def find(self, d, silent=False):
        """Find a key-value pair."""
        i = self.hash(d.key)
        while i != -1:
            if self.table[i] and self.table[i].value == d.value and self.table[i].key == d.key:
                if not silent:
                    print(f"Found at {i}")
                return i
            i = self.chain[i]
        if not silent:
            print("Not found")
        return -1

    def delete(self, d):
        """Delete a key-value pair."""
        i = self.find(d, True)
        if i == -1:
            print("Not found")
            return
        self.table[i] = None
        # Re-link the subsequent items
        j = self.chain[i]
        self.chain[i] = -1
        while j != -1 and self.table[j] is not None:
            next_j = self.chain[j]
            k = self.hash(self.table[j].key)
            self.table[k] = self.table[j]
            self.chain[j] = -1
            j = next_j
        print(f"Deleted from {i}")

    def show(self):
        """Show hash table contents."""
        for i in range(self.size):
            if self.table[i]:
                print(f"{i}: {self.table[i].key}, {self.table[i].value} -> {self.chain[i]}")
            else:
                print(f"{i}: Empty -> {self.chain[i]}")


# Main Loop
ht = HashTable()
while True:
    print("\n1.Insert 2.Search 3.Delete 4.Display 5.Exit")
    ch = input("Choice: ")
    if ch == '1':
        d = Data()
        d.set()
        ht.insert(d)
    elif ch == '2':
        d = Data()
        d.set()
        ht.find(d)
    elif ch == '3':
        d = Data()
        d.set()
        ht.delete(d)
    elif ch == '4':
        ht.show()
    elif ch == '5':
        break
    else:
        print("Invalid")
