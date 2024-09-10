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
        BaseVec2();
        BaseVec2(T x, T y);
        BaseVec2(const BaseVec2& other);
};

#endif