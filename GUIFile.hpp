#ifndef GUIFILE_HPP
#define GUIFILE_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "element.hpp"
#include "layout.hpp"

// Line, Box, Point structure definitions

class GUIFile {
    public:
        // void writeFile(const std::string& filename);
        std::vector<std::string> splitString(const std::string& str, char delimiter);
        void readFile(const std::string& filename, Layout& layout);
        void parseLayout(std::ifstream& file, Layout& layout);

    private:
        // Helper methods for parsing (not exposed to the public)
        void parseVec2(std::ifstream& file, vec2& vec);
        void parseVec3(std::ifstream& file, vec3& vec);

};

#endif // GUIFILE_HPP
