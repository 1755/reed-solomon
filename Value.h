#pragma once
#include <iostream>
#include <vector>

using namespace std;


class Value {

private:

    vector<int> from_10_to_2(int value);

    vector<int> binary_mul(vector<int> factor_1, vector<int> factor_2);

    vector<int> binary_div_reminder(vector<int> dividend, vector<int> divider);

    int from_2_to_10(vector<int> binary);


protected:

    int value;


public:

    Value();

    Value(int v);

    int get_value();

    static Value pow(Value v, int p);

    Value operator+(const Value &rv);

    Value operator*(const Value &rv);

    bool operator==(const Value &rv);

    bool operator!=(const Value &rv);
};
