#include <iostream>
#include "GUIFile.hpp"
#include "screen.hpp"
#include <SDL.h>
#include "element.hpp"
#include "layout.hpp"
#include "EventSystem.hpp"
#include "SoundPlayer.hpp"
#include <unordered_map>
#include <vector>

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
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Screen screen(SCREEN_WIDTH, SCREEN_HEIGHT);

    EventSystem& eventSystem = EventSystem::getInstance();

    std::unordered_map<Layout*, std::vector<Element*>> loadedElements;

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

    Box* boxObj = new Box(vec2(50, 150), vec2(200, 300), vec3(0, 0, 255)); // Blue Box
    layout1.addElement(boxObj);
    loadedElements[&layout1].push_back(boxObj);
    Triangle* triangleObj = new Triangle(vec2(350, 350), vec2(450, 350), vec2(400, 450), vec3(0, 255, 0)); // Green Triangle
    layout1.addElement(triangleObj); // Green triangle
    loadedElements[&layout1].push_back(triangleObj);
    Image* img = new Image("GUIFileUML.png", vec2(0, 200), vec2(300, 500));
    layout2.addElement(img); // Image
    loadedElements[&layout2].push_back(img);

    // Add buttons to the root layout (centered and spaced)
    const int buttonWidth = 100;
    const int buttonHeight = 50;
    const int buttonSpacing = 20;
    const int totalButtonsWidth = 4 * buttonWidth + 3 * buttonSpacing; // Total width occupied by all buttons and spacing
    const int startX = (SCREEN_WIDTH - totalButtonsWidth) / 2; // Center buttons horizontally
    const int startY = 10; // Margin from the top

    Button* greenButton = new Button(vec2(startX, startY), vec2(startX + buttonWidth, startY + buttonHeight), vec3(0, 255, 0), "Green");
    greenButton->setId("greenButton");
    Button* redButton = new Button(vec2(startX + buttonWidth + buttonSpacing, startY), vec2(startX + 2 * buttonWidth + buttonSpacing, startY + buttonHeight), vec3(255, 0, 0), "Red");
    redButton->setId("redButton");
    Button* blueButton = new Button(vec2(startX + 2 * (buttonWidth + buttonSpacing), startY), vec2(startX + 3 * buttonWidth + 2 * buttonSpacing, startY + buttonHeight), vec3(0, 0, 255), "Blue");
    blueButton->setId("blueButton");
    Button* yellowButton = new Button(vec2(startX + 3 * (buttonWidth + buttonSpacing), startY), vec2(startX + 4 * buttonWidth + 3 * buttonSpacing, startY + buttonHeight), vec3(255, 255, 0), "Yellow");
    yellowButton->setId("yellowButton");

    rootLayout.addElement(greenButton);
    rootLayout.addElement(redButton);
    rootLayout.addElement(blueButton);
    rootLayout.addElement(yellowButton);

    loadedElements[&rootLayout].push_back(greenButton);
    loadedElements[&rootLayout].push_back(redButton);
    loadedElements[&rootLayout].push_back(blueButton);
    loadedElements[&rootLayout].push_back(yellowButton);

    // Nest layouts 1 and 2 within the root layout
    rootLayout.addNestedLayout(&layout1);
    rootLayout.addNestedLayout(&layout2);

    eventSystem.setRootLayout(&rootLayout);
    eventSystem.setLayouts(&layout1, &layout2);

    // Create a SoundPlayer instance
    SoundPlayer soundPlayer;

    // Load a sound file
    if (!soundPlayer.loadSound("piano.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
        return 1;
    }

    eventSystem.setSoundPlayer(&soundPlayer);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    EventSystem::getInstance().addEvent(new ClickEvent(event.button.x, event.button.y));
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_c) { // Detect C key press
                    rootLayout.clearElements();
                    for (auto& pair : loadedElements) {
                        Layout* layout = pair.first;
                        std::cout << layout->getStartPosition().x << " " << layout->getStartPosition().y << std::endl;
                        std::cout << layout->getEndPosition().x << " " << layout->getEndPosition().y << std::endl;
                        const auto& elements = pair.second;
                        for (auto element : elements) {
                            layout->addElement(element);
                        }
                    }
                }
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;

                // Update screen size and layout bounds based on new dimensions
                screen = Screen(newWidth, newHeight);
                rootLayout.setBounds(0.0f, 0.0f, 1.0f, 1.0f, {0, 0}, {newWidth, newHeight});
                layout1.setBounds(0.0f, 0.0f, 0.5f, 1.0f, rootLayout.getStartPosition(), rootLayout.getEndPosition());
                layout2.setBounds(0.5f, 0.0f, 1.0f, 1.0f, rootLayout.getStartPosition(), rootLayout.getEndPosition());
            }
        }

        screen.clear();

        // Process all accumulated events
        EventSystem::getInstance().processEvents();

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
