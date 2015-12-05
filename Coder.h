#pragma once
#include <vector>
#include "Value.h"

using namespace std;

class Coder {
protected:
    int t;


public:
    Coder(int t);

    vector<Value> encode(vector<int> data);

    vector<int> decode(vector<Value> message);

};
