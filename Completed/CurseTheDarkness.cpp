#include <iostream>
#include <vector>

using namespace std;

double DistanceSquared(double x1, double y1, double x2, double y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int main() {
    int testCases;

    cin >> testCases;

    for (int i = 0; i < testCases; i++) {
        double bookX, bookY;
    
        cin >> bookX >> bookY;

        int candles;

        cin >> candles;

        bool bookLit = false;
        for (int j = 0; j < candles; j++) {
            double candleX, candleY;

            cin >> candleX >> candleY;

            if (bookLit) continue;

            if (DistanceSquared(candleX, candleY, bookX, bookY) < 64.0) {
                cout << "light a candle" << endl;

                bookLit = true;
            }
        }

        if (!bookLit) cout << "curse the darkness" << endl;
    }
}