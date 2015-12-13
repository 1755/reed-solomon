#pragma once
#include <vector>
#include <algorithm>
#include "Value.h"
#include "Polynomial.h"

using namespace std;

class Decoder
{
    int m_t;

public:
    Decoder(int t);
    vector<Value> decode(vector<Value> codedMessage);

public:
    class LocatorPolynomial : Error
    {
    public:
        LocatorPolynomial() : Error() {};
        LocatorPolynomial(const string& message) : Error(message) {};
    };


protected:
    Polynomial calculateSyndromePolynomial(const Polynomial &C);
    Polynomial calculateLocatorPolynomial(Polynomial &S); // fixme: const
    vector<Value> calculateLocatorRoots(Polynomial& LAMBDA);

};