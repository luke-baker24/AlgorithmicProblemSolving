import sys
from functools import total_ordering

def input():
    return sys.stdin.readline().strip()
        
def dist(a, b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2

def cross_product(x1, y1, x2, y2, x3, y3, x4, y4):
    ax = x2-x1
    ay = y2-y1
    bx = x4-x3
    by = y4-y3
    return ax*by-ay*bx

def JARVIS_MARCH_LEFT(Q, hull_pts):

    j = 0

    while hull_pts[j] == 0:
        j+=1

    p0 = Q[j]
    curr = p0
    count = 1

    while True:
        next = Q[j]
        next_pts = 0
        for i in range(j, len(Q)):
            if hull_pts[i] == 0:
                continue
            a = cross_product(curr[0], curr[1], next[0], next[1], curr[0], curr[1], Q[i][0], Q[i][1])
            if a<0 or (a==0 and (curr == next or dist(curr, next) > dist(curr, Q[i]))):
                next = Q[i]
                next_pts = i

        if next == p0:
            hull_pts[j] = 0
            return count
        
        hull_pts[next_pts] = 0
        curr = next
        count += 1


# sys.stdin = open("maxPointsValid.in", "r")
segments = int(input())
A = []
for i in range(segments):
    x1,y1 = map(int, input().split())
    A.append((x1,y1))


A = list(set(A))
A.sort()

buildings_left = len(A)
valid = [1] * buildings_left
loop_count = 0

while buildings_left > 2:
    buildings_left -= JARVIS_MARCH_LEFT(A, valid)
    loop_count += 1


if buildings_left == 2 and loop_count > 0:
    print("valid", loop_count)
else:
    print("invalid")

    