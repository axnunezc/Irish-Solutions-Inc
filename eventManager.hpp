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

    void queueEvent(std::unique_ptr<Event> event) {
        eventQueue.push(std::move(event));
    }

    void processEvents() {
        while (!eventQueue.empty()) {
            auto event = std::move(eventQueue.front());
            eventQueue.pop();
        }
    }
};

#endif // EVENTMANAGER_HPP