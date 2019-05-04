#ifndef VECTOR2D_HH
#define VECTOR2D_HH

#include <cmath>
#include <iomanip>
#include <iostream>

template <typename T> class Vector2D {
  public:
    T x, y;

    Vector2D() : x(0.0), y(0.0) {}

    Vector2D(T t) : x(t), y(t) {}

    Vector2D(T x, T y) : x(x), y(y) {}

    Vector2D<T> operator+(const T f) const {
        return Vector2D(this->x + f, this->y + f);
    }

    Vector2D<T> operator-(const T f) const {
        return Vector2D(this->x - f, this->y - f);
    }

    Vector2D<T> operator*(const T f) const {
        return Vector2D(this->x * f, this->y * f);
    }

    Vector2D<T> operator/(const T f) const {
        return Vector2D(this->x / f, this->y / f);
    }

    Vector2D<T> operator+(const Vector2D<T> v) const {
        return Vector2D(this->x + v.x, this->y + v.y);
    }

    Vector2D<T> operator-(const Vector2D<T> v) const {
        return Vector2D(this->x - v.x, this->y - v.y);
    }

    Vector2D<T> operator*(const Vector2D<T> v) const {
        return Vector2D(this->x * v.x, this->y * v.y);
    }

    Vector2D<T> operator/(const Vector2D<T> v) const {
        return Vector2D(this->x / v.x, this->y / v.y);
    }

    bool operator==(const Vector2D<T> v) const {
        return this->x == v.x && this->y == v.y;
    }

    bool operator!=(const Vector2D<T> v) const { return !(*this == v); }

    Vector2D<T> &operator=(const Vector2D<T> v) {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }

    Vector2D<T> &operator+=(const Vector2D<T> v) {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    Vector2D<T> &operator-=(const Vector2D<T> v) {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    Vector2D<T> &operator*=(T f) {
        this->x *= f;
        this->y *= f;
        return *this;
    }

    Vector2D<T> &operator/=(T f) {
        this->x /= f;
        this->y /= f;
        return *this;
    }

    double mod() const {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    Vector2D<T> round() const {
        return Vector2D<T>(std::round(this->x), std::round(this->y));
    }

    Vector2D<T> floor() const {
        return Vector2D<T>(std::floor(this->x), std::floor(this->y));
    }

    Vector2D<T> scale(T factor, T min, T max) const {
        T x = factor * (this->x - min) / (max - min);
        T y = factor * (this->y - min) / (max - min);
        return Vector2D<T>(x, y);
    }

    friend std::ostream &operator<<(std::ostream &s, const Vector2D<T> v) {
        s << std::setprecision(5) << "(" << v.x << ", " << v.y << ")";
        return s;
    }

    friend std::istream &operator>>(std::istream &s, Vector2D<T> &v) {
        s >> v.x >> v.y;
        return s;
    }
};

const Vector2D<double> ORIGIN(0.0, 0.0);

#endif // VECTOR2D_HH
