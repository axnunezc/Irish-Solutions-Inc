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
    T magnitude() const {
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
    BaseVec3 operator+(const BaseVec3& other) const {
        return BaseVec3(x + other.x, y + other.y, z + other.z);
    }

    BaseVec3 operator-(const BaseVec3& other) const {
        return BaseVec3(x - other.x, y - other.y, z - other.z);
    }

    BaseVec3 operator*(T scalar) const {
        return BaseVec3(x * scalar, y * scalar, z * scalar);
    }

    BaseVec3& operator+=(const BaseVec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return (*this);
    }

    BaseVec3& operator-=(const BaseVec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return (*this);
    }

    BaseVec3& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return (*this);
    }

    // Dot product
    T dot(const BaseVec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product (only meaningful for 3D vectors)
    BaseVec3 cross(const BaseVec3& other) const {
        return BaseVec3(
            y * other.z - z * other.y,  // x
            z * other.x - x * other.z,  // y
            x * other.y - y * other.x   // z
        );
    }

    // Equality operator
    bool operator==(const BaseVec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Unit vector function
    BaseVec3 unit() const {
        float mag = magnitude();
        if (mag != 0) {
            return BaseVec3(x / mag, y / mag, z / mag);
        } else {
            return BaseVec3(0, 0, 0);
        }
    }
};

typedef BaseVec3<float> vec3;

template <>
int BaseVec3<int>::magnitude() const {
    // Manhattan distance
    return std::abs(x) + std::abs(y) + std::abs(z);
}

template <>
BaseVec3<int> BaseVec3<int>::unit() const {
    float mag = magnitude();
    if (mag != 0) {
        return BaseVec3(static_cast<int>(std::floor(x / mag)),
                        static_cast<int>(std::floor(y / mag)),
                        static_cast<int>(std::floor(z / mag)));
    } else {
        return BaseVec3(0, 0, 0);
    }
}

typedef BaseVec3<int> ivec3;

#endif // VEC3_HPP