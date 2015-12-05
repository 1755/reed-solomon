#include "Coder.h"

Coder::Coder(int t) {
    this->t = t;
}

vector<Value> Coder::encode(vector<int> data) {
    vector<Value> message;

    for (int i = data.size(); i < GF2m::get_field()->get_capacity() - 1; i++) {
        data.push_back(0);
    }

    for (int i = 0; i < data.size(); i++) {

        Value symbol;
        Value x = Value::pow(Value(2), i);

        for (int j = 0; j < data.size(); j++) {
            symbol = symbol + Value(data[j]) * Value::pow(x, j);
        }

        message.push_back(symbol);
    }

    return message;
}


vector<int> Coder::decode(vector<Value> message) {

    vector<int> data;

    for (int i = 0; i < message.size(); i++) {

        Value symbol;
        Value x = Value::pow(Value(2), i).get_inverse();

        for (int j = 0; j < message.size(); j++) {
            symbol = (symbol + Value(message[j]) * Value::pow(x, j));
        }

        data.push_back(symbol.get_value());
    }

    return data;
}