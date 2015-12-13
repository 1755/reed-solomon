#pragma once
#include <vector>
#include "Value.h"

using namespace std;

class Coder {
protected:
    unsigned t;


public:
    Coder(unsigned t);

    vector<Value> encode(vector<int> data);

    vector<Value> reminder(vector<Value> dividend, vector<Value> divider);
};
