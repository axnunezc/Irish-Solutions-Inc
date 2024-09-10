// vec3.hpp
#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>

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
    BaseVec3() : components{0, 0, 0} {}
    BaseVec3(T x, T y, T z): components{x, y, z} {}
    BaseVec3(const BaseVec3& other) : components{other.x, other.y, other.z} {}
    
    // Copy assignment operator
    BaseVec3& operator=(const BaseVec3& other) {
        if (this != &other) {
            components[0] = other.components[0];
            components[1] = other.components[1];
            components[2] = other.components[2];
        }
        return *this;
    }

    // Addition operator
    BaseVec3 operator+(const BaseVec3& other) const {
        return BaseVec3(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator
    BaseVec3 operator-(const BaseVec3& other) const {
        return BaseVec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication operator
    BaseVec3 operator*(T scalar) const {
        return BaseVec3(x * scalar, y * scalar, z * scalar);
    }

    // Dot product operator
    T dot(const BaseVec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Magnitude function
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Unit vector function
    BaseVec3 unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return BaseVec3(x / mag, y / mag, z / mag) 
        } else {
            return BaseVec3(0, 0, 0);
        }
    }
};

class vec3 : public BaseVec3<float> {
public:
    vec3() : BaseVec3() {}
    vec3(float x, float y, float z) : BaseVec3(x, y, z) {}
    vec3(const vec3& other) : BaseVec3(other) {}

    vec3& operator=(const vec3& other) {
        BaseVec3::operator=(other);
        return *this;
    }
};

class ivec3 : public BaseVec3<int> {
public:
    ivec3() : BaseVec3() {}
    ivec3(int x, int y, int z) : BaseVec3(x, y, z) {}
    ivec3(const ivec3& other) : BaseVec3(other) {}

    // Magnitude function
    int magnitude() const {
        // Manhattan distance
        return std::abs(x) + std::abs(y) + std::abs(z);
    }

    // Unit vector function
    ivec3 unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return ivec3(static_cast<int>(std::floor(x / mag)),
                         static_cast<int>(std::floor(y / mag)),
                         static_cast<int>(std::floor(z / mag)));
        } else {
            return ivec3(0, 0, 0);
        }
    }
};

#endif // VEC3_HPP