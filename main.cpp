// main.cpp
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "matrix.hpp"

int main() {
    // VEC2 UNIT TESTS

    // vec2 addition
    vec2 testVec2(1, 0);
    vec2 expectedVec2(2, 0);
    vec2 resultVec2 = testVec2 + testVec2;
    if (expectedVec2 == resultVec2) {
        std::cout << "vec2 addition function working\n";
    } else {
        std::cout << "vec2 addition function FAILED!\n";
    }

    // vec2 subtraction
    expectedVec2 = vec2(0, 0);
    resultVec2 = testVec2 - testVec2;
    if (expectedVec2 == resultVec2) {
        std::cout << "vec2 subtraction function working\n";
    } else {
        std::cout << "vec2 subtraction function FAILED!\n";
    }

    // vec2 scalar multiplication
    expectedVec2 = vec2(3, 0);
    resultVec2 = testVec2 * 3;

    if (expectedVec2 == resultVec2) {
        std::cout << "vec2 scalar multiplication function working\n";
    } else {
        std::cout << "vec2 scalar multiplication function FAILED!\n";
    }

    // vec2 dot product
    vec2 otherVec2 = vec2(2, 1);
    float result = testVec2.dot(otherVec2);
    if (result == 2) {
        std::cout << "vec2 dot product function working\n";
    } else {
        std::cout << "vec2 dot product function FAILED!\n";
    }

    // IVEC2 UNIT TESTS

    // ivec2 addition
    ivec2 testIvec2(3, 4);
    int expectedMagnitudeIvec2 = 7;
    int magnitudeIvec2 = testIvec2.magnitude();
    if (magnitudeIvec2 == expectedMagnitudeIvec2) {
        std::cout << "ivec2 magnitude function working\n";
    } else {
        std::cout << "ivec2 magnitude function FAILED!\n";
    }
}