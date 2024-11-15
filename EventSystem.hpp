#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP

#include "event.hpp"
#include "layout.hpp"
#include "SoundPlayer.hpp"
#include <memory>

class EventSystem {
public:
    static EventSystem& getInstance() {
        static EventSystem instance;
        return instance;
    }

    void addEvent(Event* event) {
        events.push_back(event);
    }

    void processEvents() {
        for (auto& event : events) {
            if (event->getType() == EventType::CLICK) {
                handleClickEvent(dynamic_cast<ClickEvent*>(event));
            } else if (event->getType() == EventType::SHOW) {
                handleShowEvent(dynamic_cast<ShowEvent*>(event));
            } else if (event->getType() == EventType::SOUND) {
                handleSoundEvent(dynamic_cast<SoundEvent*>(event));
            }
        }
        events.clear();
    }

    void toggleLayout(const std::string& layoutName) {
        if (rootLayout) {
            Layout* targetLayout = findLayout(layoutName, rootLayout);
            if (targetLayout) {
                targetLayout->setActive(!(targetLayout->getActive()));
            }
        }
    }

    void setRootLayout(Layout* root) {
        rootLayout = root;
    }

    void setSoundPlayer(SoundPlayer* player) {
        soundPlayer = player;
    }

    Layout* getRootLayout() const {
        return rootLayout;
    }

    SoundPlayer* getSoundPlayer() const {
        return soundPlayer;
    }

private:
    void handleClickEvent(ClickEvent* event) {
        rootLayout->handleClickEvent(event->getX(), event->getY());
    }

    void handleShowEvent(ShowEvent* event) {
        rootLayout->handleShowEvent(event->getLayoutName());
    }

    void handleSoundEvent(SoundEvent* event) {
        soundPlayer->playSound();
    }

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

    EventSystem() {}
    std::vector<Event*> events;
    Layout* rootLayout;
    SoundPlayer* soundPlayer;
};

#endif  // EVENTSYSTEM_HPP