#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <vector>
#include <memory>
#include "element.hpp"
#include "screen.hpp"
#include "vec2.hpp"

class Layout {
public:
    // Default constructor
    Layout() : startPosition({0, 0}), endPosition({0, 0}), active(true), name("") {}

    // Constructor with full parameters
    Layout(const ivec2& start, const ivec2& end, bool isActive, const std::string& layoutName = "")
        : startPosition(start), endPosition(end), active(isActive), name(layoutName) {}

    // Constructor for name-only layouts
    Layout(const std::string& layoutName) : name(layoutName) {}

    std::string getName() const { return name; }

    void addElement(Element* element) {
        elements.push_back(element);
    }

    void addNestedLayout(Layout* layout) {
        nestedLayouts.push_back(layout);
    }

    void setActive(bool state) {
        active = state;
    }

    std::vector<Layout*> getNestedLayouts() const { return nestedLayouts; }

    bool getActive() const { return active; }

    std::vector<Element*> getElements() {
        std::vector<Element*> allElements;

        // Add the elements from this layout
        allElements.insert(allElements.end(), elements.begin(), elements.end());

        // Recursively add elements from nested layouts
        for (const auto& nestedLayout : nestedLayouts) {
            std::vector<Element*> nestedElements = nestedLayout->getElements();
            allElements.insert(allElements.end(), nestedElements.begin(), nestedElements.end());
        }

        return allElements;
    }

    void printLayoutElements() const {
        std::cout << "Layout elements for Layout at address: " << this << std::endl;
        std::cout << "Start Position: (" << startPosition.x << ", " << startPosition.y << ")" << std::endl;
        std::cout << "End Position: (" << endPosition.x << ", " << endPosition.y << ")" << std::endl;
        std::cout << "Active: " << (active ? "true" : "false") << std::endl;

        std::cout << "Direct elements in this layout:" << std::endl;
        for (const auto& element : elements) {
            std::cout << " - Element at address: " << element << std::endl;
        }

        std::cout << "Nested layouts in this layout:" << std::endl;
        for (const auto& nestedLayout : nestedLayouts) {
            std::cout << "**NESTED**" << std::endl;
            nestedLayout->printLayoutElements();
        }
        std::cout << "End of elements for Layout at address: " << this << std::endl;
    }

    void render(Screen& screen) {
        if (!active) {
            return;
        };

        ivec2 space = endPosition - startPosition;

        for (const auto& element : elements) {
            element->draw(screen, startPosition);
        }

        // Render nested layouts
        for (const auto& layout : nestedLayouts) {
            layout->render(screen);
        }
    }

    void setBounds(float sX, float sY, float eX, float eY, const ivec2& parentStart, const ivec2& parentEnd) {
        ivec2 parentSpace = parentEnd - parentStart;
        startPosition = parentStart + ivec2(static_cast<int>(sX * parentSpace.x), static_cast<int>(sY * parentSpace.y));
        endPosition = parentStart + ivec2(static_cast<int>(eX * parentSpace.x), static_cast<int>(eY * parentSpace.y));

        for (const auto& layout : nestedLayouts) {
            layout->setBounds(sX, sY, eX, eY, startPosition, endPosition);
        }
    }

    ivec2 getStartPosition() const { return startPosition; }
    ivec2 getEndPosition() const { return endPosition; }

    void handleClickEvent(int x, int y) {
        for (auto& element : elements) {
            Button* button = dynamic_cast<Button*>(element);
            if (button) {
                button->handleClick(x, y);
            }
        }

        for (const auto& layout : nestedLayouts) {
            layout->handleClickEvent(x, y);
        }
    }

    void handleShowEvent(const std::string& layoutName) {
        if (name == layoutName) {
            active = !active;
        } else {
            for (const auto& nestedLayout : nestedLayouts) {
                nestedLayout->handleShowEvent(layoutName);
            }
        }
    }

private:
    ivec2 startPosition;
    ivec2 endPosition;
    bool active;
    std::string name;

    std::vector<Element*> elements;
    std::vector<Layout*> nestedLayouts;
};

#endif // LAYOUT_HPP
