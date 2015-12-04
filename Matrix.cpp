//
// Created by sergey on 04.12.15.
//

#include "Matrix.h"

Matrix::Matrix(int height, int width)
{
    m_height = height;
    m_width = width;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            m_elements[i][j] = Value(0);
        }
    }
}

Value Matrix::getValue(int i, int j) const
{
    return m_elements[i][j];
}

void Matrix::setValue(int i, int j, const Value &value)
{
    m_elements[i][j] = value;
}

Matrix &Matrix::operator=(const Matrix &rvalue)
{

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_elements[i][j] = Value(0);
        }
    }

    return *this;
}

Matrix Matrix::reverse() {
    // todo: implement me
    return Matrix(m_height, m_width);
}

bool operator==(const Matrix &lvalue, const Matrix &rvalue)
{
    // todo: compare sizes
    for (int i = 0; i < lvalue.height(); ++i) {
        for (int j = 0; j < lvalue.width(); ++j) {
            if(lvalue.getValue(i, j) != rvalue.getValue(i, j)) {
                return false;
            }
        }
    }

    return true;
}

Matrix operator+(const Matrix &lvalue, const Matrix &rvalue)
{
    // todo: throw exception if matrices size isn't equal
    Matrix newMatrix(lvalue.height(), lvalue.width());
    for (int i = 0; i < lvalue.height(); ++i) {
        for (int j = 0; j < lvalue.width(); ++j) {
            newMatrix.setValue(i, j, lvalue.getValue(i,j) + rvalue.getValue(i,j));
        }
    }
    return newMatrix;
}

/*Matrix operator-(const Matrix &lvalue, const Matrix &rvalue)
{
    // todo: throw exception if matrices size isn't equal
    Matrix newMatrix(lvalue.height(), lvalue.width());
    for (int i = 0; i < lvalue.height(); ++i) {
        for (int j = 0; j < lvalue.width(); ++j) {
            newMatrix.setValue(i, j, lvalue.getValue(i,j) - rvalue.getValue(i,j));
        }
    }
    return newMatrix;
}*/

Matrix operator*(const Matrix &lvalue, const Matrix &rvalue)
{
    // todo: throw exception if matrices size not valid
    Matrix newMatrix(lvalue.height(), rvalue.width());
    for (int i = 0; i < lvalue.height(); ++i) {
        for (int j = 0; j < rvalue.width(); ++j) {
            Value sum = Value(0);
            for (int k = 0; k < rvalue.height(); ++k) {
                sum = sum + (lvalue.getValue(i,k)*rvalue.getValue(k, j));
            }
            newMatrix.setValue(i, j, sum);
        }
    }

    return newMatrix;
}

int Matrix::height() const {
    return m_height;
}

int Matrix::width() const {
    return m_width;
}
