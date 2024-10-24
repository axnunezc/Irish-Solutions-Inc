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
        void stageElement(Element* element);

        void writeFile(const std::string& filename);
        void readFile(const std::string& filename);

        // Getters
        std::vector<Element*> getElements() const;
        void clear();

    private:
        std::vector<Element*> elements;

        // Helper methods for parsing (not exposed to the public)
        void parseVec2(std::ifstream& file, vec2& vec);
        void parseVec3(std::ifstream& file, vec3& vec);

};

#endif // GUIFILE_HPP
