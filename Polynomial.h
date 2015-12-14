#pragma once
#include "Value.h"
#include "Error.h"
#include <vector>
#include <string>

using namespace std;

class Polynomial
{
    static const bool DEBUG = false;
    vector<Value> m_valuesVector;
    string m_name;

public:
    Polynomial(const vector<Value>& valuesVector);
    void name(const string& name);
    const string& name() const;
    int degree() const;
    int size() const;
    void debug() const;

public:
    Value& operator[](int index);
    //const Value& operator[](int index) const;
    Value operator()(const Value& x) const;

    friend bool operator==(const Polynomial& lvalue, const Polynomial& rvalue);
    friend bool operator!=(const Polynomial& lvalue, const Polynomial& rvalue){return !operator==(lvalue,rvalue);}

    friend Polynomial operator+(const Polynomial& lvalue, const Polynomial& rvalue);
    friend Polynomial operator-(const Polynomial& lvalue, const Polynomial& rvalue);
    friend Polynomial operator*(const Polynomial& lvalue, const Polynomial& rvalue);
    friend Polynomial operator*(const Value& lvalue, const Polynomial& rvalue);
    friend Polynomial operator%(const Polynomial& lvalue, const Polynomial& rvalue);
//    friend Polynomial operator/(const Polynomial& lvalue, const Polynomial& rvalue);

    Polynomial& operator=(const Polynomial& rvalue);


    friend std::ostream& operator<<(std::ostream& os, const Polynomial& obj);

public:
    class IndexError : Error
    {
    public:
        IndexError() : Error() {};
        IndexError(const string& message) : Error(message) {};
    };

private:
    Polynomial() {};
};


