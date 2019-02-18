#ifndef VECTOR2D_HH
#define VECTOR2D_HH

#include <cmath>
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
        return std::sqrt(this->px * this->px + this->py * this->py);
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

    friend std::ostream &operator<<(std::ostream &s, const Vector2D<T> v) {
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

  private:
    T px, py;
};

const Vector2D<double> ORIGIN = Vector2D<double>(0, 0);

#endif // VECTOR2D_HH
