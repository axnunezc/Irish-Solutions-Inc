#include "GUIFile.hpp"

// // Write an XML file from stored data
// void GUIFile::writeFile(const std::string& filename) {
//     std::ofstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Failed to open file for writing: " << filename << "\n";
//         return;
//     }

//     file << "<layout>\n";

//     // Iterate through elements and write based on their type
//     for (const auto& element : rootLayout.getElements()) {
//         if (Line* line = dynamic_cast<Line*>(element)) {
//             file << "  <line>\n";
//             file << "    <vec2>\n";
//             file << "      <x>" << line->getStart().x << "</x>\n";
//             file << "      <y>" << line->getStart().y << "</y>\n";
//             file << "    </vec2>\n";
//             file << "    <vec2>\n";
//             file << "      <x>" << line->getEnd().x << "</x>\n";
//             file << "      <y>" << line->getEnd().y << "</y>\n";
//             file << "    </vec2>\n";
//             file << "    <vec3>\n";
//             file << "      <x>" << line->getColor().x << "</x>\n";
//             file << "      <y>" << line->getColor().y << "</y>\n";
//             file << "      <z>" << line->getColor().z << "</z>\n";
//             file << "    </vec3>\n";
//             file << "  </line>\n";
//         } else if (Box* box = dynamic_cast<Box*>(element)) {
//             file << "  <box>\n";
//             file << "    <vec2>\n";
//             file << "      <x>" << box->getMin().x << "</x>\n";
//             file << "      <y>" << box->getMin().y << "</y>\n";
//             file << "    </vec2>\n";
//             file << "    <vec2>\n";
//             file << "      <x>" << box->getMax().x << "</x>\n";
//             file << "      <y>" << box->getMax().y << "</y>\n";
//             file << "    </vec2>\n";
//             file << "    <vec3>\n";
//             file << "      <x>" << box->getColor().x << "</x>\n";
//             file << "      <y>" << box->getColor().y << "</y>\n";
//             file << "      <z>" << box->getColor().z << "</z>\n";
//             file << "    </vec3>\n";
//             file << "  </box>\n";
//         } else if (Triangle* triangle = dynamic_cast<Triangle*>(element)) {
//             file << "  <triangle>\n";
//             file << "    <vec2>\n";
//             file << "      <x>" << triangle->getP1().x << "</x>\n";
//             file << "      <y>" << triangle->getP1().y << "</y>\n";
//             file << "    </vec2>\n";
//             file << "    <vec2>\n";
//             file << "      <x>" << triangle->getP2().x << "</x>\n";
//             file << "      <y>" << triangle->getP2().y << "</y>\n";
//             file << "    </vec2>\n";
//             file << "    <vec2>\n";
//             file << "      <x>" << triangle->getP3().x << "</x>\n";
//             file << "      <y>" << triangle->getP3().y << "</y>\n";
//             file << "    </vec2>\n";
//             file << "    <vec3>\n";
//             file << "      <x>" << triangle->getColor().x << "</x>\n";
//             file << "      <y>" << triangle->getColor().y << "</y>\n";
//             file << "      <z>" << triangle->getColor().z << "</z>\n";
//             file << "    </vec3>\n";
//             file << "  </triangle>\n";
//         }
//     }

//     file << "</layout>\n";
//     file.close();
// }

std::vector<std::string> GUIFile::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::istringstream stream(str);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

void GUIFile::readFile(const std::string& filename, Layout& layout) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << "\n";
        return;
    }

    parseLayout(file, layout);
}

// Read in XML File
void GUIFile::parseLayout(std::ifstream& file, Layout& parentLayout) {
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        std::cout << &parentLayout << std::endl;
        vec2 v2 = vec2();
        vec3 v3 = vec3();
        if (line.find("<layout") != std::string::npos) {
            Layout* layout = new Layout();
            std::vector<std::string> tokens = splitString(line, ' ');
            float sX = 0.0f, sY = 0.0f, eX = 1.0f, eY = 1.0f;
            bool active = false;
            for (const std::string& token : tokens) {
                if (token.find("sX=") != std::string::npos) {
                    std::vector<std::string> fields = splitString(token, '=');
                    sX = std::stof(fields[1]);
                }
                if (token.find("sY=")!= std::string::npos) {
                    std::vector<std::string> fields = splitString(token, '=');
                    sY = std::stof(fields[1]);
                }
                if (token.find("eX=")!= std::string::npos) {
                    std::vector<std::string> fields = splitString(token, '=');
                    eX = std::stof(fields[1]);
                }
                if (token.find("eY=")!= std::string::npos) {
                    std::vector<std::string> fields = splitString(token, '=');
                    eY = std::stof(fields[1]);
                }
                if (token.find("active=")!= std::string::npos) {
                    std::vector<std::string> fields = splitString(token, '=');
                    std::size_t activeFieldEnd = fields[1].find('>');
                    std::string activeField = fields[1].substr(0, activeFieldEnd);
                    active = (activeField == "true");
                }
            }
            layout->setBounds(sX, sY, eX, eY, {parentLayout.getStartPosition()}, {parentLayout.getEndPosition()});
            layout->setActive(active);
            parentLayout.addNestedLayout(layout);
            parseLayout(file, *layout);
        } else if (line.find("</layout>") != std::string::npos) {
            return;
        } else if (line.find("<line>") != std::string::npos) {
            Line* lineObj = new Line();
            parseVec2(file, v2);
            lineObj->setStart(v2);
            parseVec2(file, v2);
            lineObj->setEnd(v2);
            parseVec3(file, v3);
            lineObj->setColor(v3);
            parentLayout.addElement(lineObj);
        } else if (line.find("<box>") != std::string::npos) {
            Box* boxObj = new Box();
            parseVec2(file, v2);
            boxObj->setMin(v2);
            parseVec2(file, v2);
            boxObj->setMax(v2);
            parseVec3(file, v3);
            boxObj->setColor(v3);
            parentLayout.addElement(boxObj);
        } else if (line.find("<triangle>") != std::string::npos) {
            Triangle* triangleObj = new Triangle();
            parseVec2(file, v2);
            triangleObj->setP1(v2);
            parseVec2(file, v2);
            triangleObj->setP2(v2);
            parseVec2(file, v2);
            triangleObj->setP3(v2);
            parseVec3(file, v3);
            triangleObj->setColor(v3);
            parentLayout.addElement(triangleObj);
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
        try {
            vec.z = std::stof(zContent);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting z to float: " << e.what() << "\n";
            return;
        }
    }
}
