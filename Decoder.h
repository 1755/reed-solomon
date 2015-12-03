#pragma once
#include <vector>

using namespace std;

class Decoder
{
    int m_t = 0;
    int m_m = 0;
public:
    Decoder(int t, int m);
    vector<int> decode(vector<int> message);
};