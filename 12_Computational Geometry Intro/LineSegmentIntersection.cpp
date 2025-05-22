#include <iostream>
#include <math.h>
#include <iomanip>
#include <cmath>

using namespace std;

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

pair<double, double> pointOfIntersection(pair<double, double> one_start, pair<double, double> one_end, pair<double, double> two_start, pair<double, double> two_end) {
    double A1 = one_end.second - one_start.second;
    double B1 = one_start.first - one_end.first;
    double C1 = A1 * one_start.first + B1 * one_start.second;

    double A2 = two_end.second - two_start.second;
    double B2 = two_start.first - two_end.first;
    double C2 = A2 * two_start.first + B2 * two_start.second;
    
    double D = A1 * B2 - B1 * A2;

    double intersectX = double(B2 * C1 - B1 * C2) / double(D);
    double intersectY = double(A1 * C2 - A2 * C1) / double(D);
    
    return pair<double, double>(intersectX, intersectY);
}

void printPoints(pair<double, double> p1, pair<double, double> p2) {
    //If one of the segments given as input was just a single point, this catches that edge case
    if (p1.first == p2.first && p1.second == p2.second) cout << p1.first << " " << p1.second << endl;

    //If p1 has higher precedence
    else if (p1.first < p2.first || p1.first == p2.first && p1.second < p2.second) 
        cout << p1.first << " " << p1.second << " " << p2.first << " " << p2.second << endl;
    
    //If p2 has higher precedence
    else 
        cout << p2.first << " " << p2.second << " " << p1.first << " " << p1.second << endl;
}

double fixNegZero(double in) {
    return abs(in) < 0.01 ? 0.00 : in;
}

int main() {
    int cases;

    cin >> cases;

    cout << fixed << setprecision(2);

    for (int i = 0; i < cases; i++) {
        int x1, y1, x2, y2, x3, y3, x4, y4;

        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        pair<int, int> p1 = pair<int, int>(x1, y1);
        pair<int, int> p2 = pair<int, int>(x2, y2);
        pair<int, int> p3 = pair<int, int>(x3, y3);
        pair<int, int> p4 = pair<int, int>(x4, y4);

        int d1 = direction(p3, p4, p1);
        int d2 = direction(p3, p4, p2);
        int d3 = direction(p1, p2, p3);
        int d4 = direction(p1, p2, p4);
    
        //Segments intersect and aren't collinear
        if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) //p1-2 straddles p3-4
         && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)) //p3-4 straddles p1-2
            ) {
            pair<double, double> intersectionPoint = pointOfIntersection(p1, p2, p3, p4);

            cout << fixNegZero(intersectionPoint.first) << " " << fixNegZero(intersectionPoint.second) << endl;
        }
    
        //Segments are collinear
        else if (d1 == 0 && d2 == 0 && d3 == 0 && d4 == 0) {
            pair<double, double> dP1 = pair<double, double>(p1.first, p1.second);
            pair<double, double> dP2 = pair<double, double>(p2.first, p2.second);
            pair<double, double> dP3 = pair<double, double>(p3.first, p3.second);
            pair<double, double> dP4 = pair<double, double>(p4.first, p4.second);

            if (onSegment(p3, p4, p2) && onSegment(p3, p4, p1)) {
                printPoints(dP1, dP2);
            }
            else if (onSegment(p1, p2, p3) && onSegment(p3, p4, p1)) {
                printPoints(dP1, dP3);
            }
            else if (onSegment(p1, p2, p4) && onSegment(p3, p4, p1)) {
                printPoints(dP1, dP4);
            }
            else if (onSegment(p1, p2, p3) && onSegment(p3, p4, p2)) {
                printPoints(dP2, dP3);
            }
            else if (onSegment(p1, p2, p4) && onSegment(p3, p4, p2)) {
                printPoints(dP2, dP4);
            }
            else if (onSegment(p1, p2, p3) && onSegment(p1, p2, p4)) {
                printPoints(dP3, dP4);
            }

            //In case the segments are collinear but don't actually intersect
            else {
                cout << "none" << endl;
            }
        }

        else if (onSegment(p1, p2, p3) && direction(p1, p2, p3) == 0) {
            cout << double(p3.first) << " " << double(p3.second) << endl;
        }
        else if (onSegment(p1, p2, p4) && direction(p1, p2, p4) == 0) {
            cout << double(p4.first) << " " << double(p4.second) << endl;
        }
        else if (onSegment(p3, p4, p1) && direction(p3, p4, p1) == 0) {
            cout << double(p1.first) << " " << double(p1.second) << endl;
        }
        else if (onSegment(p3, p4, p2) && direction(p3, p4, p2) == 0) {
            cout << double(p2.first) << " " << double(p2.second) << endl;
        }

        else {
            cout << "none" << endl;
        }
    }
}

