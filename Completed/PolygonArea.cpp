#include <iostream>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

bool sameSigns(int x, int y) {
    return x < 0 && y < 0 || x > 0 && y > 0;
}

int distanceSquared(int x1, int y1, int x2, int y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1); 
}

int distanceSquared(pair<int, int> one, pair<int, int> two) {
    return (two.first - one.first) * (two.first - one.first) + (two.second - one.second) * (two.second - one.second); 
}

int min(int val1, int val2) {
    if (val1 < val2) return val1;
    else return val2;
}

pair<int, int> sub(pair<int, int> one, pair<int, int> two) {
    return pair<int, int>(one.first - two.first, one.second - two.second);
}

pair<int, int> add(pair<int, int> one, pair<int, int> two) {
    return pair<int, int>(one.first + two.first, one.second + two.second);
}

int cross(pair<int, int> one, pair<int, int> two) {
    return one.first * two.second - one.second * two.first;
}

// returns True if pk is on segment pi, pj
// assumes you've already determined that pi, pj, and pk are collinear
bool onSegment(pair<int, int> pi, pair<int, int> pj, pair<int, int> pk) {
	if (min(pi.first, pj.first) <= pk.first && pk.first <= max(pi.first, pj.first) && min(pi.second, pj.second) <= pk.second && pk.second <= max(pi.second, pj.second))
		return true;
    
	return false;
}

// returns direction of pk relative to segment pi, pj
int direction(pair<int, int> pi, pair<int, int> pj, pair<int, int> pk) {
	return cross(sub(pk, pi), sub(pj, pi));
}

// segments p1 -> p2 and p3 -> p4
bool segmentsIntersect(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3, pair<int, int> p4) {
	int d1 = direction(p3, p4, p1);
	int d2 = direction(p3, p4, p2);
	int d3 = direction(p1, p2, p3);
	int d4 = direction(p1, p2, p4);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;

	// handle collinear edge cases
	/*if (d1 == 0 && onSegment(p3, p4, p1))
		return true;
	if (d2 == 0 && onSegment(p3, p4, p2))
		return true;
	if (d3 == 0 && onSegment(p1, p2, p3))
		return true;
	if (d4 == 0 && onSegment(p1, p2, p4))
		return true;*/

	return false;
}

int main() {
    cout << fixed << setprecision(1);

    while (true) {
        int verts;

        cin >> verts;

        if (verts == 0) break;

        vector<pair<int, int>> polygon;

        for (int i = 0; i < verts; i++) {
            int x, y;
            cin >> x >> y;

            polygon.push_back(pair<int, int>(x, y));
        }

        int area = 0;

        for (int i = 0; i < verts; i++) {
            pair<int, int> curr = polygon.at(i);
            pair<int, int> next = polygon.at((i + 1) % verts);

            area += next.second * curr.first - curr.second * next.first;
        }

        if (area < 0) {
            cout << "CW" << " " << abs(area / 2.0) << endl;
        }
        else {
            cout << "CCW" << " " << (area / 2.0) << endl;
        }
    }
}