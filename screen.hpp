// #include <SDL2/SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "matrix.hpp"

class Screen {
    private:
        unsigned int width, height;
        SDL_Surface* surface;

    public:
        // Color a single pixel
        void setPixel(const ivec2& pos, const ivec3& color) {
            if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) {
                uint32_t* pixels = (uint32_t*)surface->pixels;
                uint32_t pixelColor = SDL_MapRGB(surface->format, color.x, color.y, color.z);
                pixels[pos.y * width + pos.x] = pixelColor;
            }
        }

        // Blit to other surface
        void blitTo(SDL_Surface* other) {
        SDL_BlitSurface(surface, nullptr, other, nullptr);
    }
};