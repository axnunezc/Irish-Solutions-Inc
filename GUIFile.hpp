#ifndef GUIFILE_HPP
#define GUIFILE_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"

// Line, Box, Point structure definitions
struct Line {
    vec2 startPos;
    vec2 endPos;
    vec3 color;
};

struct Box {
    vec2 minBounds;
    vec2 maxBounds;
    vec3 color;
};

struct Point {
    vec2 position;
    vec3 color;
};

class GUIFile {
    public:
        void stageLine(const Line& line);
        void stageBox(const Box& box);
        void stagePoint(const Point& point);

        void writeFile(const std::string& filename);
        void readFile(const std::string& filename);

        // Getters
        std::vector<Line> getLines() const;
        std::vector<Box> getBoxes() const;
        std::vector<Point> getPoints() const;
        void clear();

    private:
        std::vector<Line> lines;
        std::vector<Box> boxes;
        std::vector<Point> points;

        // Helper methods for parsing (not exposed to the public)
        void parseVec2(std::ifstream& file, vec2& vec);
        void parseVec3(std::ifstream& file, vec3& vec);

};

#endif // GUIFILE_HPP
