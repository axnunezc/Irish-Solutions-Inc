// matrix.hpp
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

class Matrix {
private:
    float components[3][3];

public:
    // Constructors
    Matrix() : components{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}} {} // Identity matrix

    Matrix(float data[3][3]) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                components[i][j] = data[i][j];
            }
        }
    }

    Matrix(const Matrix& other) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                components[i][j] = other.components[i][j];
            }
        }
    }

    // Assignment operator overload
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    components[i][j] = other.components[i][j];
                }
            }
        }
        return *this;
    }

    // Matrix multiplication operator overload
    Matrix operator*(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result.components[i][j] = 0;
                for (int k = 0; k < 3; ++k) {
                    result.components[i][j] += components[i][k] * other.components[k][j];
                }
            }
        }
        return result;
    }

    // Transpose function
    Matrix transpose() const {
        Matrix result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result.components[i][j] = components[j][i];
            }
        }
        return result;
    }
};

#endif // MATRIX_HPP