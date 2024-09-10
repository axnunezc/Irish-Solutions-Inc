// vec2.hpp
#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <iostream>

template <typename T>
class BaseVec2 {
    protected:
        T components [2];

    public:
        // Vector variables
        T& x = components[0];
        T& y = components[1];

        // Constructors
        BaseVec2() : components{0, 0} {};
        BaseVec2(T x, T y) : components{x, y} {}
        BaseVec2(const BaseVec2& other) : components{other.x, other.y} {}
        
        // Copy assignment operator
        BaseVec2& operator=(const BaseVec2& other) {
            if (this != &other) {
                components[0] = other.components[0];
                components[1] = other.components[1];
            }
            return *this;
        }
};

class vec2 : public BaseVec2<float> {
public:
    vec2() : BaseVec2() {}
    vec2(float x, float y) : BaseVec2(x, y) {}
    vec2(const vec2& other) : BaseVec2(other) {}

    vec2& operator=(const vec2& other) {
        BaseVec2::operator=(other);
        return *this;
    }
};

class ivec2 : public BaseVec2<int> {
public:
    ivec2() : BaseVec2() {}
    ivec2(int x, int y) : BaseVec2(x, y) {}
    ivec2(const ivec2& other) : BaseVec2(other) {}

    ivec2& operator=(const ivec2& other) {
        BaseVec2::operator=(other);
        return *this;
    }

    int magnitude() const {
        // Manhattan distance
        return std::abs(x) + std::abs(y);
    }

};

#endif // VEC2_HPP