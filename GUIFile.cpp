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
            Line lineObj;
            std::getline(file, line);
            parseVec2(file, lineObj.startPos);
            std::getline(file, line);
            std::getline(file, line);
            parseVec2(file, lineObj.endPos);
            std::getline(file, line);
            std::getline(file, line);
            parseVec3(file, lineObj.color);
            std::getline(file, line);
            lines.push_back(lineObj);
        }
        else if (line.find("<box>") != std::string::npos) {
            Box boxObj;
            std::getline(file, line);
            parseVec2(file, boxObj.minBounds);
            std::getline(file, line);
            std::getline(file, line);
            parseVec2(file, boxObj.maxBounds);
            std::getline(file, line);
            std::getline(file, line);
            parseVec3(file, boxObj.color);
            std::getline(file, line);
            boxes.push_back(boxObj);
        }
        else if (line.find("<point>") != std::string::npos) {
            Point pointObj;
            std::getline(file, line);
            parseVec2(file, pointObj.position);
            std::getline(file, line);
            std::getline(file, line);
            parseVec3(file, pointObj.color);
            std::getline(file, line);
            points.push_back(pointObj);
        }
    }
    file.close();
}

void GUIFile::parseVec2(std::ifstream& file, vec2& vec) {
    std::string line;
    std::getline(file, line);
    vec.x = std::stof(line.substr(line.find('>') + 1));
    std::getline(file, line);
    std::getline(file, line);
    vec.y = std::stof(line.substr(line.find('>') + 1));
    std::getline(file, line);
}

void GUIFile::parseVec3(std::ifstream& file, vec3& vec) {
    std::string line;
    std::getline(file, line);
    vec.x = std::stof(line.substr(line.find('>') + 1));
    std::getline(file, line);
    std::getline(file, line);
    vec.y = std::stof(line.substr(line.find('>') + 1));
    std::getline(file, line);
    std::getline(file, line);
    vec.z = std::stof(line.substr(line.find('>') + 1));
    std::getline(file, line);
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
