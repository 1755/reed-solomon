//
// Created by sergey on 13.12.15.
//

#include "Polynomial.h"

Polynomial::Polynomial(const vector<Value> &valuesVector)
{
    m_valuesVector = valuesVector;
}

void Polynomial::name(const string &name)
{
    m_name = name;
}

const string &Polynomial::name() const
{
    return m_name;
}


int Polynomial::degree() const
{
    for (int i = 0; i < m_valuesVector.size(); ++i) {
        if(m_valuesVector[i].get_value() != 0) {
            return int(m_valuesVector.size() - i - 1);
        }
    }
    return 0;
}

Value &Polynomial::operator[](int index)
{
    if(index < 0 || index >= m_valuesVector.size()) {
        throw new IndexError("Polynomial index error");
    }
    return m_valuesVector[index];
}

/*const Value& Polynomial::operator[](int index) const
{
    if(index < 0 || index >= m_valuesVector.size()) {
        throw new IndexError("Polynomial index error");
    }
    return m_valuesVector[index];
}*/


Value Polynomial::operator()(const Value &x) const
{
    Value result = 0;
    for (int i = int(m_valuesVector.size() - 1); i >= 0 ; --i) {
        result = result + m_valuesVector[i] * Value::pow(x, i);
    }
    return result;
}

bool operator==(const Polynomial &lvalue, const Polynomial &rvalue)
{
    if(lvalue.degree() != rvalue.degree()) {
        return false;
    }

    for (int i = 0; i < lvalue.degree(); ++i) {
        if(lvalue.m_valuesVector[i].get_value() != rvalue.m_valuesVector[i].get_value()) { // fixme: access via operator[]
            return false;
        }
    }
    return true;
}

Polynomial operator+(const Polynomial &lvalue, const Polynomial &rvalue)
{
    vector<Value> sum((unsigned long) max(lvalue.degree(), rvalue.degree()) + 1);
    for (int degree = 0; degree < sum.size(); ++degree) {
        Value left = 0;
        Value right = 0;

        if(degree <= lvalue.degree()) {
            left = lvalue.m_valuesVector[lvalue.m_valuesVector.size() - degree - 1];
        }

        if(degree <= rvalue.degree() + 1) {
            right = rvalue.m_valuesVector[rvalue.m_valuesVector.size() - degree - 1];
        }

        sum[sum.size() - degree - 1] = left + right;
    }

    return sum;
}

Polynomial operator-(const Polynomial &lvalue, const Polynomial &rvalue)
{
    return lvalue + rvalue; // todo: checkme
}

Polynomial operator*(const Polynomial &lvalue, const Polynomial &rvalue)
{

    vector<Value> mul;
    for (int q = 0; q <= lvalue.degree() + rvalue.degree(); ++q) {
        mul.push_back(0);
        Value a = 0;
        for (int i = 0; i <= q; ++i) {
            Value left = 0;
            Value right = 0;
            if(i <= lvalue.degree()) {
                left = lvalue.m_valuesVector[i]; // fixme
            }

            if(q - i <= rvalue.degree()) {
                right = rvalue.m_valuesVector[q-i]; // fixme
            }
//            cout << left.get_value() << " " << right.get_value() << endl;

            a = a + left*right;
        }
//        cout << endl;
        mul[q] = a;
    }
    return Polynomial(mul);
}


Polynomial operator*(const Value &lvalue, const Polynomial &rvalue)
{
    vector<Value> amul;
    for (int i = 0; i <= rvalue.degree(); ++i) {
        amul[i] = lvalue * rvalue.m_valuesVector[i]; // todo:fixme
    }
    return Polynomial(amul);
}

Polynomial operator%(const Value &lvalue, const Polynomial &rvalue) {
    return Polynomial(std::vector<Value>());
}

std::ostream &operator<<(std::ostream &os, const Polynomial &obj)
{
    os << "Polynomial's vector: " << endl;
    for (int i = 0; i < obj.m_valuesVector.size(); ++i) {
        os << obj.m_valuesVector[i].get_value() << " ";
    }
    os << endl;
    os << "-------";
    os << "Polynomial" << endl;
    if(obj.name().length() > 0) {
        os << obj.name() << "(x) = ";
    }
    for (int i = 0; i < obj.m_valuesVector.size(); ++i) {
        os << obj.m_valuesVector[i].get_value();
        if(i < obj.m_valuesVector.size() - 1) {
            os << "*" << "x^" << obj.m_valuesVector.size() - i - 1;
        }

        if(i < obj.m_valuesVector.size() - 1) {
            os << " + ";
        }
    }
    os << endl;


    return os;
}

Polynomial &Polynomial::operator=(const Polynomial &rvalue)
{
    for (int i = 0; i < rvalue.m_valuesVector.size(); ++i) {
        m_valuesVector[i] = rvalue.m_valuesVector[i];
    }
    return *this;
}


