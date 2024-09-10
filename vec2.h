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
        BaseVec2& operator=(const BaseVec2& other);
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