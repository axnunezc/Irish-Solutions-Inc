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

private:
    ivec2 startPosition;
    ivec2 endPosition;
    bool active;

    std::vector<std::shared_ptr<Element>> elements;
    std::vector<std::shared_ptr<Layout>> nestedLayouts;
};

#endif // LAYOUT_HPP
