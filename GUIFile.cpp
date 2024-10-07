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

// Write an XML file from stored data
void GUIFile::writeFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    file << "<layout>\n";
    
    // Writing lines
    for (const auto& line : lines) {
        file << "  <line>\n";
        file << "    <vec2>\n";
        file << "      <x>" << line.startPos.x << "</x>\n";
        file << "      <y>" << line.startPos.y << "</y>\n";
        file << "    </vec2>\n";
        file << "    <vec2>\n";
        file << "      <x>" << line.endPos.x << "</x>\n";
        file << "      <y>" << line.endPos.y << "</y>\n";
        file << "    </vec2>\n";
        file << "    <vec3>\n";
        file << "      <x>" << line.color.x << "</x>\n";
        file << "      <y>" << line.color.y << "</y>\n";
        file << "      <z>" << line.color.z << "</z>\n";
        file << "    </vec3>\n";
        file << "  </line>\n";
    }

    // Writing boxes
    for (const auto& box : boxes) {
        file << "  <box>\n";
        file << "    <vec2>\n";
        file << "      <x>" << box.minBounds.x << "</x>\n";
        file << "      <y>" << box.minBounds.y << "</y>\n";
        file << "    </vec2>\n";
        file << "    <vec2>\n";
        file << "      <x>" << box.maxBounds.x << "</x>\n";
        file << "      <y>" << box.maxBounds.y << "</y>\n";
        file << "    </vec2>\n";
        file << "    <vec3>\n";
        file << "      <x>" << box.color.x << "</x>\n";
        file << "      <y>" << box.color.y << "</y>\n";
        file << "      <z>" << box.color.z << "</z>\n";
        file << "    </vec3>\n";
        file << "  </box>\n";
    }

    // Writing points
    for (const auto& point : points) {
        file << "  <point>\n";
        file << "    <vec2>\n";
        file << "      <x>" << point.position.x << "</x>\n";
        file << "      <y>" << point.position.y << "</y>\n";
        file << "    </vec2>\n";
        file << "    <vec3>\n";
        file << "      <x>" << point.color.x << "</x>\n";
        file << "      <y>" << point.color.y << "</y>\n";
        file << "      <z>" << point.color.z << "</z>\n";
        file << "    </vec3>\n";
        file << "  </point>\n";
    }
    
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
            std::cout << "Line" << "\n";
            Line lineObj;
            std::getline(file, line);
            parseVec2(file, lineObj.startPos);
            std::getline(file, line);
            parseVec2(file, lineObj.endPos);
            std::getline(file, line);
            parseVec3(file, lineObj.color);
            lines.push_back(lineObj);
        }
        else if (line.find("<box>") != std::string::npos) {
            std::cout << "Box" << "\n";
            Box boxObj;
            std::getline(file, line);
            parseVec2(file, boxObj.minBounds);
            std::getline(file, line);
            parseVec2(file, boxObj.maxBounds);
            std::getline(file, line);
            parseVec3(file, boxObj.color);
            boxes.push_back(boxObj);
        }
        else if (line.find("<point>") != std::string::npos) {
            std::cout << "Point" << "\n";
            Point pointObj;
            std::getline(file, line);
            parseVec2(file, pointObj.position);
            std::getline(file, line);
            parseVec3(file, pointObj.color);
            points.push_back(pointObj);
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
    std::getline(file, line);
    if (line.empty()) {
        std::cerr << "Error: Expected <x> tag but got empty line.\n";
        return;
    }
    std::size_t xStart = line.find('>') + 1;
    std::size_t xEnd = line.find("</x>");
    if (xEnd == std::string::npos) {
        std::cerr << "Error: Could not find </x> closing tag.\n";
        return;
    }
    std::string xContent = line.substr(xStart, xEnd - xStart);
    xContent = trim(xContent);
    std::cout << "Vec2 x content: '" << xContent << "'\n";
    
    try {
        vec.x = std::stof(xContent);  // Convert to float
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error converting x to float: " << e.what() << "\n";
        return;
    }

    // Parsing the y value
    std::getline(file, line);
    if (line.empty()) {
        std::cerr << "Error: Expected <y> tag but got empty line.\n";
        return;
    }
    std::size_t yStart = line.find('>') + 1;
    std::size_t yEnd = line.find("</y>");
    if (yEnd == std::string::npos) {
        std::cerr << "Error: Could not find </y> closing tag.\n";
        return;
    }
    std::string yContent = line.substr(yStart, yEnd - yStart);
    yContent = trim(yContent);
    std::cout << "Vec2 y content: '" << yContent << "'\n";
    
    try {
        vec.y = std::stof(yContent);  // Convert to float
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error converting y to float: " << e.what() << "\n";
        return;
    }

    std::getline(file, line);  // Consume the </vec2> line
}

void GUIFile::parseVec3(std::ifstream& file, vec3& vec) {
    std::string line;
    
    // Parsing the x value
    std::getline(file, line);
    if (line.empty()) {
        std::cerr << "Error: Expected <x> tag but got empty line.\n";
        return;
    }
    std::size_t xStart = line.find('>') + 1;
    std::size_t xEnd = line.find("</x>");
    if (xEnd == std::string::npos) {
        std::cerr << "Error: Could not find </x> closing tag.\n";
        return;
    }
    std::string xContent = line.substr(xStart, xEnd - xStart);
    xContent = trim(xContent);
    std::cout << "Vec3 x content: '" << xContent << "'\n";

    try {
        vec.x = std::stof(xContent);  // Convert to float
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error converting x to float: " << e.what() << "\n";
        return;
    }

    // Parsing the y value
    std::getline(file, line);
    if (line.empty()) {
        std::cerr << "Error: Expected <y> tag but got empty line.\n";
        return;
    }
    std::size_t yStart = line.find('>') + 1;
    std::size_t yEnd = line.find("</y>");
    if (yEnd == std::string::npos) {
        std::cerr << "Error: Could not find </y> closing tag.\n";
        return;
    }
    std::string yContent = line.substr(yStart, yEnd - yStart);
    yContent = trim(yContent);
    std::cout << "Vec3 y content: '" << yContent << "'\n";

    try {
        vec.y = std::stof(yContent);  // Convert to float
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error converting y to float: " << e.what() << "\n";
        return;
    }

    // Parsing the z value
    std::getline(file, line);
    if (line.empty()) {
        std::cerr << "Error: Expected <z> tag but got empty line.\n";
        return;
    }
    std::size_t zStart = line.find('>') + 1;
    std::size_t zEnd = line.find("</z>");
    if (zEnd == std::string::npos) {
        std::cerr << "Error: Could not find </z> closing tag.\n";
        return;
    }
    std::string zContent = line.substr(zStart, zEnd - zStart);
    zContent = trim(zContent);
    std::cout << "Vec3 z content: '" << zContent << "'\n";

    try {
        vec.z = std::stof(zContent);  // Convert to float
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error converting z to float: " << e.what() << "\n";
        return;
    }

    std::getline(file, line);  // Consume the </vec3> line
}

// Getter methods
std::vector<Line> GUIFile::getLines() const {
    return lines;
}

std::vector<Box> GUIFile::getBoxes() const {
    return boxes;
}

std::vector<Point> GUIFile::getPoints() const {
    return points;
}

// Clear data
void GUIFile::clear() {
    lines.clear();
    boxes.clear();
    points.clear();
}
