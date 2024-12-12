// element.hpp
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "screen.hpp"
#include "stb_image.h"
#include "event.hpp"
#include <algorithm>
#include <random>
#include <cstdlib>

class Element {
public:
    virtual ~Element() = default;
    virtual void draw(Screen& screen, const ivec2& offset = {0, 0}) = 0;

    // Getter and setter for position
    vec2 getPosition() const { return position; }
    void setPosition(const vec2& newPosition) { position = newPosition; }

    virtual int getType() const = 0;

protected:
    vec2 position;
};

class Box : public Element {
public:
    Box() : min(0.0f, 0.0f), max(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f) {}

    Box(vec2 _min, vec2 _max, vec3 _color)
        : min(_min), max(_max), color(_color) {}

    void draw(Screen& screen, const ivec2& offset = {0, 0}) override {
        int x1 = static_cast<int>(std::round(std::min(min.x, max.x) + offset.x + position.x));
        int y1 = static_cast<int>(std::round(std::min(min.y, max.y) + offset.y + position.y));
        int x2 = static_cast<int>(std::round(std::max(min.x, max.x) + offset.x + position.x));
        int y2 = static_cast<int>(std::round(std::max(min.y, max.y) + offset.y + position.y));

        for (int y = y1; y <= y2; ++y) {
            for (int x = x1; x <= x2; ++x) {
                screen.setPixel(vec2(static_cast<float>(x), static_cast<float>(y)), color);
            }
        }
    }

    // Getters
    vec2 getMin() const { return min; }
    vec2 getMax() const { return max; }
    vec3 getColor() const { return color; }

    // Setters
    void setMin(const vec2& _min) { min = _min; }
    void setMax(const vec2& _max) { max = _max; }
    void setColor(const vec3& _color) { color = _color; }

    int getType() const override {
        return 1;
    }

    bool containsPoint(const vec2& point) const {
        float minX = std::min(min.x, max.x) + position.x;
        float maxX = std::max(min.x, max.x) + position.x;
        float minY = std::min(min.y, max.y) + position.y;
        float maxY = std::max(min.y, max.y) + position.y;

        return (point.x >= minX && point.x <= maxX &&
                point.y >= minY && point.y <= maxY);
    }

protected:
    vec2 min;
    vec2 max;
    vec3 color;
};

class Line : public Element {
public:
    Line() : start(0.0f, 0.0f), end(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f) {}

    Line(vec2 _start, vec2 _end, vec3 _color)
        : start(_start), end(_end), color(_color) {}

    void draw(Screen& screen, const ivec2& offset = {0, 0}) override {
        int x0 = static_cast<int>(std::round(start.x + offset.x + position.x));
        int y0 = static_cast<int>(std::round(start.y + offset.y + position.y));
        int x1 = static_cast<int>(std::round(end.x + offset.x + position.x));
        int y1 = static_cast<int>(std::round(end.y + offset.y + position.y));

        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            screen.setPixel(vec2(static_cast<float>(x0), static_cast<float>(y0)), color);

            if (x0 == x1 && y0 == y1) break;

            int err2 = err * 2;
            if (err2 > -dy) { err -= dy; x0 += sx; }
            if (err2 < dx) { err += dx; y0 += sy; }
        }
    }

    // Getters
    vec2 getStart() const { return start; }
    vec2 getEnd() const { return end; }
    vec3 getColor() const { return color; }

    // Setters
    void setStart(const vec2& _start) { start = _start; }
    void setEnd(const vec2& _end) { end = _end; }
    void setColor(const vec3& _color) { color = _color; }

    int getType() const override {
        return 3;
    }

private:
    vec2 start;
    vec2 end;
    vec3 color;
};

class Triangle : public Element {
public:
    Triangle() : p1(0.0f, 0.0f), p2(0.0f, 0.0f), p3(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f) {}

    Triangle(vec2 _p1, vec2 _p2, vec2 _p3, vec3 _color)
        : p1(_p1), p2(_p2), p3(_p3), color(_color) {}

    void draw(Screen& screen, const ivec2& offset = {0, 0}) override {
        float minX = std::floor(std::min({ p1.x, p2.x, p3.x }) + offset.x + position.x);
        float maxX = std::ceil(std::max({ p1.x, p2.x, p3.x }) + offset.x + position.x);
        float minY = std::floor(std::min({ p1.y, p2.y, p3.y }) + offset.y + position.y);
        float maxY = std::ceil(std::max({ p1.y, p2.y, p3.y }) + offset.y + position.y);

        for (int y = static_cast<int>(minY); y <= static_cast<int>(maxY); ++y) {
            for (int x = static_cast<int>(minX); x <= static_cast<int>(maxX); ++x) {
                vec2 pixel(x + 0.5f, y + 0.5f);
                if (inTriangle(pixel, p1, p2, p3)) {
                    screen.setPixel(pixel, color);
                }
            }
        }
    }

    // Getters
    vec2 getP1() const { return p1; }
    vec2 getP2() const { return p2; }
    vec2 getP3() const { return p3; }
    vec3 getColor() const { return color; }

    // Setters
    void setP1(const vec2& _p1) { p1 = _p1; }
    void setP2(const vec2& _p2) { p2 = _p2; }
    void setP3(const vec2& _p3) { p3 = _p3; }
    void setColor(const vec3& _color) { color = _color; }

