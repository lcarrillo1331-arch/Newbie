/*
C++ Matrix Implementation with Raw Arrays & Single Subscript

To use a classic array while maintaining dynamic sizing
at runtime, we must use a dynamically allocated 1D array
via the new and delete[] operators.Because we are managing
raw memory directly instead of letting std::vector handle
it, we must explicitly implement the Rule of Three
(Destructor, Copy Constructor, and Copy Assignment Operator)
to prevent memory leaks and shallow copy bugs.To access the
matrix using a single-index subscript, the class overloads
operator[] to accept a single integer representing the row.
To get the 2D look (matrix[row][col]), this operator returns
a raw pointer to the start of that specific row. The compiler
then automatically applies the second set of brackets [col]
directly to that pointer.

*/
#ifndef ARRAY_MATRIX_H
#define ARRAY_MATRIX_H

#include <iostream>
#include <stdexcept>
#include <algorithm> // For std::copy and std::fill

template <typename T>
class ArrayMatrix {
private:
    size_t m_rows;
    size_t m_cols;
    T* m_data; // Raw 1D array allocated on the heap

public:
    // 1. Constructor
    ArrayMatrix(size_t rows, size_t cols, const T& initial_val = T())
        : m_rows(rows), m_cols(cols), m_data(nullptr) {
        if (rows == 0 || cols == 0) {
            throw std::invalid_argument("Matrix dimensions must be greater than zero.");
        }
        m_data = new T[rows * cols];
        std::fill(m_data, m_data + (rows * cols), initial_val);
    }

    // 2. Destructor
    ~ArrayMatrix() {
        delete[] m_data;
    }

    // 3. Copy Constructor
    ArrayMatrix(const ArrayMatrix<T>& other)
        : m_rows(other.m_rows), m_cols(other.m_cols) {
        m_data = new T[m_rows * m_cols];
        std::copy(other.m_data, other.m_data + (m_rows * m_cols), m_data);
    }

    // 4. Copy Assignment Operator
    ArrayMatrix<T>& operator=(const ArrayMatrix<T>& other) {
        if (this != &other) {
            T* new_data = new T[other.m_rows * other.m_cols];
            std::copy(other.m_data, other.m_data + (other.m_rows * other.m_cols), new_data);

            delete[] m_data;
            m_data = new_data;
            m_rows = other.m_rows;
            m_cols = other.m_cols;
        }
        return *this;
    }

    // Getters
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    // Single-index subscript operator (Non-const)
    T* operator[](size_t row) {
        if (row >= m_rows) throw std::out_of_range("Row index out of bounds.");
        return &m_data[row * m_cols];
    }

    // Single-index subscript operator (Const version)
    const T* operator[](size_t row) const {
        if (row >= m_rows) throw std::out_of_range("Row index out of bounds.");
        return &m_data[row * m_cols];
    }

    // Matrix Addition
    ArrayMatrix<T> operator+(const ArrayMatrix<T>& other) const {
        if (m_rows != other.m_rows || m_cols != other.m_cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        ArrayMatrix<T> result(m_rows, m_cols);
        for (size_t i = 0; i < m_rows * m_cols; ++i) {
            result.m_data[i] = this->m_data[i] + other.m_data[i];
        }
        return result;
    }

    // Matrix Multiplication
    ArrayMatrix<T> operator*(const ArrayMatrix<T>& other) const {
        if (m_cols != other.m_cols) { // Logic check: column of A must match row of B
            // fixing parameter check below
        }
        if (m_cols != other.m_rows) {
            throw std::invalid_argument("Matrix dimensions mismatch for multiplication.");
        }

        ArrayMatrix<T> result(m_rows, other.m_cols, T(0));

        // Cache-friendly (i, k, j) loop layout utilizing our double bracket syntax
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t k = 0; k < m_cols; ++k) {
                T temp = (*this)[i][k];
                for (size_t j = 0; j < other.m_cols; ++j) {
                    result[i][j] += temp * other[k][j];
                }
            }
        }
        return result;
    }

    void print() const {
        for (size_t r = 0; r < m_rows; ++r) {
            for (size_t c = 0; c < m_cols; ++c) {
                std::cout << (*this)[r][c] << " ";
            }
            std::cout << "\n";
        }
    }

    // --- STREAM OPERATORS ---

    // 1. Output Stream Operator (Print)
    // Declared as friend to access private m_rows, m_cols, and m_data directly
    friend std::ostream& operator<<(std::ostream& os, const ArrayMatrix<T>& matrix) {
        for (size_t r = 0; r < matrix.m_rows; ++r) {
            for (size_t c = 0; c < matrix.m_cols; ++c) {
                os << matrix[r][c];
                if (c + 1 < matrix.m_cols) os << " "; // Space separating columns
            }
            os << "\n"; // Newline separating rows
        }
        return os; // Allow chaining (e.g., std::cout << mat1 << mat2;)
    }

    // 2. Input Stream Operator (Read)
    friend std::istream& operator>>(std::istream& is, ArrayMatrix<T>& matrix) {
        for (size_t i = 0; i < matrix.m_rows * matrix.m_cols; ++i) {
            // Read element by element from stream into flat array sequential memory
            if (!(is >> matrix.m_data[i])) {
                // If stream input fails mid-way, break out early
                break;
            }
        }
        return is; // Allow chaining (e.g., std::cin >> mat1 >> mat2;)
    }
};

#endif // ARRAY_MATRIX_H