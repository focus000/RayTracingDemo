#include <cmath>
#include <iostream>

template<typename T>
class Vec3 {
    public:
    T x;
    T y;
    T z;
    Vec3() : x(T(0)) {}
    Vec3(T xx) : x(xx), y(xx), z(xx) {}
    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
    Vec3<T> operator * (const T &f) const { return Vec3<T>(x * f, y * f, z * f); }
    Vec3<T> operator * (const Vec3<T> &v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }
    T dot(const Vec3<T> &v) const {return x * v.x + y * v.y + z * v.z; }
    Vec3<T> operator - (const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
    Vec3<T> operator + (const Vec3<T> &v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    Vec3<T>& operator += (const Vec3<T> &v) const { x += v.x; y += v.y; z += v.z; return *this; }
    Vec3<T>& operator *= (const Vec3<T> &v) const { x *= v.x; y *= v.y; z *= v.z; return *this; }
    Vec3<T> operator - () const { return Vec3<T>(-x, -y, -z); }
    T length2() const { return x * x + y * y + z * z; }
    // should implment template sqrt
    T length() const { return sqrt(length2()); }
    Vec3<T>& normalize() { return *this *= 1/length(); }
    friend std::ostream & operator << (std::ostream &os, const Vec3<T> &v) {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }
};

typedef Vec3<float> Vec3f;

class Sphere {
    public:
    Vec3f center;
    float radius, radius2;
    Vec3f surfaceColor, emissionColor;
    float transparency, reflaection;
    Sphere(
        const Vec3f &c,
        const float &r,
        const Vec3f &sc,
        const Vec3f &ec = 0,
        const float &transp = 0,
        const float &refl = 0
    ) : center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec), transparency(transp), reflaection(refl) {}
    // t0, t1 is the distence to insect points
    bool intersect(Vec3f rayOrigin, Vec3f rayDirction, float &t0, float &t1) {
        Vec3f l = center - rayOrigin;
        float tca = l.dot(rayDirction);
        float tca2 = tca * tca;
        float l2 = l.dot(l);
        if (tca2 < l2 - radius2) return false;
        float thc = sqrt(radius2 - l2 + tca2);
        t0 = tca - thc;
        t1 = tca + thc;
        return true;
    }
};