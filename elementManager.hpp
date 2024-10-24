#ifndef ELEMENTMANAGER_HPP
#define ELEMENTMANAGER_HPP

#include <vector>
#include <algorithm>
#include "element.hpp"

class ElementManager {
public:
    ElementManager() = default;
    ~ElementManager() {
        // Clean up active elements
        for (Element* elem : elements) {
            delete elem;
        }

        // Clean up pool
        for (Element* elem : elementPool) {
            delete elem;
        }
    }

    void addElement(Element* element) {
        elements.push_back(element);
    }

    // Release an element back to the pool
    void releaseElement(Element* element) {
        auto idx = std::find(elements.begin(), elements.end(), element);
        if (idx != elements.end()) {
            elements.erase(idx);
            elementPool.push_back(element);
        }
    }

    const std::vector<Element*>& getElements() const {
        return elements;
    }

private:
    std::vector<Element*> elements;
    std::vector<Element*> elementPool;

};

#endif // ELEMENTMANAGER_HPP
