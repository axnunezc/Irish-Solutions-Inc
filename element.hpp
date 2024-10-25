// element.hpp
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "screen.hpp"
#include "stb_image.h"

class Element {
public:
    virtual ~Element() = default;

    virtual void draw(Screen& screen) = 0;
};

class Box : public Element {
public:
    vec2 min;
    vec2 max;
    vec3 color;

    Box() : min(0.0f, 0.0f), max(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f) {}

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
public:
    vec2 start;
    vec2 end;
    vec3 color;

    Line() : start(0.0f, 0.0f), end(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f) {}

    Line(vec2 _start, vec2 _end, vec3 _color)
        : start(_start), end(_end), color(_color) {}

    void draw(Screen& screen) override {
        int x0 = static_cast<int>(std::round(start.x));
        int y0 = static_cast<int>(std::round(start.y));
        int x1 = static_cast<int>(std::round(end.x));
        int y1 = static_cast<int>(std::round(end.y));

        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            screen.setPixel(vec2(static_cast<float>(x0), static_cast<float>(y0)), color); // Set pixel
            
            if (x0 == x1 && y0 == y1) break; // Exit if we've reached the endpoint
            
            int err2 = err * 2;
            if (err2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (err2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }
};

class Triangle : public Element {
public:
    vec2 p1, p2, p3;
    vec3 color;

    Triangle() : p1(0.0f, 0.0f), p2(0.0f, 0.0f), p3(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f) {}

    Triangle(vec2 _p1, vec2 _p2, vec2 _p3, vec3 _color)
        : p1(_p1), p2(_p2), p3(_p3), color(_color) {}

    void draw(Screen& screen) override {
        float minX = std::floor(std::min({ p1.x, p2.x, p3.x }));
        float maxX = std::ceil(std::max({ p1.x, p2.x, p3.x }));
        float minY = std::floor(std::min({ p1.y, p2.y, p3.y }));
        float maxY = std::ceil(std::max({ p1.y, p2.y, p3.y }));

        for (int y = static_cast<int>(minY); y <= static_cast<int>(maxY); ++y) {
            for (int x = static_cast<int>(minX); x <= static_cast<int>(maxX); ++x) {
                vec2 pixel(x + 0.5f, y + 0.5f);

                if (inTriangle(pixel, p1, p2, p3)) {
                    screen.setPixel(pixel, color);
                }
            }
        }
    }

private:
    // Barycentric coordinates
    bool inTriangle(const vec2& p, const vec2& a, const vec2& b, const vec2& c) {
        float area = triangleArea(a, b, c);
        float area1 = triangleArea(p, b, c);
        float area2 = triangleArea(a, p, c);
        float area3 = triangleArea(a, b, p);
        return (area == area1 + area2 + area3);
    }

    float triangleArea(const vec2& a, const vec2& b, const vec2& c) {
        return std::abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0f);
    }
};

class Image : public Element {
public:
    Image(const std::string& filePath, const vec2& position, float scale = 1.0f, float rotation = 0.0f)
        : textureSurface(nullptr), position(position), scale(scale), rotation(rotation) {
        
        int imgWidth, imgHeight, imgChannels;
        unsigned char* imgData = stbi_load(filePath.c_str(), &imgWidth, &imgHeight, &imgChannels, 4);
        if (imgData) {
            textureSurface = SDL_CreateRGBSurfaceWithFormatFrom(imgData, imgWidth, imgHeight, 32, imgWidth * 4, SDL_PIXELFORMAT_RGBA32);
            if (!textureSurface) {
                std::cerr << "Failed to create SDL surface from image data.\n";
                stbi_image_free(imgData);
            }
        } else {
            std::cerr << "Failed to load image: " << filePath << "\n";
        }
    }

    ~Image() {
        if (textureSurface) {
            SDL_FreeSurface(textureSurface);
        }
    }

    void draw(Screen& screen) override {
        if (!textureSurface) return;

        SDL_Rect dstRect = { static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(textureSurface->w * scale), static_cast<int>(textureSurface->h * scale) };
        SDL_BlitScaled(textureSurface, nullptr, screen.getSurface(), &dstRect);
    }

    void setScale(float newScale) { scale = newScale; }
    void setRotation(float newRotation) { rotation = newRotation; }

private:
    SDL_Surface* textureSurface;
    vec2 position;
    float scale;
    float rotation;
};

#endif // ELEMENT_HPP