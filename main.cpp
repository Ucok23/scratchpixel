#include <cstdint>
#include <cmath>

template<typename T>
class Vec3 {
public:
    Vec3() : x(T(0)), y(T(0)), z(T(0)) {}

    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

    T x, y, z;

    T length() {
        return sqrt(x * x + y * y + z * z);
    }

    T dot(const Vec3<T> &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3<T> &normalize() {
        T len = length();
        if (len > 0) {
            T invLen = 1 / len;
            x *= invLen, y *= invLen, z *= invLen;
        }
        return *this;
    }

    Vec3<T> cross(const Vec3<T> &v) const {
        return Vec3<T>(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
        );
    }

    Vec3<T> operator +(const Vec3<T> &v) const {
        return Vec3<T>(x + v.x, y + v.y, z + v.z);
    }

    Vec3<T> operator -(const Vec3<T> &v) const {
        return Vec3<T>(x - v.x, y - v.y, z - v.z);
    }

    Vec3<T> operator *(const T &r) const {
        return Vec3<T>(x * r, y * r, z * r);
    }

private:
    explicit Vec3(const T &xx) : x(xx), y(xx), z(xx) {}
};

template<typename T>
class Matrix44 {
public:
    Matrix44() {}

    const T* operator [] (uint8_t i) const { return m[i]; }

    T m[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    Matrix44 operator * (const Matrix44& rhs) const {
        Matrix44 mult;
        for (uint8_t i = 0; i < 4; ++i) {
            for (uint8_t j = 0; j < 4; ++j) {
                mult[i][j] = m[i][0] * rhs[0][j] +
                             m[i][1] * rhs[1][j] +
                             m[i][2] * rhs[2][j] +
                             m[i][3] * rhs[3][j];
            }
        }
        return mult;
    }
};

typedef Vec3<float> Vec3f;
typedef Matrix44<float> Matrix44f;

int main() {
    Vec3f a(2, 2, 2);
    Vec3f b(1, 1, 1);
    int d = 4;

    Vec3f c = a + b;
    Vec3f e = a * d;
    a.normalize();

    return 0;
}
