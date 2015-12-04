#pragma once
#include <iostream>
#include <vector>
#include "GF2m.h"

using namespace std;


class Value {

private:

    vector<vector<int>> polynomials = {
            {1, 1, 1}, // 2
            {1, 0, 1, 1}, // 3
            {1, 0, 0, 1, 1}, // 4
            {1, 0, 0, 1, 0, 1}, // 5
            {1, 0, 0, 0, 0, 1, 1}, // 6
            {1, 0, 0, 0, 1, 0, 0, 1}, // 7
            {1, 0, 0, 0, 1, 1, 1, 0, 1}, // 8
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 1}, // 9
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, // 10
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, // 11
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1}, // 12
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1}, // 13
            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1}, // 14
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, // 15
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1} // 16
    };

    vector<int> from_10_to_2(int value);

    vector<int> binary_mul(vector<int> factor_1, vector<int> factor_2);

    vector<int> binary_div_reminder(vector<int> dividend, vector<int> divider);

    int from_2_to_10(vector<int> binary);


protected:

    int value;

    vector<int> polynomial = polynomials[GF2m::get_field()->get_m() - 2];

public:

    Value();

    Value(int v);

    int get_value();

    Value get_inverse();

    static Value pow(Value v, int p);

    Value operator+(const Value &rv);

    Value operator*(const Value &rv);

    Value operator/(Value &rv);

    bool operator==(const Value &rv);

    bool operator!=(const Value &rv);
};
