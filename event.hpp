#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

enum class EventType { CLICK, SHOW, SOUND };

class Event {
public:
    virtual ~Event() = default;
    virtual EventType getType() const = 0;
};

class ClickEvent : public Event {
    int x, y;
public:
    ClickEvent(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
    EventType getType() const override { return EventType::CLICK; }
    int getX() const { return x; }
    int getY() const { return y; }
};

class ShowEvent : public Event {
    int x, y;
    std::string layoutName;
public:
    ShowEvent(int xCoord, int yCoord, const std::string &name) : x(xCoord), y(yCoord), layoutName(name) {}
    EventType getType() const override { return EventType::SHOW; }
    int getX() const { return x; }
    int getY() const { return y; }
    const std::string& getLayoutName() const { return layoutName; }
};

class SoundEvent : public Event {
    int x, y;
public:
    SoundEvent(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
    EventType getType() const override { return EventType::SOUND; }
    int getX() const { return x; }
    int getY() const { return y; }
};

#endif // EVENT_HPP