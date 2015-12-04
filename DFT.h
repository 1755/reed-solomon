#pragma once

#include <vector>
#include "Value.h"
#include <cmath>


using namespace std;

class DFT
{
public:
    vector<Value> forward(vector<Value> dataVector);

protected:
    Value polynomial(vector<Value> dataVector, Value x);

};