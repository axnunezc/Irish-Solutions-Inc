// vec3.hpp
#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>

template <typename T, typename Derived>
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

    // Overload the [] operator for accessing components by index
    T& operator[](int index) {
        if (index < 0 || index > 2) {
            throw std::out_of_range("Index out of range for vec3");
        }
        return components[index];
    }

    // Arithmetic operations
    Derived operator+(const Derived& other) const {
        return Derived(x + other.x, y + other.y, z + other.z);
    }

    Derived operator-(const Derived& other) const {
        return Derived(x - other.x, y - other.y, z - other.z);
    }

    Derived operator*(T scalar) const {
        return Derived(x * scalar, y * scalar, z * scalar);
    }

    Derived& operator+=(const Derived& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return static_cast<Derived&>(*this);
    }

    Derived& operator-=(const Derived& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return static_cast<Derived&>(*this);
    }

    Derived& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return static_cast<Derived&>(*this);
    }

    // Dot product
    T dot(const Derived& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product (only meaningful for 3D vectors)
    Derived cross(const Derived& other) const {
        return Derived(
            y * other.z - z * other.y,  // x
            z * other.x - x * other.z,  // y
            x * other.y - y * other.x   // z
        );
    }

    // Equality operator
    bool operator==(const Derived& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Unit vector function
    Derived unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return Derived(x / mag, y / mag, z / mag);
        } else {
            return Derived(0, 0, 0);
        }
    }
};

class vec3 : public BaseVec3<float, vec3> {
public:
    vec3() : BaseVec3() {}
    vec3(float x, float y, float z) : BaseVec3(x, y, z) {}
    vec3(const vec3& other) : BaseVec3(other) {}
};

class ivec3 : public BaseVec3<int, ivec3> {
public:
    ivec3() : BaseVec3() {}
    ivec3(int x, int y, int z) : BaseVec3(x, y, z) {}
    ivec3(const ivec3& other) : BaseVec3(other) {}

    // Magnitude specialization for ivec3
    int magnitude() const {
        // Manhattan distance
        return std::abs(x) + std::abs(y) + std::abs(z);
    }

    // Unit vector specialization for ivec3
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