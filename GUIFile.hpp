#ifndef GUIFILE_HPP
#define GUIFILE_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "element.hpp"
#include "elementManager.hpp"

// Line, Box, Point structure definitions

class GUIFile {
    public:
        void writeFile(const std::string& filename);
        void readFile(const std::string& filename);

    private:
        ElementManager& elementManager = ElementManager::getInstance(); 

        // Helper methods for parsing (not exposed to the public)
        void parseVec2(std::ifstream& file, vec2& vec);
        void parseVec3(std::ifstream& file, vec3& vec);

};

#endif // GUIFILE_HPP
