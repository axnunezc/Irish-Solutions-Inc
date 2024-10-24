#include "GUIFile.hpp"

// Write an XML file from stored data
void GUIFile::writeFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    file << "<layout>\n";
    
    // // Writing lines
    // for (const auto& line : lines) {
    //     file << "  <line>\n";
    //     file << "    <vec2>\n";
    //     file << "      <x>" << line.start.x << "</x>\n";
    //     file << "      <y>" << line.start.y << "</y>\n";
    //     file << "    </vec2>\n";
    //     file << "    <vec2>\n";
    //     file << "      <x>" << line.end.x << "</x>\n";
    //     file << "      <y>" << line.end.y << "</y>\n";
    //     file << "    </vec2>\n";
    //     file << "    <vec3>\n";
    //     file << "      <x>" << line.color.x << "</x>\n";
    //     file << "      <y>" << line.color.y << "</y>\n";
    //     file << "      <z>" << line.color.z << "</z>\n";
    //     file << "    </vec3>\n";
    //     file << "  </line>\n";
    // }

    // // Writing boxes
    // for (const auto& box : boxes) {
    //     file << "  <box>\n";
    //     file << "    <vec2>\n";
    //     file << "      <x>" << box.min.x << "</x>\n";
    //     file << "      <y>" << box.min.y << "</y>\n";
    //     file << "    </vec2>\n";
    //     file << "    <vec2>\n";
    //     file << "      <x>" << box.max.x << "</x>\n";
    //     file << "      <y>" << box.max.y << "</y>\n";
    //     file << "    </vec2>\n";
    //     file << "    <vec3>\n";
    //     file << "      <x>" << box.color.x << "</x>\n";
    //     file << "      <y>" << box.color.y << "</y>\n";
    //     file << "      <z>" << box.color.z << "</z>\n";
    //     file << "    </vec3>\n";
    //     file << "  </box>\n";
    // }
    
    file << "</layout>\n";
    file.close();
}

// Read in XML File
void GUIFile::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("<line>") != std::string::npos) {
            Line* lineObj = new Line();
            parseVec2(file, lineObj->start);
            parseVec2(file, lineObj->end);
            parseVec3(file, lineObj->color);
            elementManager.addElement(lineObj);
        }
        else if (line.find("<box>") != std::string::npos) {
            Box* boxObj = new Box();
            parseVec2(file, boxObj->min);
            parseVec2(file, boxObj->max);
            parseVec3(file, boxObj->color);
            elementManager.addElement(boxObj);
        }
    }
    file.close();
}

// Trim whitespace
std::string trim(const std::string& str) {
    const auto begin = str.find_first_not_of(' ');
    if (begin == std::string::npos) return "";
    const auto end = str.find_last_not_of(' ');
    return str.substr(begin, end - begin + 1);
}

void GUIFile::parseVec2(std::ifstream& file, vec2& vec) {
    std::string line;

    // Parsing the x value
    while (line.find("<x>") == std::string::npos) {
        std::getline(file, line);
    }
    if (line.empty()) {
        std::cerr << "Error: Expected <x> tag but got empty line.\n";
        return;
    }

    if (line.find("<x>") != std::string::npos) {
        std::size_t xStart = line.find('x') + 2;
        std::size_t xEnd = line.find("</x>");
        std::string xContent = "";
        if (xEnd == std::string::npos) {
            // Closing tag on separate line
            std::getline(file, line);
            xContent = trim(line);
            std::getline(file, line); // Consume the </x> line
        } else {
            // Closing tag on same line
            xContent = line.substr(xStart, xEnd - xStart);
            xContent = trim(xContent);
        }
        std::cout << "Vec2 x content: '" << xContent << "'\n";
        try {
            vec.x = std::stof(xContent);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting x to float: " << e.what() << "\n";
            return;
        }
    }

    // Parsing the y value
    while (line.find("<y>") == std::string::npos) {
        std::getline(file, line);
    }
    if (line.empty()) {
        std::cerr << "Error: Expected <y> tag but got empty line.\n";
        return;
    }

    if (line.find("<y>") != std::string::npos) {
        std::size_t yStart = line.find('y') + 2;
        std::size_t yEnd = line.find("</y>");
        std::string yContent = "";
        if (yEnd == std::string::npos) {
            // Closing tag on separate line
            std::getline(file, line);
            yContent = trim(line);
            std::getline(file, line); // Consume the </y> line
        } else {
            // Closing tag on same line
            yContent = line.substr(yStart, yEnd - yStart);
            yContent = trim(yContent);
        }
        std::cout << "Vec2 y content: '" << yContent << "'\n";
        try {
            vec.y = std::stof(yContent);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting y to float: " << e.what() << "\n";
            return;
        }
    }
}

void GUIFile::parseVec3(std::ifstream& file, vec3& vec) {
    std::string line;

    // Parsing the x value
    while (line.find("<x>") == std::string::npos) {
        std::getline(file, line);
    }
    if (line.empty()) {
        std::cerr << "Error: Expected <x> tag but got empty line.\n";
        return;
    }

    if (line.find("<x>") != std::string::npos) {
        std::size_t xStart = line.find('x') + 2;
        std::size_t xEnd = line.find("</x>");
        std::string xContent = "";
        if (xEnd == std::string::npos) {
            // Closing tag on separate line
            std::getline(file, line);
            xContent = trim(line);
            std::getline(file, line); // Consume the </x> line
        } else {
            // Closing tag on same line
            xContent = line.substr(xStart, xEnd - xStart);
            xContent = trim(xContent);
        }
        std::cout << "Vec3 x content: '" << xContent << "'\n";
        try {
            vec.x = std::stof(xContent);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting x to float: " << e.what() << "\n";
            return;
        }
    }

    // Parsing the y value
    while (line.find("<y>") == std::string::npos) {
        std::getline(file, line);
    }
    if (line.empty()) {
        std::cerr << "Error: Expected <y> tag but got empty line.\n";
        return;
    }

    if (line.find("<y>") != std::string::npos) {
        std::size_t yStart = line.find('y') + 2;
        std::size_t yEnd = line.find("</y>");
        std::string yContent = "";
        if (yEnd == std::string::npos) {
            // Closing tag on separate line
            std::getline(file, line);
            yContent = trim(line);
            std::getline(file, line); // Consume the </y> line
        } else {
            // Closing tag on same line
            yContent = line.substr(yStart, yEnd - yStart);
            yContent = trim(yContent);
        }
        std::cout << "Vec3 y content: '" << yContent << "'\n";
        try {
            vec.y = std::stof(yContent);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting y to float: " << e.what() << "\n";
            return;
        }
    }

    // Parsing the z value
    while (line.find("<z>") == std::string::npos) {
        std::getline(file, line);
    }
    if (line.empty()) {
        std::cerr << "Error: Expected <z> tag but got empty line.\n";
        return;
    }

    if (line.find("<z>") != std::string::npos) {
        std::size_t zStart = line.find('z') + 2;
        std::size_t zEnd = line.find("</z>");
        std::string zContent = "";
        if (zEnd == std::string::npos) {
            // Closing tag on separate line
            std::getline(file, line);
            zContent = trim(line);
            std::getline(file, line); // Consume the </z> line
        } else {
            // Closing tag on same line
            zContent = line.substr(zStart, zEnd - zStart);
            zContent = trim(zContent);
        }
        std::cout << "Vec3 z content: '" << zContent << "'\n";
        try {
            vec.z = std::stof(zContent);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting z to float: " << e.what() << "\n";
            return;
        }
    }
}
