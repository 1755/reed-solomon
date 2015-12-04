#include "Coder.h"
#include "Value.h"

Coder::Coder(int m, int t) {
    this->m = m;
    this->t = t;
}

vector<int> Coder::encode(vector<int> data) {
    vector<int> message;

    for (int i = 0; i < t*t; i++) {
        data.push_back(0);
    }

    for (int i = 0; i < data.size(); i++) {

        Value symbol;
        Value x = Value::pow(Value(2), i);

        for (int j = 0; j < data.size(); j++) {
            symbol = symbol + Value(data[j]) * Value::pow(x, j);
        }

        message.push_back(symbol.get_value());
    }

    return message;
}