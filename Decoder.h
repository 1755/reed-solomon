#pragma once
#include <vector>
#include <algorithm>
#include "Value.h"
#include "Polynomial.h"

using namespace std;

class Decoder
{
    int m_t;
    map<int, int> m_logarithmsTable; // fixme

public:
    Decoder(int t);
    vector<Value> decode(vector<Value> codedMessage);

    Value log(const Value& value);
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
    vector<Value> calculateErrorsPosition(Polynomial& LAMBDA);
    Polynomial calculateSigmaPolynomial(Polynomial& S, Polynomial& LAMBDA, vector<Value> errorPositions);
    Polynomial calculateLocatorDerivativePolynomial(Polynomial &LAMBDA, vector<Value> &errorsPosition);
    Polynomial calculateCorrectionPolynomial(vector<Value> &codedMessage, Polynomial &SIGMA, Polynomial &LAMBDAD,
                                                 vector<Value> &errorPositions);
private:
    void initLogarithmTable();

};