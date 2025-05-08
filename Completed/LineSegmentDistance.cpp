#include <iostream>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <sstream>
#include<string>

using namespace std;

double distanceSquared(double x1, double y1, double x2, double y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1); 
}

double distanceSquared(pair<double, double> one, pair<double, double> two) {
    return (two.first - one.first) * (two.first - one.first) + (two.second - one.second) * (two.second - one.second); 
}

double min(double val1, double val2) {
    if (val1 < val2) return val1;
    else return val2;
}

pair<double, double> sub(pair<double, double> one, pair<double, double> two) {
    return pair<double, double>(one.first - two.first, one.second - two.second);
}

pair<double, double> add(pair<double, double> one, pair<double, double> two) {
    return pair<double, double>(one.first + two.first, one.second + two.second);
}

pair<double, double> mult(pair<double, double> one, double value) {
    return pair<double, double>(one.first * value, one.second * value);
}

double cross(pair<double, double> one, pair<double, double> two) {
    return one.first * two.second - one.second * two.first;
}

double dot(pair<double, double> one, pair<double, double> two) {
    return one.first * two.first + one.second * two.second;
}

// returns True if pk is on segment pi, pj
// assumes you've already determined that pi, pj, and pk are collinear
bool onSegment(pair<double, double> pi, pair<double, double> pj, pair<double, double> pk) {
	if (min(pi.first, pj.first) <= pk.first && pk.first <= max(pi.first, pj.first) && min(pi.second, pj.second) <= pk.second && pk.second <= max(pi.second, pj.second))
		return true;
    
	return false;
}

// returns direction of pk relative to segment pi, pj
double direction(pair<double, double> pi, pair<double, double> pj, pair<double, double> pk) {
	return cross(sub(pk, pi), sub(pj, pi));
}

// segments p1 -> p2 and p3 -> p4
bool segmentsIntersect(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3, pair<double, double> p4) {
	double d1 = direction(p3, p4, p1);
	double d2 = direction(p3, p4, p2);
	double d3 = direction(p1, p2, p3);
	double d4 = direction(p1, p2, p4);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;

	// handle collinear edge cases
	if (d1 == 0 && onSegment(p3, p4, p1))
		return true;
	if (d2 == 0 && onSegment(p3, p4, p2))
		return true;
	if (d3 == 0 && onSegment(p1, p2, p3))
		return true;
	if (d4 == 0 && onSegment(p1, p2, p4))
		return true;

	return false;
}

int main() {
    int cases;

    cin >> cases;

    cout << fixed << setprecision(2);

    for (int i = 0; i < cases; i++) {
        double x1, y1, x2, y2, x3, y3, x4, y4;

        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        pair<double, double> p1 = pair<double, double>(x1, y1);
        pair<double, double> p2 = pair<double, double>(x2, y2);
        pair<double, double> p3 = pair<double, double>(x3, y3);
        pair<double, double> p4 = pair<double, double>(x4, y4);

        //Case 0: the segments intersect and we're done here
        if (segmentsIntersect(p1, p2, p3, p4)) cout << 0.00 << endl;
        else {
            //Cases:
            //Case 1: the closest distance is some distance between some of the 4 endpoints.
            //Case 2: the closest distance is a projection from one endpoint to the other line.

            double p3M = dot(sub(p2, p1), sub(p3, p1)) / distanceSquared(p1, p2);
            double p4M = dot(sub(p2, p1), sub(p4, p1)) / distanceSquared(p1, p2);

            double p1M = dot(sub(p4, p3), sub(p1, p3)) / distanceSquared(p3, p4);
            double p2M = dot(sub(p4, p3), sub(p2, p3)) / distanceSquared(p3, p4);

            double minDist = 1000000;

            if (p1M >= 0 && p1M <= 1) {
                double p1Dist = sqrt(distanceSquared(p1, add(p3, mult(sub(p4, p3), dot(sub(p4, p3), sub(p1, p3)) / distanceSquared(p3, p4)))));

                minDist = min(minDist, p1Dist);
            }
            if (p2M >= 0 && p2M <= 1) {
                double p2Dist = sqrt(distanceSquared(p2, add(p3, mult(sub(p4, p3), dot(sub(p4, p3), sub(p2, p3)) / distanceSquared(p3, p4)))));

                minDist = min(minDist, p2Dist);
            }
            if (p3M >= 0 && p3M <= 1) {
                double p3Dist = sqrt(distanceSquared(p3, add(p1, mult(sub(p2, p1), dot(sub(p2, p1), sub(p3, p1)) / distanceSquared(p1, p2)))));

                minDist = min(minDist, p3Dist);
            }
            if (p4M >= 0 && p4M <= 1) {
                double p4Dist = sqrt(distanceSquared(p4, add(p1, mult(sub(p2, p1), dot(sub(p2, p1), sub(p4, p1)) / distanceSquared(p1, p2)))));

                minDist = min(minDist, p4Dist);
            }

            double dist1_3 = sqrt(distanceSquared(p1, p3));
            double dist1_4 = sqrt(distanceSquared(p1, p4));
            double dist2_3 = sqrt(distanceSquared(p2, p3));
            double dist2_4 = sqrt(distanceSquared(p2, p4));

            cout << min(minDist, min(min(dist1_3, dist1_4), min(dist2_3, dist2_4))) << endl;
        }
    }
}