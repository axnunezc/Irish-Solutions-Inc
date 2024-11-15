#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP

#include "event.hpp"
#include "layout.hpp"
#include <memory>

class EventSystem {
public:
    static EventSystem& getInstance() {
        static EventSystem instance;
        return instance;
    }

    void toggleLayout(const std::string& layoutName) {
        if (rootLayout) {
            Layout* targetLayout = findLayout(layoutName, rootLayout);
            if (targetLayout) {
                std::cout << targetLayout->getActive() << std::endl;
                targetLayout->setActive(!(targetLayout->getActive()));
            }
        }
    }

    void setRootLayout(Layout* root) {
        rootLayout = root;
    }

private:
    Layout* rootLayout = nullptr;  // Root layout of the system

    Layout* findLayout(const std::string& layoutName, Layout* layout) {
        if (layout->getName() == layoutName) {
            return layout;
        }

        for (Layout* nestedLayout : layout->getNestedLayouts()) {
            Layout* foundLayout = findLayout(layoutName, nestedLayout);
            if (foundLayout) {
                return foundLayout;
            }
        }

        return nullptr;
    }

    EventSystem() {}  // Private constructor for singleton
};

#endif  // EVENTSYSTEM_HPP