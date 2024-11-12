#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

enum class EventType { CLICK, SHOW, SOUND };

class Event {
public:
    virtual ~Event() = default;
    virtual EventType getType() const = 0;
};

#endif // EVENT_HPP