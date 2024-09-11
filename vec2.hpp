// vec2.hpp
#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <iostream>

template <typename T>
class BaseVec2 {
    private:
        T components [2];

    public:
        // Vector variables
        T& x = components[0];
        T& y = components[1];

        // Constructors
        BaseVec2() : components{0, 0} {};
        BaseVec2(T _x, T _y) : components{_x, _y} {}
        BaseVec2(const BaseVec2& copy) : components{copy.x, copy.y} {}
        
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

class vec2 : public BaseVec2<float> {
public:
    vec2() : BaseVec2() {}
    vec2(float x, float y) : BaseVec2(x, y) {}
    vec2(const vec2& other) : BaseVec2(other) {}

    vec2& operator=(const vec2& other) {
        if (this != &other) {
            BaseVec2::operator=(other);
        }
        return *this;
    }

    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }

    vec2 operator*(float scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    // Dot product operator
    float dot(const vec2& other) const {
        return x * other.x + y * other.y;
    }

    bool operator==(const vec2& other) const {
        return x == other.x && y == other.y;
    }
};

class ivec2 : public BaseVec2<int> {
public:
    ivec2() : BaseVec2() {}
    ivec2(int x, int y) : BaseVec2(x, y) {}
    ivec2(const ivec2& other) : BaseVec2(other) {}

    ivec2& operator=(const ivec2& other) {
        if (this != &other) {
            BaseVec2::operator=(other);
        }
        return *this;
    }

    ivec2 operator+(const ivec2& other) const {
        return ivec2(x + other.x, y + other.y);
    }

    ivec2 operator-(const ivec2& other) const {
        return ivec2(x - other.x, y - other.y);
    }

    ivec2 operator*(int scalar) const {
        return ivec2(x * scalar, y * scalar);
    }

    int magnitude() const {
        // Manhattan distance
        return std::abs(x) + std::abs(y);
    }

    // Unit vector function
    ivec2 unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return ivec2(static_cast<int>(std::floor(x / mag)), static_cast<int>(std::floor(y / mag)));
        } else {
            return ivec2(0, 0);
        }
    }

    // Equality operator
    bool operator==(const ivec2& other) const {
        return x == other.x && y == other.y;
    }
};

#endif // VEC2_HPP