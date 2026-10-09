// Matrix2: Requires -std=c++23
/* Implementation 2: Modern Multi-Index Subscript Syntax (C++23)
The language allows operator[] to accept multiple arguments. This means
you can safely use the cleaner, native indexing look of matrix[row, col].
*/
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class ModernMatrix {
private:
    size_t m_rows;
    size_t m_cols;
    std::vector<T> m_data;

public:
    ModernMatrix(size_t rows, size_t cols, const T& initial_val = T())
        : m_rows(rows), m_cols(cols), m_data(rows * cols, initial_val) {}

    // C++23 Multi-index operator[] - Non-const version
    T& operator[](size_t r, size_t c) {
        if (r >= m_rows || c >= m_cols) throw std::out_of_range("Index out of bounds.");
        return m_data[r * m_cols + c];
    }

    // C++23 Multi-index operator[] - Const version
    const T& operator[](size_t r, size_t c) const {
        if (r >= m_rows || c >= m_cols) throw std::out_of_range("Index out of bounds.");
        return m_data[r * m_cols + c];
    }

    void print() const {
        for (size_t r = 0; r < m_rows; ++r) {
            for (size_t c = 0; c < m_cols; ++c) {
                // Using the modern operator[] inside the class
                std::cout << (*this)[r, c] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {   // Requires a C++23 compliant compiler
    ModernMatrix<double> mat(3, 3, 0.0);

    // Modern multi-argument square bracket syntax
    mat[0, 0] = 1.1;
    mat[1, 1] = 2.2;
    mat[2, 2] = 3.3;

    std::cout << "Modern C++23 Matrix Layout:\n";
    mat.print();

    return 0;
}