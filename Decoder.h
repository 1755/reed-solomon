#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include "Value.h"
#include "Polynomial.h"

using namespace std;

class Decoder
{
    int m_t;
    int m_n;
    map<int, int> m_logarithmsTable; // fixme

public:
    Decoder(int t);
    vector<Value> decode(vector<Value> codedMessage);

    Value log(const Value& value);
    void debug(bool flag);

public:


    class FixedSyndromeError : public Error
    {
    public:
        FixedSyndromeError() : Error() {};
        FixedSyndromeError(const string& message) : Error(message) {};
    };


    class LocatorPolynomialError : public Error
    {
    public:
        LocatorPolynomialError() : Error() {};
        LocatorPolynomialError(const string& message) : Error(message) {};
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