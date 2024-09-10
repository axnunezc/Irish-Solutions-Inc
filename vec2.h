// vec2.h
#ifndef VEC2_H
#define VEC2_H

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
        BaseVec2(const BaseVec2& other) : components{other.components[0], other.components[1]} {}
        
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
    vec2();
    vec2(float x, float y);
};

class ivec2 : public BaseVec2<int> {
public:
    ivec2();
    ivec2(int x, int y);
    int magnitude() const; // int magnitude
};

#endif // VEC2_H