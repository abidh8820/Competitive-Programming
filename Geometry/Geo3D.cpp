#include <bits/stdc++.h>
using namespace std;
//#define static_assert(...)

typedef double Tf;
typedef double Ti;  /// use long long for exactness
const Tf PI = acos(-1), EPS = 1e-9;
int dcmp(Tf x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

struct Point3 {
    Ti x, y, z;
    Point3(Ti x = 0, Ti y = 0, Ti z = 0) : x(x), y(y), z(z) {}

    Point3 operator+(const Point3 &u) const { return Point3(x + u.x, y + u.y, z + u.z); }
    Point3 operator-(const Point3 &u) const { return Point3(x - u.x, y - u.y, z - u.z); }
    Point3 operator*(const long long u) const { return Point3(x * u, y * u, z * u); }
    Point3 operator*(const Tf u) const { return Point3(x * u, y * u, z * u); }
    Point3 operator/(const Tf u) const { return Point3(x / u, y / u, z / u); }

    bool operator==(const Point3 &u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0 && dcmp(z - u.z); }
    bool operator!=(const Point3 &u) const { return !(*this == u); }
    bool operator<(const Point3 &u) const {
        return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0) ||
               (dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0 && dcmp(z - u.z) < 0);
    }

    friend istream &operator>>(istream &is, Point3 &p) { return is >> p.x >> p.y >> p.z; }
    friend ostream &operator<<(ostream &os, const Point3 &p) { return os << p.x << " " << p.y << " " << p.z; }
};

Ti dot(Point3 a, Point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Point3 cross(Point3 v, Point3 w) {
    return Point3(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
}

// Tf length(Point3 a) { return sqrt(dot(a, a)); }
// Ti sqLength(Point3 a) { return dot(a, a); }
// Tf distance(Point3 a, Point3 b) {return length(a-b);}
// Tf angle(Point3 u) { return atan2(u.y, u.x); }

int main() { cout << "bruh" << endl; }
