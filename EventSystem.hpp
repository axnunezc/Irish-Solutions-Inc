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

    // void dispatchEvent(Event* event) {
    //     rootLayout->updateEvent(event);
    // }

    void setRootLayout(Layout* root) {
        rootLayout = root;
    }

private:
    Layout* rootLayout = nullptr;  // Root layout of the system

    EventSystem() {}  // Private constructor for singleton
};

#endif  // EVENTSYSTEM_HPP