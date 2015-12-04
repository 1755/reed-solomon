#pragma once

#include <vector>
#include "Value.h"

class Matrix
{
    int m_height;
    int m_width;
    vector<vector<Value> > m_elements;

public:
    Matrix(int height, int width);
    Value getValue(int i, int j) const;
    void setValue(int i, int j, const Value& value);
    Matrix& operator=(const Matrix& rvalue);
    Matrix reverse();
    int height() const;
    int width() const;


public:
    friend bool operator==(const Matrix& lvalue, const Matrix& rvalue);
    friend bool operator!=(const Matrix& lvalue, const Matrix& rvalue){return !operator==(lvalue,rvalue);}
    friend Matrix operator+(const Matrix& lvalue, const Matrix& rvalue);
//    friend Matrix operator-(const Matrix& lvalue, const Matrix& rvalue);
    friend Matrix operator*(const Matrix& lvalue, const Matrix& rvalue);


};


//std::ostream& operator<<(std::ostream& os, const Matrix& obj);
//std::istream& operator>>(std::istream& is, const Matrix& obj);

