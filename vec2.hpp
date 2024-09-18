#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <iostream>
#include <stdexcept>

template <typename T, typename Derived>
class BaseVec2 {
protected:
    T components[2];

public:
    // Vector variables
    T& x = components[0];
    T& y = components[1];

    // Constructors
    BaseVec2() : components{0, 0} {}
    BaseVec2(T _x, T _y) : components{_x, _y} {}
    BaseVec2(const BaseVec2& copy) : components{copy.components[0], copy.components[1]} {}

    // Copy assignment operator
    BaseVec2& operator=(const BaseVec2& copy) {
        if (this != &copy) {
            components[0] = copy.components[0];
            components[1] = copy.components[1];
        }
        return *this;
    }

    // Magnitude function
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Overload the [] operator for accessing components by index
    T& operator[](int index) {
        if (index < 0 || index > 1) {
            throw std::out_of_range("Index out of range for vec2");
        }
        return components[index];
    }

    // Arithmetic operations
    Derived operator+(const Derived& other) const {
        return Derived(x + other.x, y + other.y);
    }

    Derived operator-(const Derived& other) const {
        return Derived(x - other.x, y - other.y);
    }

    Derived operator*(T scalar) const {
        return Derived(x * scalar, y * scalar);
    }

    Derived& operator+=(const Derived& other) {
        x += other.x;
        y += other.y;
        return static_cast<Derived&>(*this);
    }

    Derived& operator-=(const Derived& other) {
        x -= other.x;
        y -= other.y;
        return static_cast<Derived&>(*this);
    }

    Derived& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return static_cast<Derived&>(*this);
    }

    // Dot product
    T dot(const Derived& other) const {
        return x * other.x + y * other.y;
    }

    // Equality operator
    bool operator==(const Derived& other) const {
        return x == other.x && y == other.y;
    }

    // Unit vector function
    Derived unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return Derived(x / mag, y / mag);
        } else {
            return Derived(0, 0);
        }
    }
};

class vec2 : public BaseVec2<float, vec2> {
public:
    vec2() : BaseVec2() {}
    vec2(float x, float y) : BaseVec2(x, y) {}
    vec2(const vec2& other) : BaseVec2(other) {}
};

class ivec2 : public BaseVec2<int, ivec2> {
public:
    ivec2() : BaseVec2() {}
    ivec2(int x, int y) : BaseVec2(x, y) {}
    ivec2(const ivec2& other) : BaseVec2(other) {}

    // Magnitude specialization for ivec2
    int magnitude() const {
        // Manhattan distance
        return std::abs(x) + std::abs(y);
    }

    // Unit vector specialization for ivec2
    ivec2 unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return ivec2(static_cast<int>(std::floor(x / mag)),
                         static_cast<int>(std::floor(y / mag)));
        } else {
            return ivec2(0, 0);
        }
    }
};

#endif // VEC2_HPP