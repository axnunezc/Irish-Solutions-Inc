#include "GUIFile.hpp"

// Stage a line
void GUIFile::stageLine(const Line& line) {
    lines.push_back(line);
}

// Stage a box
void GUIFile::stageBox(const Box& box) {
    boxes.push_back(box);
}

// Stage a point
void GUIFile::stagePoint(const Point& point) {
    points.push_back(point);
}
