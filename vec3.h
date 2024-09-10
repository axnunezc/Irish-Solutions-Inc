// vec3.h
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <algorithm>
#include <array>

template <typename T>
class BaseVec3 {
protected:
    T components[3];

public:
    // Vector variables
    T& x = components[0];
    T& y = components[1];
    T& z = components[2];

    // Constructors
    BaseVec3() : components{0, 0, 0} {};
    BaseVec3(T x, T y, T z): components{x, y, z} {};
    BaseVec3(const BaseVec3& other) : components{other.components[0], other.components[1], other.components[2]} {};
    
    // Copy assignment operator
    BaseVec3& operator=(const BaseVec3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }
};

class vec3 : public BaseVec3<float> {
public:
    vec3();
    vec3(float x, float y, float z);
    vec3 cross(const vec3& other) const;
};

class ivec3 : public BaseVec3<int> {
public:
    ivec3();
    ivec3(int x, int y, int z);
    int magnitude() const; // int magnitude
};

#endif // VEC3_H