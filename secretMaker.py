fo = open("foo.txt", "w")

fo.write("10000\n")

for i in range(0, 2500):
    fo.write(str(i) + " 0" + "\n")

for i in range(0, 2500):
    fo.write("0 " + str(i) + "\n")

for i in range(0, 2500):
    fo.write(str(i) + " 2500" + "\n")

for i in range(0, 2500):
    fo.write("2500 " + str(i) + "\n")

fo.close()