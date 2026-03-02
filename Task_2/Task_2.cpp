#include <iostream>
#include <cmath>
#include <string>
#include <windows.h>

using namespace std;

struct Point {
    string name;
    double x, y;
};

double distanceToLine(double x, double y, double a, double b, double c) {
    return fabs(a * x + b * y + c) / sqrt(a * a + b * b);
}

int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    double a = 3, b = -4, c = 5;

    Point points[] = {
        {"M1", -1, 1},
        {"M2", 1.5, 2},
        {"M3", 6, 4},
        {"M4", 3, 4},
        {"M5", 1, 5}
    };

    int n = sizeof(points) / sizeof(points[0]);

    double minDist = distanceToLine(points[0].x, points[0].y, a, b, c);
    string closest = points[0].name;

    for (int i = 1; i < n; i++) {
        double d = distanceToLine(points[i].x, points[i].y, a, b, c);
        cout << points[i].name << " -> відстань = " << d << endl;
        if (d < minDist) {
            minDist = d;
            closest = points[i].name;
        }
    }

    cout << "\nНайближчий населений пункт: " << closest
        << " (відстань = " << minDist << ")" << endl;

    return 0;
}

