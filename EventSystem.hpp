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

    void setLayouts(Layout* l1, Layout* l2) {
        layout1 = l1;
        layout2 = l2;
    }

private:
    void handleClickEvent(ClickEvent* event) {
        if (!rootLayout) return;

        // Check if any element in the root layout is clicked
        std::vector<Element*> elements = rootLayout->getElements();
        for (Element* element : elements) {
            if (auto* button = dynamic_cast<Button*>(element)) {
                if (button->containsPoint(event->getX(), event->getY())) {
                    if (button->getId() == "greenButton") {
                        if (soundPlayer) {
                            soundPlayer->playSound();
                            std::cout << "Sound played after pressing green button" << std::endl;
                        }
                        return;
                    } else if (button->getId() == "redButton") {
                        for (Element* layoutElement : elements) {
                            if (auto* image = dynamic_cast<Image*>(layoutElement)) {
                                image->rotate90Degrees();
                                return; // Stop after rotating the first image
                            }
                        }
                    } else if (button->getId() == "blueButton") {
                        toggleLayouts();
                        std::cout << "Toggling" << std::endl;
                        return;
                    } else if (button->getId() == "yellowButton") {
                        generateRandomShape();
                        return;
                    }
                }
            }
        }
    }

    void toggleLayouts() {
        if (!layout1 || !layout2) return;

        if (layoutsSplit) {
            std::cout << "Hidden" << std::endl;
            layout2->setActive(false);
            layout1->setBounds(0.0f, 0.0f, 1.0f, 1.0f, rootLayout->getStartPosition(), rootLayout->getEndPosition());
            for (auto& element : layout1->getElements()) {
                // Check if the element is a Box
                if (auto* box = dynamic_cast<Box*>(element)) {
                    vec2 min = box->getMin();
                    vec2 max = box->getMax();
                    min.x *= 2;
                    max.x *= 2;
                    box->setMin(min);
                    box->setMax(max);
                }

                if (auto* line = dynamic_cast<Line*>(element)) {
                    vec2 start = line->getStart();
                    vec2 end = line->getEnd();
                    start.x *= 2;
                    end.x *= 2; 
                    line->setStart(start);
                    line->setEnd(end); 
                }

                if (auto* triangle = dynamic_cast<Triangle*>(element)) {
                    vec2 p1 = triangle->getP1();
                    vec2 p2 = triangle->getP2();
                    vec2 p3 = triangle->getP3();
                    p1.x *= 2;
                    p2.x *= 2; 
                    p3.x *= 2;
                    triangle->setP1(p1);
                    triangle->setP2(p2);
                    triangle->setP3(p3);
                }
            }
        } else {
            std::cout << "Shown" << std::endl;
            layout2->setActive(true);
            layout1->setBounds(0.0f, 0.0f, 0.5f, 1.0f, rootLayout->getStartPosition(), rootLayout->getEndPosition());
            layout2->setBounds(0.5f, 0.0f, 1.0f, 1.0f, rootLayout->getStartPosition(), rootLayout->getEndPosition());
            for (auto& element : layout1->getElements()) {
                // Check if the element is a Box
                if (auto* box = dynamic_cast<Box*>(element)) {
                    vec2 min = box->getMin();
                    vec2 max = box->getMax();
                    min.x /= 2;
                    max.x /= 2;
                    box->setMin(min);
                    box->setMax(max);
                }

                if (auto* line = dynamic_cast<Line*>(element)) {
                    vec2 start = line->getStart();
                    vec2 end = line->getEnd();
                    start.x /= 2;
                    end.x /= 2; 
                    line->setStart(start);
                    line->setEnd(end); 
                }

                if (auto* triangle = dynamic_cast<Triangle*>(element)) {
                    vec2 p1 = triangle->getP1();
                    vec2 p2 = triangle->getP2();
                    vec2 p3 = triangle->getP3();
                    p1.x /= 2;
                    p2.x /= 2; 
                    p3.x /= 2;
                    triangle->setP1(p1);
                    triangle->setP2(p2);
                    triangle->setP3(p3);
                }
            }
        }

        layoutsSplit = !layoutsSplit; // Toggle the state
    }

    void generateRandomShape() {
        // Define random generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> layoutDist(1, 2); // Choose layout
        std::uniform_int_distribution<int> shapeDist(1, 2);  // Choose shape (1: Box, 2: Triangle)
        std::uniform_int_distribution<float> posDist(0, 450);  // Random position (adjust range as needed)
        std::uniform_int_distribution<float> colorDist(0, 255); // Random RGB values

        // Select layout
        Layout* targetLayout = (layoutDist(gen) == 1) ? layout1 : layout2;

        // Select shape type
        int shapeType = shapeDist(gen);

        // Generate random color
        float r = colorDist(gen);
        float g = colorDist(gen);
        float b = colorDist(gen);

        // Generate random positions
        vec2 start = {posDist(gen), posDist(gen) + 100};
        vec2 end = {posDist(gen), posDist(gen) + 100};
        vec2 max = {start.x + posDist(gen), start.y + posDist(gen) + 100}; // Size limit for Box
        vec2 v1 = {start.x, start.y + 100};
        vec2 v2 = {start.x + posDist(gen), start.y + 100}; // Create Triangle vertices
        vec2 v3 = {start.x, start.y + posDist(gen) + 100};

        // Create the shape and add it to the layout
        switch (shapeType) {
            case 1: { // Box
                auto* box = new Box(start, max, {r, g, b});
                targetLayout->addElement(box);
                std::cout << "Random Box added to layout" << std::endl;
                break;
            }
            case 2: { // Triangle
                auto* triangle = new Triangle(v1, v2, v3, {r, g, b});
                targetLayout->addElement(triangle);
                std::cout << "Random Triangle added to layout" << std::endl;
                break;
            }
        }
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
    bool layoutsSplit = true;
    Layout* layout1 = nullptr;
    Layout* layout2 = nullptr;
    int screenWidth = 960;
    int screenHeight = 540;
};

#endif  // EVENTSYSTEM_HPP