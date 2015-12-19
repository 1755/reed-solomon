#pragma once
#include <iostream>
#include <vector>

using namespace std;
class Value;

class GF2m {

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



    static GF2m *field;

    GF2m() {  }

    int m;

public:

    vector<Value> inverse;

    static GF2m *get_field() {
        if(!field)
            field = new GF2m();

        return field;
    }

    void set_m(int dim);

    int get_m();

    int get_capacity();

    vector<int> get_p();

};


class Value {

private:

    vector<int> binary_mul(vector<int> factor_1, vector<int> factor_2) const;

    vector<int> binary_div_reminder(vector<int> dividend, vector<int> divider) const;

protected:

    int value;

    vector<int> polynomial = GF2m::get_field()->get_p();

public:

    Value();

    Value(int v);

    Value(const Value& v);

    int get_value() const;

    Value get_inverse() const;

    static vector<int> from_10_to_2(int value);

    static int from_2_to_10(vector<int> binary);

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
