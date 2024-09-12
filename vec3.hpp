// vec3.hpp
#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>

template <typename T>
class BaseVec3 {
private:
    T components[3];

public:
    // Vector variables
    T& x = components[0];
    T& y = components[1];
    T& z = components[2];

    // Constructors
    BaseVec3() : components{0, 0, 0} {}
    BaseVec3(T _x, T _y, T _z): components{_x, _y, _z} {}
    BaseVec3(const BaseVec3& copy) : components{copy.x, copy.y, copy.z} {}
    
    // Copy assignment operator
    BaseVec3& operator=(const BaseVec3& copy) {
        if (this != &copy) {
            components[0] = copy.components[0];
            components[1] = copy.components[1];
            components[2] = copy.components[2];
        }
        return *this;
    }

    // Magnitude function
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

class vec3 : public BaseVec3<float> {
public:
    vec3() : BaseVec3() {}
    vec3(float x, float y, float z) : BaseVec3(x, y, z) {}
    vec3(const vec3& other) : BaseVec3(other) {}

    vec3& operator=(const vec3& other) {
        if (this != &other) {
            BaseVec3::operator=(other);
        }
        return *this;
    }

    // Addition operator
    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator
    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication operator
    vec3 operator*(int scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    // Dot product operator
    float dot(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Unit vector function
    vec3 unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return vec3(x / mag, y / mag, z / mag);
        } else {
            return vec3(0, 0, 0);
        }
    }

    // Cross product function
    vec3 cross(const vec3& other) const {
        return vec3(
            y * other.z - z * other.y,  // x
            z * other.x - x * other.z,  // y
            x * other.y - y * other.x   // z
        );
    }

    // Equality operator
    bool operator==(const vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

class ivec3 : public BaseVec3<int> {
public:
    ivec3() : BaseVec3() {}
    ivec3(int x, int y, int z) : BaseVec3(x, y, z) {}
    ivec3(const ivec3& other) : BaseVec3(other) {}

    ivec3& operator=(const ivec3& other) {
        if (this != &other) {
            BaseVec3::operator=(other);
        }
        return *this;
    }

    // Addition operator
    ivec3 operator+(const ivec3& other) const {
        return ivec3(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator
    ivec3 operator-(const ivec3& other) const {
        return ivec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication operator
    ivec3 operator*(int scalar) const {
        return ivec3(x * scalar, y * scalar, z * scalar);
    }

    // Dot product operator
    int dot(const ivec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

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

    // Equality operator
    bool operator==(const ivec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

#endif // VEC3_HPP