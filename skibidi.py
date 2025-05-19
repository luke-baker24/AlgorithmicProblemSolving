import random

skibidi = open('skibidi.txt', 'w')

skibidi.write("10\n")

for i in range(0, 250):
    skibidi.write(str(random.randint(-10000, 10000)) + " " + str(random.randint(-10000, 10000)) + "\n")

for i in range(0, 250):
    skibidi.write(str(random.randint(-1000, 1000)) + " " + str(random.randint(-1000, 1000)) + "\n")

for i in range(0, 250):
    skibidi.write(str(random.randint(-100, 100)) + " " + str(random.randint(-100, 100)) + "\n")

skibidi.write("0 0\n")
skibidi.write("10 10\n")

skibidi.close()