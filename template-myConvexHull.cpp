#include "bits/stdc++.h"
using namespace std;

#define T long long
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    Point operator+(const Point &u) const { return Point(x + u.x, y + u.y); }
    Point operator-(const Point &u) const { return Point(x - u.x, y - u.y); }
    Point operator*(const long long u) const { return Point(x * u, y * u); }
    Point operator*(const double u) const { return Point(x * u, y * u); }
    Point operator/(const double u) const { return Point(x / u, y / u); }

    bool operator < (Point& c) {
        return make_pair(x,y) < make_pair(c.x, c.y);
    }
    
    friend T dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
    friend T cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
    friend T length(Point a) { return sqrt(dot(a, a)); }
    friend T sqLength(Point a) { return dot(a, a); }
    friend T distance(Point a, Point b) {return length(a-b);}
    friend T angle(Point u) { return atan2(u.y, u.x); }
    friend istream& operator>>(istream &is, Point &p) {   return is >> p.x >> p.y;}
    friend ostream& operator<<(ostream &os, const Point &p) { return os << p.x << " " << p.y;}
};

long long Area(Point a, Point b, Point c) { return cross(b - a, b - c); }
int sgn(const long long& x) { return x >= 0 ? x ? 1 : 0 : -1; }

void ConvexHull(vector<Point> &points, vector<Point> &hull) {
    sort(points.begin(), points.end());

    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (int rep = 0; rep < 2; rep++) {
        int k = (rep==0?2 : 1);
        for (int i = k; i < points.size(); i++) {
            while (hull.size() >= 2) {
                Point A = hull.end()[-2];
                Point B = hull.end()[-1];
                Point C = points[i];
                if (Area(A, B, C) >= 0) break;
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        reverse(points.begin(), points.end());
    }
    hull.pop_back();
}

