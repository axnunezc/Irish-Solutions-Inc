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