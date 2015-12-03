//
// Created by sergey on 03.12.15.
//

#ifndef REEDSOLOMON_DECODER_H
#define REEDSOLOMON_DECODER_H

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


#endif //REEDSOLOMON_DECODER_H
