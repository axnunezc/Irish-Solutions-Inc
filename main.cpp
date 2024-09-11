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

    // vec2 magnitude
    if (testVec2.magnitude() == 1) {
        std::cout << "vec2 magnitude function working\n";
    } else {
        std::cout << "vec2 magnitude function FAILED!\n";
    }

    // vec2 unit vector
    testVec2 = vec2(3, 4);
    expectedVec2 = vec2(0.6, 0.8);
    if (testVec2.unit() == expectedVec2) {
        std::cout << "vec2 unit vector function working\n";
    } else {
        std::cout << "vec2 unit vector function FAILED!\n";
    }

    // IVEC2 UNIT TESTS

    // ivec2 addition
    ivec2 testIvec2(3, 4);
    ivec2 expectedIvec2(6, 8);
    ivec2 resultIvec2 = testIvec2 + testIvec2;
    if (resultIvec2 == expectedIvec2) {
        std::cout << "ivec2 addition function working\n";
    } else {
        std::cout << "ivec2 addition function FAILED!\n";
    }

    // ivec2 subtraction
    expectedIvec2 = ivec2(0, 0);
    resultIvec2 = testIvec2 - testIvec2;
    if (resultIvec2 == expectedIvec2) {
        std::cout << "ivec2 subtraction function working\n";
    } else {
        std::cout << "ivec2 subtraction function FAILED!\n";
    }

    // ivec2 scalar multiplication
    expectedIvec2 = ivec2(9, 12);
    resultIvec2 = testIvec2 * 3;
    if (resultIvec2 == expectedIvec2) {
        std::cout << "ivec2 scalar multiplication function working\n";
    } else {
        std::cout << "ivec2 scalar multiplication function FAILED!\n";
    }

    // ivec2 magnitude
    int expectedMagnitudeIvec2 = 7;
    if (testIvec2.magnitude() == expectedMagnitudeIvec2) {
        std::cout << "ivec2 magnitude function working\n";
    } else {
        std::cout << "ivec2 magnitude function FAILED!\n";
    }

    // ivec2 unit vector
    expectedIvec2 = ivec2(0, 0);
    if (testIvec2.unit() == expectedIvec2) {
        std::cout << "ivec2 unit vector function working\n";
    } else {
        std::cout << "ivec2 unit vector function FAILED!\n";
    }

    // VEC3 UNIT TESTS

    // IVEC3 UNIT TESTS
}