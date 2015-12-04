#include "Value.h"

Value::Value() {
    value = 0;
}


Value::Value(int v) {
    value = v;
}


int Value::get_value() {
    return value;
}

Value Value::get_inverse() {
    return pow(*this, GF2m::get_field()->get_capacity() - 2);
}


Value Value::pow(Value v, int p) {
    Value result = Value(1);

    for (int i = 0; i < p; i++) {
        result = result * v;
    }

    return result;
}


bool Value::operator==(const Value &rv) {
    return (value == rv.value);
}


bool Value::operator!=(const Value &rv) {
    return (value != rv.value);
}


Value Value::operator+(const Value &rv) {
    return Value(value ^ rv.value);
}


Value Value::operator/(Value &rv) {
    return (*this)*rv.get_inverse();
}


Value Value::operator*(const Value &rv) {

    vector<int> left = from_10_to_2(value);
    vector<int> right = from_10_to_2(rv.value);

    vector<int> mul = binary_mul(left, right);

    vector<int> binary = binary_div_reminder(mul, polynomial);

    return Value(from_2_to_10(binary));
}


vector<int> Value::from_10_to_2(int value) {

    vector<int> result;
    if (value/2 == 0) {
        result.push_back(value%2);
    } else {
        result = from_10_to_2(value / 2);
        result.push_back(value%2);
    }

    return result;
}


vector<int> Value::binary_mul(vector<int> factor_1, vector<int> factor_2) {

    vector<int> result;

    for (int i = 0; i < factor_1.size(); i++) {

        for (int j = 0; j < factor_2.size(); j++) {

            int value = factor_1[i] * factor_2[j];

            if (i == 0) {
                result.push_back(value);
            } else {
                if (i + j == result.size()) {
                    result.push_back(value);
                } else {
                    result[i + j] = result[i + j] ^ value;
                }
            }
        }
    }

    return result;
}


vector<int> Value::binary_div_reminder(vector<int> dividend, vector<int> divider) {

    for (int i = divider.size(); i < dividend.size(); i++) {
        divider.push_back(0);
    }

    while (dividend.size() == divider.size()) {

        for (int i = 0; i < dividend.size(); i++) {
            dividend[i] = dividend[i] ^ divider[i];
        }

        while (dividend.front() == 0 && !dividend.empty()) {
            dividend.erase(dividend.begin());

            if (divider.back() == 0)
                divider.erase(divider.end() - 1);
        }
    }

    return dividend;
}


int Value::from_2_to_10(vector<int> binary) {
    int result = 0;

    for (int i = 0; i < binary.size() ; i++) {
        result += binary[i] * (1 << binary.size() - i - 1);
    }

    return result;
}
