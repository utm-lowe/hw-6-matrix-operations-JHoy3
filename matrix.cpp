/**
 * @file matrix.cpp
 * @brief Implementation of the Matrix class
 * @copyright Copyright (c) 2024
 */

#include "matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor
Matrix::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols)
{
    ar = new double*[rows];
    for (unsigned int i = 0; i < rows; ++i) {
        ar[i] = new double[cols]{};  // Initialize to 0
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& rhs) : m(rhs.m), n(rhs.n)
{
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
}

// Destructor
Matrix::~Matrix()
{
    for (int i = 0; i < m; ++i) {
        delete[] ar[i];
    }
    delete[] ar;
}

// Get rows
int Matrix::getRows() const
{
    return m;
}

// Get columns
int Matrix::getCols() const
{
    return n;
}

// Non-const at operator
double& Matrix::at(unsigned int row, unsigned int col)
{
    return ar[row][col];
}

// Const at operator
const double& Matrix::at(unsigned int row, unsigned int col) const
{
    return ar[row][col];
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& rhs)
{
    if (this != &rhs) {
        // Delete old data
        for (int i = 0; i < m; ++i) {
            delete[] ar[i];
        }
        delete[] ar;

        // Copy dimensions
        m = rhs.m;
        n = rhs.n;

        // Allocate and copy data
        ar = new double*[m];
        for (int i = 0; i < m; ++i) {
            ar[i] = new double[n];
            for (int j = 0; j < n; ++j) {
                ar[i][j] = rhs.ar[i][j];
            }
        }
    }
    return *this;
}

// Addition operator
Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix result(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = m1.at(i, j) + m2.at(i, j);
        }
    }
    return result;
}

// Subtraction operator
Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    Matrix result(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = m1.at(i, j) - m2.at(i, j);
        }
    }
    return result;
}

// Matrix multiplication
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix result(m1.getRows(), m2.getCols());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m2.getCols(); ++j) {
            double sum = 0;
            for (int k = 0; k < m1.getCols(); ++k) {
                sum += m1.at(i, k) * m2.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

// Scalar multiplication (scalar * matrix)
Matrix operator*(double scalar, const Matrix& m)
{
    Matrix result(m.getRows(), m.getCols());
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            result.at(i, j) = scalar * m.at(i, j);
        }
    }
    return result;
}

// Scalar multiplication (matrix * scalar)
Matrix operator*(const Matrix& m, double scalar)
{
    return scalar * m;
}

// Output operator
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            os << setw(10) << m.at(i, j) << " ";
        }
        os << endl;
    }
    return os;
}

// Input operator
std::istream& operator>>(std::istream& is, Matrix& m)
{
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            is >> m.at(i, j);
        }
    }
    return is;
}
