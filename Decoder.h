#pragma once
#include <vector>
#include <algorithm>
#include "Value.h"
#include "DFT.h"
#include "Matrix.h"

using namespace std;

class Decoder
{
    int m_t = 0; // количество максимально возможных исправлений ошибок
    int m_m = 0; // степень поля
    int m_n = 0; // количество информационных символов
    int m_o = 0; // количество избыточных символов
    int m_codedMessageSize;

public:
    Decoder(int t, int m);
    vector<Value> decode(vector<Value> codedMessage);

private:
    vector<Value> getInfoVector(const vector<Value>& codedMessage);
    vector<Value> getSyndromeVector(const vector<Value> &decodedMessage);
    vector<int> detectErrorsIndexes(const vector<Value> &locatorVector);
    vector<Value> calculateLocatorVector(const vector<Value> &syndromeVector);
    vector<Value> calculateCorrectingVector(const vector<Value> &decodedMessage, const vector<Value> &locatorVector);
    Value correctorPolynomial(const vector<Value>& correctorVector, Value x);
    Value locatorPolinomial(const vector<Value> &locatorVector, Value x);

    void updateCodedMessageInfo(const vector<Value> &codedMessage);

};