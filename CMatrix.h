//
// Created on 9/7/26.
//
#ifndef C_MATRIX_H
#define C_MATRIX_H

#include <cstddef>
using std::size_t;

class CMatrix
{
public:
    CMatrix(size_t rows, size_t columns, int initialValue = 0);
    CMatrix(const CMatrix& other);
    ~CMatrix();

    CMatrix& operator=(const CMatrix& other);

    CMatrix add(const CMatrix& other) const;
    CMatrix subtract(const CMatrix& other) const;
    CMatrix multiply(const CMatrix& other) const;
    CMatrix transpose() const;

    size_t getRows() const;
    size_t getColumns() const;

    int get(size_t row, size_t column) const;
    void set(size_t row, size_t column, int value);

private:
    size_t rowCount;
    size_t columnCount;
    int* data;

    size_t offset(size_t row, size_t column) const;
    void requireValidPosition(size_t row, size_t column) const;
};

#endif // C_MATRIX_H