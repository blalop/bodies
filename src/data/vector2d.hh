#ifndef VECTOR2D_HH
#define VECTOR2D_HH

#ifdef QT_CORE_LIB
#include <QtMath>
#define _sqrt(x) qSqrt(x)
#else
#include <cmath>
#define _sqrt(x) std::sqrt(x)
#endif

#include <iomanip>
#include <iostream>

template <typename T> class Vector2D {
  public:
    Vector2D() : px(0.0), py(0.0) {}

    Vector2D(T x, T y) : px(x), py(y) {}

    template <typename U> Vector2D(Vector2D<U> v) {
        this->px = v.px;
        this->py = v.py;
    }

    T x() const { return this->px; }

    T y() const { return this->py; }

    double mod() const {
        return _sqrt(this->px * this->px + this->py * this->py);
    }

    Vector2D<T> operator+(const Vector2D<T> v) const {
        return Vector2D(this->px + v.px, this->py + v.py);
    }

    Vector2D<T> operator-(const Vector2D<T> v) const {
        return Vector2D(this->px - v.px, this->py - v.py);
    }

    Vector2D<T> operator*(T f) const {
        return Vector2D(this->px * f, this->py * f);
    }

    Vector2D<T> operator/(T f) const {
        return Vector2D(this->px / f, this->py / f);
    }

    bool operator==(const Vector2D<T> v) const {
        return this->px == v.px && this->py == v.py;
    }

    bool operator!=(const Vector2D<T> v) const { return !(this == v); }

    Vector2D<T> &operator=(const Vector2D<T> v) {
        this->px = v.px;
        this->py = v.py;
        return *this;
    }

    Vector2D<T> &operator+=(const Vector2D<T> v) {
        this->px += v.px;
        this->py += v.py;
        return *this;
    }

    Vector2D<T> &operator-=(const Vector2D<T> v) {
        this->px -= v.px;
        this->py -= v.py;
        return *this;
    }

    Vector2D<T> &operator*=(T f) {
        this->px *= f;
        this->py *= f;
        return *this;
    }

    Vector2D<T> &operator/=(T f) {
        this->px /= f;
        this->py /= f;
        return *this;
    }

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &s, const Vector2D<T1> v);

  private:
    T px, py;
};

template <typename T>
std::ostream &operator<<(std::ostream &s, const Vector2D<T> v) {
    using std::fixed;
    using std::setprecision;
    using std::setw;
    auto precision = s.precision();
    auto width = s.width();
    s << "(";
    s << fixed << setw(width) << setprecision(precision) << v.px;
    s << ", ";
    s << fixed << setw(width) << setprecision(precision) << v.py;
    s << ")";
    return s;
}

#endif // VECTOR2D_HH