    int getType() const override {
        return 2;
    }

    bool containsPoint(const vec2& point) const {
        vec2 transformedP1 = p1 + position;
        vec2 transformedP2 = p2 + position;
        vec2 transformedP3 = p3 + position;

        return inTriangle(point, transformedP1, transformedP2, transformedP3);
    }

private:
    vec2 p1, p2, p3;
    vec3 color;

    // Barycentric coordinates
    bool inTriangle(const vec2& p, const vec2& a, const vec2& b, const vec2& c) const {
        float area = triangleArea(a, b, c);
        float area1 = triangleArea(p, b, c);
        float area2 = triangleArea(a, p, c);
        float area3 = triangleArea(a, b, p);
        return (area == area1 + area2 + area3);
    }

    float triangleArea(const vec2& a, const vec2& b, const vec2& c) const {
        return std::abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0f);
    }
};

class Image : public Element {
public:
    Image() : min(0.0f, 0.0f), max(0.0f, 0.0f), rotation(0.0f) {}

    Image(const std::string& filePath, vec2 _min, vec2 _max)
        : min(_min), max(_max), rotation(0.0f) {
        int imgWidth, imgHeight, imgChannels;
        unsigned char* imgData = stbi_load(filePath.c_str(), &imgWidth, &imgHeight, &imgChannels, 4);
        if (imgData) {
            textureSurface = SDL_CreateRGBSurfaceWithFormatFrom(
                imgData, imgWidth, imgHeight, 32, imgWidth * 4, SDL_PIXELFORMAT_RGBA32);
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

    void draw(Screen& screen, const ivec2& offset = {0, 0}) override {
        int x1 = static_cast<int>(std::round(std::min(min.x, max.x) + offset.x));
        int y1 = static_cast<int>(std::round(std::min(min.y, max.y) + offset.y));
        int x2 = static_cast<int>(std::round(std::max(min.x, max.x) + offset.x));
        int y2 = static_cast<int>(std::round(std::max(min.y, max.y) + offset.y));

        SDL_Rect dstRect = { x1, y1, x2 - x1, y2 - y1 };
        SDL_BlitScaled(textureSurface, nullptr, screen.getSurface(), &dstRect);
    }

    int getType() const override {
        return 4;
    }

    void rotate90Degrees() {
        if (!textureSurface) return;

        // Create a new surface for the rotated image
        SDL_Surface* rotatedSurface = SDL_CreateRGBSurfaceWithFormat(
            0, textureSurface->h, textureSurface->w, 32, textureSurface->format->format);
        if (!rotatedSurface) {
            std::cerr << "Failed to create rotated surface.\n";
            return;
        }

        // Rotate pixels 90 degrees
        for (int y = 0; y < textureSurface->h; ++y) {
            for (int x = 0; x < textureSurface->w; ++x) {
                Uint32 pixel = ((Uint32*)textureSurface->pixels)[y * textureSurface->w + x];
                int newX = textureSurface->h - y - 1; // New X coordinate
                int newY = x;                        // New Y coordinate
                ((Uint32*)rotatedSurface->pixels)[newY * rotatedSurface->w + newX] = pixel;
            }
        }

        // Replace the original surface with the rotated surface
        SDL_FreeSurface(textureSurface);
        textureSurface = rotatedSurface;

        return;
    }

    // Getters
    vec2 getMin() const { return min; }
    vec2 getMax() const { return max; }
    float getRotation() const { return rotation; }

    // Setters
    void setMin(const vec2& _min) { min = _min; }
    void setMax(const vec2& _max) { max = _max; }
    void setRotation(float _rotation) { rotation = _rotation; }

private:
    SDL_Surface* textureSurface = nullptr;
    vec2 min;
    vec2 max;
    float rotation;
};

class Button : public Box {
public:
    // Constructor that takes position, size, color, and label
    Button(const vec2& min, const vec2& max, const vec3& color, const std::string& label = "")
        : Box(min, max, color), label(label), id("") {}

    // Override the draw method to include the button label (if any)
    void draw(Screen& screen, const ivec2& offset = {0, 0}) override {
        Box::draw(screen, offset);  // Draw the button as a Box first
        
        // Add label drawing (simple placeholder for text)
        if (!label.empty()) {
        }
    }

    void setId(const std::string& buttonId) { id = buttonId; }
    std::string getId() const { return id; }

    using ClickCallback = std::function<void()>;

    // Button click handler
    bool handleClick(int x, int y) {
        std::cout << x << " " << y << std::endl;
        std::cout << getMin().x << " " << getMin().y << std::endl;
        std::cout << getMax().x << " " << getMax().y << std::endl;
        // Check if the click is within the bounds of the button
        if (x >= min.x && x <= max.x && y >= min.y && y <= max.y) {
            std::cout << "Button at memory address: " << this << " clicked!" << std::endl;
            return true;
        } else {
            return false;
        }
    }

    bool containsPoint(int x, int y) const {
        return (x >= min.x && x <= max.x && y >= min.y && y <= max.y);
    }

    void setOnClick(ClickCallback callback) { onClick = callback; }

    // Getters and Setters for the label
    void setLabel(const std::string& _label) { label = _label; }
    std::string getLabel() const { return label; }

private:
    std::string label;  // Button label (e.g., "Click Me!")
    ClickCallback onClick;
    std::string id;
};

#endif // ELEMENT_HPP