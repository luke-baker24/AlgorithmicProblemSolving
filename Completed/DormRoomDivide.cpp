#include <iomanip>
#include <iostream>
#include <math.h>
#include <cstdio>
#include <vector>

using namespace std;

typedef pair<long, long> pt;
typedef pair<long double, long double> dpt;

long min(long val1, long val2) {
    if (val1 < val2) return val1;
    else return val2;
}

//yeah this returns long double the area but this is all relative so no one gaf
long double getDTriArea(vector<dpt> polygon) {
    long double area = 0;

    area += polygon[1].second * polygon[0].first - polygon[0].second * polygon[1].first;
    area += polygon[2].second * polygon[1].first - polygon[1].second * polygon[2].first;
    area += polygon[0].second * polygon[2].first - polygon[2].second * polygon[0].first;

    return area;
}

//yeah this returns long double the area but this is all relative so no one gaf
long getTriArea(vector<pt> polygon) {
    long area = 0;

    area += polygon[1].second * polygon[0].first - polygon[0].second * polygon[1].first;
    area += polygon[2].second * polygon[1].first - polygon[1].second * polygon[2].first;
    area += polygon[0].second * polygon[2].first - polygon[2].second * polygon[0].first;

    return area;
}

long double goofyLerpCauseCppIsStupid(long double a, long double b, long double f) {
    return (b - a) * f + a;
}

dpt dptLerp(dpt one, dpt two, long double f) {
    return dpt(goofyLerpCauseCppIsStupid(one.first, two.first, f), goofyLerpCauseCppIsStupid(one.second, two.second, f));
}

vector<dpt> toDptVector(vector<pt> in) {
    return vector<dpt>(in.begin(), in.end());
}

int main() {
    long verts;
    cin >> verts;

    vector<pt> polygon(verts);

    for (long i = 0; i < verts; i++) {
        long x, y;
        cin >> x >> y;

        pt newPt = pt(x, y);

        polygon[i] = newPt;
    }

    pt door = polygon[0];

    //algorithm:
    //go through and find the two polongs that border one half being bigger and one half being smaller.
    //if one polong creates exactly half, we're done. yay!
    //otherwise, start binary searching by longerpolating between those two "transition" polongs.
    //work until the absolute difference between the polygon areas are 10^(-7).

    vector<long> triAreas(verts);
    long totArea = 0;
    for (long i = 1; i < verts - 1; i++) {
        triAreas[i] = getTriArea( { door, polygon[i], polygon[i + 1]});
        totArea += triAreas[i];
    }

    long lowerlongArea = 0;
    long upperlongArea = totArea;

    cout << fixed << setprecision(6);

    for (long i = 1; i < verts - 1; i++) {
        lowerlongArea += triAreas[i];
        upperlongArea -= triAreas[i];

        if (lowerlongArea == upperlongArea) {
            cout << polygon.at(i + 1).first << " " << polygon.at(i + 1).second << endl;

            break;
        }

        //we found the crossover polong. we lerp now my boys
        if (lowerlongArea > upperlongArea) {
            lowerlongArea -= triAreas[i];

            //Find the other two vertices of the triangle we're binary searching
            dpt lowerLerpPt = polygon.at(i);
            dpt upperLerpPt = polygon.at(i + 1);

            long double minLerp = 0.0;
            long double maxLerp = 1.0;
            long double guessLerp = (maxLerp + minLerp) / 2.0;

            dpt lerpPt = dptLerp(lowerLerpPt, upperLerpPt, guessLerp);

            while (true) {
                vector<dpt> lowerPolygon = { door, lowerLerpPt, lerpPt};

                long double lowerTriArea = getDTriArea(lowerPolygon);

                long double lowerArea = lowerlongArea + lowerTriArea;

                if (abs(totArea - lowerArea * 2.0) < 0.0000005)
                    break;

                if (totArea < lowerArea * 2.0)
                    maxLerp = guessLerp;
                else if (totArea > lowerArea * 2.0)
                    minLerp = guessLerp;
                else
                    break;

                guessLerp = (maxLerp + minLerp) / 2.0;

                lerpPt = dptLerp(lowerLerpPt, upperLerpPt, guessLerp);
            }

            cout << lerpPt.first << " " << lerpPt.second << endl;

            break;
        }
    }
}