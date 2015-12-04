//
// Created by sergey on 04.12.15.
//

#include "Matrix.h"

Matrix::Matrix(int height, int width)
{
    m_height = height;
    m_width = width;

    for (int i = 0; i < height; ++i) {
        m_elements.push_back(vector<Value>());
        for (int j = 0; j < width; ++j) {
            m_elements[i].push_back(0);
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
//    cout << "SET: " << value.get_value() << " i=" << i << " j=" << j << endl;
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

Matrix Matrix::reverse()
{
    // todo: chek if this is square matrix

    Matrix E(height(), width());
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            E.setValue(i, j, Value(0));
            if(i == j) {
                E.setValue(i, j, Value(1));
            }
        }
    }

    Matrix triangularMatrix = *this;
    for (int k = 0; k < height(); ++k) {
        if(triangularMatrix.getValue(k, k) == Value(0) && k < height() - 1) {
            for (int i = 0; i < width(); ++i) {
                triangularMatrix.setValue(k,i, triangularMatrix.getValue(k,i) + triangularMatrix.getValue(k+1,i));
                E.setValue(k, i, E.getValue(k,i) + E.getValue(k+1, i));
            }
        }
        for (int i = k + 1; i < height(); ++i) {
            Value c = triangularMatrix.getValue(i, k) / triangularMatrix.getValue(k, k);
            for (int j = 0; j < width(); ++j) {
                triangularMatrix.setValue(i,j, triangularMatrix.getValue(i,j) - c*triangularMatrix.getValue(k,j));
                E.setValue(i,j, E.getValue(i,j) - c*E.getValue(k,j));
            }
        }
    }

    //backward
    for (int k = height() - 1; k >= 0; --k) {
        for (int i = k - 1; i >= 0; --i) {
            Value c = triangularMatrix.getValue(i, k) / triangularMatrix.getValue(k, k);
            for (int j = 0; j < width(); ++j) {
                triangularMatrix.setValue(i,j, triangularMatrix.getValue(i,j) - c*triangularMatrix.getValue(k,j));
                E.setValue(i,j, E.getValue(i,j) - c*E.getValue(k,j));
            }

        }

    }

    // uno diag
    for (int i = 0; i < height(); ++i) {
        Value inv = triangularMatrix.getValue(i,i).get_inverse();
        for (int j = 0; j < width(); ++j) {
            triangularMatrix.setValue(i, j, triangularMatrix.getValue(i,j) * inv);
            E.setValue(i,j, E.getValue(i,j) * inv);
        }
    }


    return E;
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

Matrix Matrix::transpose() {
    Matrix t(height(), width());
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            t.setValue(i,j, getValue(j, i));
        }
    }

    return t;
}

Matrix operator*(const Value &lvalue, const Matrix &rvalue) {
    Matrix newMatrix = Matrix(rvalue.height(), rvalue.width());
//    for (int i = 0; i < rvalue.height(); ++i) {
//        for (int j = 0; j < rvalue.width(); ++j) {
//            newMatrix.setValue(i, j, Value(2));
//        }
//    }
    for (int i = 0; i < newMatrix.height(); ++i) {
        for (int j = 0; j < newMatrix.width(); ++j) {
            newMatrix.setValue(i, j, lvalue * newMatrix.getValue(i,j));
        }
    }
    return newMatrix;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (int i = 0; i < matrix.height(); ++i) {
        for (int j = 0; j < matrix.width(); ++j) {
            os << matrix.getValue(i,j).get_value() << " ";
        }
        os << endl;
    }
    return  os;
}
