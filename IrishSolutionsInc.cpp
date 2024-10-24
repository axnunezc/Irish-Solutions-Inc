// IrishSolutionsInc.cpp
#include <iostream>
#include "GUIFile.hpp"
#include "screen.hpp"
#include <SDL.h>
#include "element.hpp"  // Include element.hpp for Box and Triangle classes

const int SCREEN_WIDTH = 960;  // Initial screen width
const int SCREEN_HEIGHT = 540; // Initial screen height

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

    // Read in XML file and create line, box, and point elements in GUIFile class
    GUIFile guiFile;
    // guiFile.readFile("shapes.xml");

    // Creating new elements (line, box, triangle, and point)
    Line newLine = { vec2(50, 50), vec2(200, 200), vec3(0, 255, 0) }; // Green line
    Box newBox = { vec2(250, 250), vec2(400, 400), vec3(255, 0, 0) }; // Red box
    Triangle newTriangle = { vec2(300, 100), vec2(350, 200), vec2(250, 200), vec3(0, 0, 255) }; // Blue triangle

    // Stage the new elements
    guiFile.stageLine(newLine);
    guiFile.stageBox(newBox);
    guiFile.stageTriangle(newTriangle);

    // Write new XML file with added elements
    guiFile.writeFile("shapes_out.xml");

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
        for (auto& line : guiFile.getLines()) {
            line.draw(screen); // Use the draw method of the Line class
        }

        // Draw boxes from the GUIFile
        for (auto& box : guiFile.getBoxes()) {
            box.draw(screen); // Use the draw method of the Box class
        }

        // Draw triangles from the GUIFile
        for (auto& triangle : guiFile.getTriangles()) {
            triangle.draw(screen); // Use the draw method of the Triangle class
        }

        // Blit the screen surface to the window surface
        screen.blitTo(screenSurface);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
