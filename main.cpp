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
    float vec2Result = testVec2.dot(otherVec2);
    if (vec2Result == 2.0) {
        std::cout << "vec2 dot product function working\n";
    } else {
        std::cout << "vec2 dot product function FAILED!\n";
    }

    // vec2 magnitude
    if (testVec2.magnitude() == 1.0) {
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

    // ivec2 dot product
    ivec2 otherIvec2 = ivec2(2, 1);
    int ivec2Result = testIvec2.dot(otherIvec2);
    if (ivec2Result == 10) {
        std::cout << "ivec2 dot product function working\n";
    } else {
        std::cout << "ivec2 dot product function FAILED!\n";
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

    // vec3 addition
    vec3 testVec3(1, 1, 1);
    vec3 expectedVec3(2, 2, 2);
    vec3 resultVec3 = testVec3 + testVec3;
    if (expectedVec3 == resultVec3) {
        std::cout << "vec3 addition function working\n";
    } else {
        std::cout << "vec3 addition function FAILED!\n";
    }

    // vec3 subtraction
    expectedVec3 = vec3(0, 0, 0);
    resultVec3 = testVec3 - testVec3;
    if (expectedVec3 == resultVec3) {
        std::cout << "vec3 subtraction function working\n";
    } else {
        std::cout << "vec3 subtraction function FAILED!\n";
    }

    // vec3 scalar multiplication
    expectedVec3 = vec3(3, 3, 3);
    resultVec3 = testVec3 * 3;
    if (expectedVec3 == resultVec3) {
        std::cout << "vec3 scalar multiplication function working\n";
    } else {
        std::cout << "vec3 scalar multiplication function FAILED!\n";
    }

    // vec3 dot product
    vec3 otherVec3 = vec3(2, 2, 2);
    float vec3Result = testVec3.dot(otherVec3);
    if (vec3Result == 6.0) {
        std::cout << "vec3 dot product function working\n";
    } else {
        std::cout << "vec3 dot product function FAILED!\n";
    }

    // vec3 magnitude
    testVec3 = vec3(3, 4, 0);
    if (testVec3.magnitude() == 5.0) {
        std::cout << "vec3 magnitude function working\n";
    } else {
        std::cout << "vec3 magnitude function FAILED!\n";
    }

    // vec3 unit vector
    expectedVec3 = vec3(0.6, 0.8, 0.0);
    if (testVec3.unit() == expectedVec3) {
        std::cout << "vec3 unit vector function working\n";
    } else {
        std::cout << "vec3 unit vector function FAILED!\n";
    }

    // vec3 cross product
    otherVec3 = vec3(4.0, 5.0, 6.0);
    expectedVec3 = vec3(24.0, -18.0, -1.0);
    resultVec3 = testVec3.cross(otherVec3);
    if (testVec3.cross(otherVec3) == expectedVec3) {
        std::cout << "vec3 cross product function working\n";
    } else {
        std::cout << "vec3 cross product function FAILED!\n";
    }

    // IVEC3 UNIT TESTS

    // ivec3 addition
    ivec3 testIvec3(3, 4, 5);
    ivec3 expectedIvec3(6, 8, 10);
    ivec3 resultIvec3 = testIvec3 + testIvec3;
    if (resultIvec3 == expectedIvec3) {
        std::cout << "ivec3 addition function working\n";
    } else {
        std::cout << "ivec3 addition function FAILED!\n";
    }

    // ivec3 subtraction
    expectedIvec3 = ivec3(0, 0, 0);
    resultIvec3 = testIvec3 - testIvec3;
    if (resultIvec3 == expectedIvec3) {
        std::cout << "ivec3 subtraction function working\n";
    } else {
        std::cout << "ivec3 subtraction function FAILED!\n";
    }

    // ivec3 scalar multiplication
    expectedIvec3 = ivec3(9, 12, 15);
    resultIvec3 = testIvec3 * 3;
    if (resultIvec3 == expectedIvec3) {
        std::cout << "ivec3 scalar multiplication function working\n";
    } else {
        std::cout << "ivec3 scalar multiplication function FAILED!\n";
    }

    // ivec3 dot product
    int ivec3Result = testIvec3.dot(testIvec3);
    if (ivec3Result == 50) {
        std::cout << "ivec3 dot product function working\n";
    } else {
        std::cout << "ivec3 dot product function FAILED!\n";
    }

    // ivec3 magnitude
    if (testIvec3.magnitude() == 12) {
        std::cout << "ivec3 magnitude function working\n";
    } else {
        std::cout << "ivec3 magnitude function FAILED!\n";
    }

    // ivec3 unit vector
    expectedIvec3 = ivec3(0, 0, 0);
    if (testIvec3.unit() == expectedIvec3) {
        std::cout << "ivec3 unit vector function working\n";
    } else {
        std::cout << "ivec3 unit vector function FAILED!\n";
    }

    // ivec3 cross product
    ivec3 otherIvec3(2, 2, 2);
    expectedIvec3 = ivec3(-2, 4, -2);
    resultIvec3 = testIvec3.cross(otherIvec3);
    if (resultIvec3 == expectedIvec3) {
        std::cout << "ivec3 cross product function working\n";
    } else {
        std::cout << "ivec3 cross product function FAILED!\n";
    }
}