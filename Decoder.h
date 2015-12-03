#pragma once
#include <vector>
#include "Value.h"

using namespace std;

class Decoder
{
    int m_t = 0;
    int m_m = 0;
public:
    Decoder(int t, int m);
    vector<Value> decode(vector<Value> codedMessage);

private:
    vector<Value> getErrorSyndrome(const vector<Value> &codedMessage);
    vector<int> detectErrorsIndexes(const vector<Value> &locatorVector);
    vector<Value> calculateLocatorVector(const vector<Value> &syndromeVector);
    vector<Value> calculateCorrectingVector(const vector<Value> &codedMessage, const vector<Value> &locatorVector);

};