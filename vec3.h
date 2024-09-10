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
    BaseVec3();
    BaseVec3(T x, T y, T z);
    BaseVec3(const BaseVec3& other);
    BaseVec3& operator=(const BaseVec3& other);
};

#endif // VEC3_H