#ifndef ELEMENTMANAGER_HPP
#define ELEMENTMANAGER_HPP

#include <vector>
#include <algorithm>
#include "element.hpp"

class ElementManager {
public:
    static ElementManager& getInstance() {
        static ElementManager instance;  // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }

    ElementManager(const ElementManager&) = delete;
    void operator=(const ElementManager&) = delete;

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
    
    std::vector<Element*> elements;
    std::vector<Element*> elementPool;

};

#endif // ELEMENTMANAGER_HPP
