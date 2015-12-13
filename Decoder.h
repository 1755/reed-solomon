#pragma once
#include <vector>
#include <algorithm>
#include "Value.h"

using namespace std;

class Decoder
{
    int m_t;

public:
    Decoder(int t);
    vector<Value> decode(vector<Value> codedMessage);

};