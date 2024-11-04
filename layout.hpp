#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <vector>
#include <memory>
#include "element.hpp"
#include "screen.hpp"
#include "vec2.hpp"

class Layout {
public:
    Layout(const ivec2& start = {0, 0}, const ivec2& end = {0, 0}, bool isActive = true)
        : startPosition(start), endPosition(end), active(isActive) {}

    void addElement(std::shared_ptr<Element> element) {
        elements.push_back(element);
    }

    void addNestedLayout(std::shared_ptr<Layout> layout) {
        nestedLayouts.push_back(layout);
    }

    void setActive(bool state) {
        active = state;
    }

    void render(Screen& screen) {
        if (!active) return;

        ivec2 space = endPosition - startPosition;

        for (const auto& element : elements) {
            ivec2 elementPosition = element->getPosition() + startPosition;
            element->setPosition(elementPosition);
            element->draw(screen);
            element->setPosition(elementPosition - startPosition);  // Reset position
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

private:
    ivec2 startPosition;
    ivec2 endPosition;
    bool active;

    std::vector<std::shared_ptr<Element>> elements;
    std::vector<std::shared_ptr<Layout>> nestedLayouts;
};

#endif // LAYOUT_HPP
