// main.cpp
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "matrix.hpp"

int main() {
    // vec2 unit tests
    vec2 testVec2(1, 0);
    vec2 expectedVec2(2, 0);
    vec2 resultVec2 = testVec2 + testVec2;
    if (expectedVec2 == resultVec2) {
        std::cout << "vec2 addition function working\n";
    } else {
        std::cout << "vec2 addition function FAILED!\n";
    }

    // ivec2 unit tests
    ivec2 testIvec2(3, 4);
    int expectedMagnitudeIvec2 = 7;
    int magnitudeIvec2 = testIvec2.magnitude();
    if (magnitudeIvec2 == expectedMagnitudeIvec2) {
        std::cout << "ivec2 magnitude function working\n";
    } else {
        std::cout << "ivec2 magnitude function FAILED!\n";
    }
}