#pragma once
#include <iostream>
#include <vector>
#include "GF2m.h"

using namespace std;


class Value {

private:

    vector<int> from_10_to_2(int value) const;

    vector<int> binary_mul(vector<int> factor_1, vector<int> factor_2) const;

    vector<int> binary_div_reminder(vector<int> dividend, vector<int> divider) const;

    int from_2_to_10(vector<int> binary) const;


protected:

    int value;

    vector<int> polynomial = GF2m::get_field()->get_p();

public:

    Value();

    Value(int v);

    Value(const Value& v);

    int get_value() const;

    Value get_inverse() const;

    static Value pow(Value v, int p);

    Value operator+(const Value &rv);
    Value operator-(const Value &rv) const;

    Value operator*(const Value &rv) const ;

    Value operator/(Value &rv);

    bool operator==(const Value &rv);

    bool operator!=(const Value &rv);

    friend Value operator/(const Value& lvalue, const Value& rvalue);
    friend std::ostream& operator<<(std::ostream& os, const Value& value);


    Value& operator=(const Value& rvalue);

};
