#include <iostream>
#include "GUIFile.hpp"
#include "screen.hpp"
#include <SDL.h>
#include "element.hpp"
#include "layout.hpp"
#include "EventSystem.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

    EventSystem& eventSystem = EventSystem::getInstance();

    // Root layout covering the entire screen
    Layout rootLayout("RootLayout");
    rootLayout.setActive(true);
    rootLayout.setBounds(0.0f, 0.0f, 1.0f, 1.0f, {0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT});

    // Define Layouts 1 and 2 as sub-regions within rootLayout
    Layout layout1("LeftLayout");
    layout1.setActive(true);
    layout1.setBounds(0.0f, 0.0f, 0.5f, 1.0f, rootLayout.getStartPosition(), rootLayout.getEndPosition()); // Left half

    Layout layout2("RightLayout");
    layout2.setActive(true);
    layout2.setBounds(0.5f, 0.0f, 1.0f, 1.0f, rootLayout.getStartPosition(), rootLayout.getEndPosition()); // Right half

    // Define Nested Layout (layout3) within layout1
    Layout layout3("NestedLayout");
    layout3.setActive(true);
    layout3.setBounds(0.1f, 0.1f, 0.9f, 0.9f, layout1.getStartPosition(), layout1.getEndPosition());

    // Add elements to layout1
    layout1.addElement(new Box(vec2(50, 50), vec2(200, 200), vec3(0, 0, 255))); // Blue box
    layout1.addElement(new Line(vec2(50, 250), vec2(200, 250), vec3(0, 255, 0))); // Green line
    layout1.addElement(new Triangle(vec2(100, 300), vec2(150, 400), vec2(50, 400), vec3(255, 255, 255))); // White triangle
    Button* button = new Button(vec2(100, 300), vec2(200, 500), vec3(0, 0, 0),  "Click Me!");
    button->setOnClick([]() {
        EventSystem::getInstance().addEvent(new ShowEvent("NestedLayout"));
    });
    layout1.addElement(button);

    // Add elements to layout2
    layout2.addElement(new Box(vec2(100, 100), vec2(300, 300), vec3(255, 0, 0))); // Red box
    layout2.addElement(new Line(vec2(400, 400), vec2(600, 200), vec3(255, 255, 0))); // Yellow line
    layout2.addElement(new Triangle(vec2(600, 100), vec2(650, 200), vec2(550, 200), vec3(0, 255, 255))); // Cyan triangle

    // Add elements to layout3
    layout3.addElement(new Box(vec2(20, 20), vec2(120, 120), vec3(128, 0, 128))); // Purple box
    layout3.addElement(new Line(vec2(30, 130), vec2(130, 130), vec3(128, 128, 0))); // Olive line

    // Nest layout3 within layout1
    layout1.addNestedLayout(&layout3);

    // // Nest layouts 1 and 2 within the root layout
    rootLayout.addNestedLayout(&layout1);
    rootLayout.addNestedLayout(&layout2);

    eventSystem.setRootLayout(&rootLayout);

    // Read in XML file
    GUIFile guiFile;
    guiFile.readFile("shapes.xml", rootLayout);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    EventSystem::getInstance().addEvent(new ClickEvent(event.button.x, event.button.y));
                    EventSystem::getInstance().addEvent(new ShowEvent("NestedLayout"));
                    EventSystem::getInstance().addEvent(new SoundEvent());
                }
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;

                // Update screen size and layout bounds based on new dimensions
                screen = Screen(newWidth, newHeight);
                rootLayout.setBounds(0.0f, 0.0f, 1.0f, 1.0f, {0, 0}, {newWidth, newHeight});
                layout1.setBounds(0.0f, 0.0f, 0.5f, 1.0f, rootLayout.getStartPosition(), rootLayout.getEndPosition());
                layout2.setBounds(0.5f, 0.0f, 1.0f, 1.0f, rootLayout.getStartPosition(), rootLayout.getEndPosition());
                layout3.setBounds(0.1f, 0.1f, 0.9f, 0.9f, layout1.getStartPosition(), layout1.getEndPosition());
            }
        }

        // Process all accumulated events
        EventSystem::getInstance().processEvents();

        // Set screen color to gray
        SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 128, 128, 128));

        // Render elements from the root layout, which includes layout1 and layout2
        rootLayout.render(screen);

        // Blit the screen surface to the window surface
        screen.blitTo(screenSurface);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
