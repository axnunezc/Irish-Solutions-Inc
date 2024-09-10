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
};

#endif // VEC3_H