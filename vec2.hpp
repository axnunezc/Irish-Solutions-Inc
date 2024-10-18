#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <iostream>
#include <stdexcept>

template <typename T>
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
    T magnitude() const {
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
    BaseVec2 operator+(const BaseVec2& other) const {
        return BaseVec2(x + other.x, y + other.y);
    }

    BaseVec2 operator-(const BaseVec2& other) const {
        return BaseVec2(x - other.x, y - other.y);
    }

    BaseVec2 operator*(T scalar) const {
        return BaseVec2(x * scalar, y * scalar);
    }

    BaseVec2& operator+=(const BaseVec2& other) {
        x += other.x;
        y += other.y;
        return (*this);
    }

    BaseVec2& operator-=(const BaseVec2& other) {
        x -= other.x;
        y -= other.y;
        return (*this);
    }

    BaseVec2& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return (*this);
    }

    // Dot product
    T dot(const BaseVec2& other) const {
        return x * other.x + y * other.y;
    }

    // Equality operator
    bool operator==(const BaseVec2& other) const {
        return x == other.x && y == other.y;
    }

    // Unit vector function
    BaseVec2 unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return BaseVec2(x / mag, y / mag);
        } else {
            return BaseVec2(0, 0);
        }
    }
};

typedef BaseVec2<float> vec2;

template <>
inline int BaseVec2<int>::magnitude() const {
    // Manhattan distance
    return std::abs(x) + std::abs(y);
}

template <>
inline BaseVec2<int> BaseVec2<int>::unit() const {
    float mag = magnitude();
    if (mag != 0) {
        return BaseVec2(static_cast<int>(std::floor(x / mag)),
                        static_cast<int>(std::floor(y / mag)));
    } else {
        return BaseVec2(0, 0);
    }
}

typedef BaseVec2<int> ivec2;

#endif // VEC2_HPP