#include <algorithm>
#include <functional>
#include <math.h>
#include <unordered_set>
#include <cstdio>

using namespace std;

typedef pair<int, int> pt;

int distanceSquared(pt one, pt two) {
    return (two.first - one.first) * (two.first - one.first) + (two.second - one.second) * (two.second - one.second); 
}

int min(int val1, int val2) {
    if (val1 < val2) return val1;
    else return val2;
}

pt sub(pt one, pt two) {
    return pt(one.first - two.first, one.second - two.second);
}

pt add(pt one, pt two) {
    return pt(one.first + two.first, one.second + two.second);
}

int cross(pt one, pt two) {
    return one.first * two.second - one.second * two.first;
}

// returns direction of pk relative to segment pi, pj
int direction(pt pi, pt pj, pt pk) {
	return cross(sub(pk, pi), sub(pj, pi));
}

bool ptsEqual(pt p1, pt p2) {
    return p1.first == p2.first && p1.second == p2.second;
}

void jarvisMarch(pt points[], int verts) {
    pt hull[10000];
    int hullIdx = 0;

    int idx = 0;
    do {
        hull[hullIdx++] = points[idx];
        
        int nIdx = (idx + 1) % verts;

        for (int i = 0; i < verts; i++) {
            // determine turn direction from curr->next->Q[i]
            int dir = direction(points[idx], points[nIdx], points[i]);
            
            if (dir > 0 || dir == 0 && distanceSquared(points[idx], points[i]) > distanceSquared(points[idx], points[nIdx]))
                nIdx = i;
        }

        idx = nIdx;
    } while (idx != 0);

    printf("%d\n", hullIdx);
    for (int i = 0; i < hullIdx; i++)
        printf("%d %d\n", hull[i].first, hull[i].second);
}

int main() {
    while (true) {
        int verts;

        scanf("%d", &verts);

        if (verts == 0) break;

        pt points[10000];

        for (int i = 0; i < verts; i++) {
            int x, y;
            scanf("%d %d", &x, &y);

            pt newPt = pt(x, y);

            points[i] = newPt;
        }

        sort(points, points + verts);
        pt* dedupe_end = unique(points, points + verts);
        verts = dedupe_end - points;
        
        if (verts < 3) {
            printf("%d\n", verts);

            for (int i = 0; i < verts; i++)
                printf("%d %d\n", points[i].first , points[i].second);
        }
        else {
            jarvisMarch(points, verts);
        }
    }
}