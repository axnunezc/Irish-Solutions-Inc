// element.hpp
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "screen.hpp"

class Element {
public:
    virtual ~Element() = default;

    virtual void draw(Screen& screen) = 0;
};

class Box : public Element {
private:
    vec2 min;
    vec2 max;
    vec3 color;

public:
    Box(vec2 _min, vec2 _max, vec3 _color)
        : min(_min), max(_max), color(_color) {}

    void draw(Screen& screen) override {
        int x1 = static_cast<int>(std::round(std::min(min.x, max.x)));
        int y1 = static_cast<int>(std::round(std::min(min.y, max.y)));
        int x2 = static_cast<int>(std::round(std::max(min.x, max.x)));
        int y2 = static_cast<int>(std::round(std::max(min.y, max.y)));

        for (int y = y1; y <= y2; ++y) {
            for (int x = x1; x <= x2; ++x) {
                screen.setPixel(vec2(static_cast<float>(x), static_cast<float>(y)), color);
            }
        }
    }
};

class Line : public Element {
private:
    vec2 start;
    vec2 end;
    vec3 color;

public:
    Line(vec2 _start, vec2 _end, vec3 _color)
        : start(_start), end(_end), color(_color) {}
};

#endif // ELEMENT_HPP