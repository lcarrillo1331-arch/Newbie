// Matrix 1
// Implementation 1: Flat Vector with Matrix Multiplication
// This version includes the mathematical matrix multiplication
// (operator*), which requires validating that the number of
// columns in the first matrix matches the number of rows in
// the second matrix.


#ifndef P1_MATRIX1_H
#define P1_MATRIX1_H

#include <iostream>
#include <vector>


template <typename T>
class Matrix1 {
private:
    size_t m_rows;
    size_t m_cols;
    std::vector<T> m_data; // Flat 1D storage for continuous memory layout

public:
    // Constructor
    // TODO: Constructor with third optional parameter.
    //       Use an initialization list.
    Matrix1

    // Getters
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    // Operator() overloading for element access: matrix(row, col)
    // Non-const version (allows modification)
    T& operator()(size_t r, size_t c) {
        if (r >= m_rows || c >= m_cols) {
            throw std::out_of_range("Matrix index out of bounds.");
        }
        return m_data[r * m_cols + c];
    }

    // Const version (read-only)
    const T& operator()(size_t r, size_t c) const {
        if (r >= m_rows || c >= m_cols) {
            throw std::out_of_range("Matrix index out of bounds.");
        }
        return m_data[r * m_cols + c];
    }

    // Overloading '+' operator for Matrix addition
    Matrix1<T> operator+(const Matrix1<T>& other) const {
        if (m_rows != other.m_rows || m_cols != other.m_cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        Matrix1<T> result(m_rows, m_cols);
        for (size_t i = 0; i < m_data.size(); ++i) {
            result.m_data[i] = m_data[i] + other.m_data[i];
        }
        return result;
    }

    // Matrix Multiplication: (A x B) * (B x C) = (A x C)
    Matrix1<T> operator*(const Matrix1<T>& other) const {
        if (m_cols != other.m_rows) {
            throw std::invalid_argument("Matrix dimensions mismatch for multiplication.");
        }

        Matrix1<T> result(m_rows, other.m_cols, T(0));

        // TODO: Analyze Cache-friendly loop order (i, k, j) to optimize data locality
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t k = 0; k < m_cols; ++k) {
                T temp = (*this)(i, k);
                for (size_t j = 0; j < other.m_cols; ++j) {
                    result(i, j) += temp * other(k, j);
                }
            }
        }
        return result;
    }

    // Print helper function
    void print() const {
        for (size_t r = 0; r < m_rows; ++r) {
            for (size_t c = 0; c < m_cols; ++c) {
                std::cout << (*this)(r, c) << " ";
            }
            std::cout << "\n";
        }
    }
};

#endif //P1_MATRIX1_H