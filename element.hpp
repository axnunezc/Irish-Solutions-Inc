// element.hpp
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "screen.hpp"
#include "stb_image.h"
#include "event.hpp"

class Element {
public:
    virtual ~Element() = default;
    virtual void draw(Screen& screen, const ivec2& offset = {0, 0}) = 0;

    // Getter and setter for position
    vec2 getPosition() const { return position; }
    void setPosition(const vec2& newPosition) { position = newPosition; }

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

private:
    vec2 p1, p2, p3;
    vec3 color;

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

    void draw(Screen& screen, const ivec2& offset = {0, 0}) override {
        SDL_Rect dstRect = { static_cast<int>(position.x + offset.x), static_cast<int>(position.y + offset.y), static_cast<int>(textureSurface->w * scale), static_cast<int>(textureSurface->h * scale) };
        SDL_BlitSurface(textureSurface, nullptr, screen.getSurface(), &dstRect);
    }

    // Getters
    vec2 getPosition() const { return position; }
    float getScale() const { return scale; }
    float getRotation() const { return rotation; }

    // Setters
    void setPosition(const vec2& newPosition) { position = newPosition; }
    void setScale(float newScale) { scale = newScale; }
    void setRotation(float newRotation) { rotation = newRotation; }

private:
    SDL_Surface* textureSurface;
    vec2 position;
    float scale;
    float rotation;
};

class Button : public Box {
public:
    // Constructor that takes position, size, color, and label
    Button(const vec2& min, const vec2& max, const vec3& color, const std::string& label = "")
        : Box(min, max, color), label(label) {}

    // Override the draw method to include the button label (if any)
    void draw(Screen& screen, const ivec2& offset = {0, 0}) override {
        Box::draw(screen, offset);  // Draw the button as a Box first
        
        // Add label drawing (simple placeholder for text)
        if (!label.empty()) {
        }
    }

    using ClickCallback = std::function<void()>;

    // Button click handler
    void handleClick(int x, int y) {
        // Check if the click is within the bounds of the button
        if (x >= min.x && x <= max.x && y >= min.y && y <= max.y) {
            std::cout << "Button at memory address: " << this << " clicked!" << std::endl;
            if (onClick) {
                onClick();
            }
        }
    }

    void setOnClick(ClickCallback callback) { onClick = callback; }

    // Getters and Setters for the label
    void setLabel(const std::string& _label) { label = _label; }
    std::string getLabel() const { return label; }

private:
    std::string label;  // Button label (e.g., "Click Me!")
    ClickCallback onClick;
};

#endif // ELEMENT_HPP