#ifndef GUIFILE_HPP
#define GUIFILE_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "element.hpp"

// Line, Box, Point structure definitions

class GUIFile {
    public:
        void stageLine(const Line& line);
        void stageBox(const Box& box);
        void stageTriangle(const Triangle& triangle);

        void writeFile(const std::string& filename);
        void readFile(const std::string& filename);

        // Getters
        std::vector<Line> getLines() const;
        std::vector<Box> getBoxes() const;
        std::vector<Triangle> getTriangles() const;
        void clear();

    private:
        std::vector<Line> lines;
        std::vector<Box> boxes;
        std::vector<Triangle> triangles;

        // Helper methods for parsing (not exposed to the public)
        void parseVec2(std::ifstream& file, vec2& vec);
        void parseVec3(std::ifstream& file, vec3& vec);

};

#endif // GUIFILE_HPP
