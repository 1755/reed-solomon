//
// Created by sergey on 04.12.15.
//

#include "DFT.h"



vector<Value> DFT::forward(vector<Value> dataVector)
{
    vector<Value> code;
    for (int i = 0; i < dataVector.size(); ++i) {
        code.push_back(Value(polynomial(dataVector, pow(2, i))));
    }

    return code;
}

Value DFT::polynomial(vector<Value> dataVector, Value x)
{
    Value v = Value(0);
    for (int i = 0; i < dataVector.size(); ++i) {
        v = v + dataVector[i] * Value::pow(x, i).get_inverse();
    }
    return v;
}
