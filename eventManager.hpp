#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <memory>
#include <queue>
#include "Event.hpp"

class EventManager {
    static EventManager* instance;
    std::queue<std::unique_ptr<Event>> eventQueue;

    EventManager() = default;

public:
    static EventManager* getInstance() {
        if (!instance) instance = new EventManager();
        return instance;
    }
};

#endif // EVENTMANAGER_HPP