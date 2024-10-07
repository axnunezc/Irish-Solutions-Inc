// IrishSolutionsInc.cpp
#include <iostream>
#include "GUIFile.hpp"
#include "screen.hpp"
#include <SDL.h>

const int SCREEN_WIDTH = 960;  // Initial screen width
const int SCREEN_HEIGHT = 540; // Initial screen height

void drawBresenhamLines(Screen& screen, vec2 center, vec3 color) {
    // Get screen corners
    vec2 topLeft(0, 0);
    vec2 topRight(screen.getWidth() - 1, 0);
    vec2 bottomLeft(0, screen.getHeight() - 1);
    vec2 bottomRight(screen.getWidth() - 1, screen.getHeight() - 1);

    // Draw lines
    screen.drawLine(center, topLeft, color);
    screen.drawLine(center, topRight, color);
    screen.drawLine(center, bottomLeft, color);
    screen.drawLine(center, bottomRight, color);
}

void drawCenterBox(Screen& screen, vec2 center, vec3 color) {
    // Get box dimensions
    float boxWidth = screen.getWidth() / 3.0f;
    float boxHeight = screen.getHeight() / 3.0f;

    // Get box corners
    vec2 topLeft(center.x - boxWidth / 2, center.y - boxHeight / 2);
    vec2 bottomRight(center.x + boxWidth / 2, center.y + boxHeight / 2);

    // Draw box
    screen.drawBox(topLeft, bottomRight, color);
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Test Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    Screen screen(SCREEN_WIDTH, SCREEN_HEIGHT);

    GUIFile guiFile;
    guiFile.readFile("shapes.xml");

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;

                screen = Screen(newWidth, newHeight);
            }
        }

        // Set screen color to gray
        SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 128, 128, 128));

        // Draw lines from the GUIFile
        for (const auto& line : guiFile.getLines()) {
            screen.drawLine(line.startPos, line.endPos, line.color);
        }

        // Draw boxes from the GUIFile
        for (const auto& box : guiFile.getBoxes()) {
            screen.drawBox(box.minBounds, box.maxBounds, box.color);
        }

        // Draw points from the GUIFile
        for (const auto& point : guiFile.getPoints()) {
            screen.setPixel(point.position, point.color);
        }

        // Blit the screen surface to the window surface
        screen.blitTo(screenSurface);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
