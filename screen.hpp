// #include <SDL2/SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "matrix.hpp"

class Screen {
    private:
        unsigned int width, height;
        SDL_Surface* surface;

    public:
        // Class constructor
        Screen(unsigned int _width, unsigned int _height) : width(_width), height(_height) {
            surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
            if (!surface) {
                std::cerr << "Failed to create SDL surface: " << SDL_GetError() << std::endl;
            }
        }

        // Class destructor
        ~Screen() {
            if (surface) {
                SDL_FreeSurface(surface);
            }
        }

        // Color a single pixel
        void setPixel(const vec2& pos, const vec3& color) {
            int x = static_cast<int>(std::round(position.x));
            int y = static_cast<int>(std::round(position.y));

            Uint8 r = static_cast<Uint8>(std::round(color.x));
            Uint8 g = static_cast<Uint8>(std::round(color.y));
            Uint8 b = static_cast<Uint8>(std::round(color.z));

            if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight) {
                return; // Out of bounds, do nothing
            }

            Uint32* pixels = (Uint32*)surface->pixels;
            Uint32 pixelColor = SDL_MapRGB(surface->format, r, g, b);
            pixels[y * (surface->pitch / 4) + x] = pixelColor;
        }

        // Line Drawing
        void drawLine(vec2 start, vec2 end, vec3 color) {
            int x1 = static_cast<int>(std::round(start.x));
            int y1 = static_cast<int>(std::round(start.y));
            int x2 = static_cast<int>(std::round(end.x));
            int y2 = static_cast<int>(std::round(end.y));

            int dx = std::abs(x2 - x1);
            int dy = std::abs(y2 - y1);
            int sx = (x1 < x2) ? 1 : -1;
            int sy = (y1 < y2) ? 1 : -1;
            int err = dx - dy;

            while (true) {
                setPixel({x1, y1}, color);

                if (x1 == x2 && y1 == y2) break;
                int e2 = err * 2;
                if (e2 > -dy) {
                    err -= dy;
                    x1 += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y1 += sy;
                }
            }
        }

        // Box Drawing
        void drawBox(vec2 min, vec2 max, vec3 color) {
            int x1 = static_cast<int>(std::round(std::min(min.x, max.x)));
            int y1 = static_cast<int>(std::round(std::min(min.y, max.y)));
            int x2 = static_cast<int>(std::round(std::max(min.x, max.x)));
            int y2 = static_cast<int>(std::round(std::max(min.y, max.y)));

            for (int x = x1; x <= x2; ++x) {
                setPixel({x, y1}, color);
                setPixel({x, y2}, color);
            }

            for (int y = y1; y <= y2; ++y) {
                setPixel({x1, y}, color);
                setPixel({x2, y}, color);
            }
        }

        // Blit to other surface
        void blitTo(SDL_Surface* other) {
        SDL_BlitSurface(surface, nullptr, other, nullptr);
    }
};