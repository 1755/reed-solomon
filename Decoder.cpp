#include "Decoder.h"


Decoder::Decoder(int t)
{
    m_t = t;
    initLogarithmTable();
}

vector<Value> Decoder::decode(vector<Value> codedMessage)
{

    m_n = int(codedMessage.size());

    Polynomial C(codedMessage);
    C.name("C");
    C.debugPrint();

    Polynomial S = calculateSyndromePolynomial(C);
    S.name("S");
    S.debugPrint();

    /** IF ZERO SYNDROME **/
    bool isZeroSyndrome = true;
    for (int i = 0; i < S.size(); ++i) {
        if(S[i] != 0) {
            isZeroSyndrome = false;
        }
    }
    if(isZeroSyndrome) {
        vector<Value> decodedMessage;
        for (int i = 0; i < codedMessage.size() - 2 * m_t; ++i) {
            decodedMessage.push_back(codedMessage[i]);
        }
        return decodedMessage;
    }
    /** IF ZERO SYNDROME **/

    Polynomial LAMBDA = calculateLocatorPolynomial(S);
    LAMBDA.name("LAMBDA");
    LAMBDA.debugPrint();


    // todo: check boundaries
    vector<Value> errorPositions = calculateErrorsPosition(LAMBDA);
    if(Polynomial::debug()) {
        cout << "Error positions: ";
        for (int i = 0; i < errorPositions.size(); ++i) {
            cout << errorPositions[i].get_value() << " ";
        }
        cout << endl;
    }

    Polynomial SIGMA = calculateSigmaPolynomial(S, LAMBDA, errorPositions);
    SIGMA.name("SIGMA");
    SIGMA.debugPrint();

    Polynomial LAMBDAD = calculateLocatorDerivativePolynomial(LAMBDA, errorPositions);
    LAMBDAD.name("LAMBDA'");
    LAMBDAD.debugPrint();


    Polynomial E = calculateCorrectionPolynomial(codedMessage, SIGMA, LAMBDAD, errorPositions);
    E.name("~E");
    E.debugPrint();

    Polynomial F =  C + E;
    F.name("~F");
    F.debugPrint();


    Polynomial SCHECK = calculateSyndromePolynomial(F);
    for (int i = 0; i < SCHECK.size(); ++i) {
        if(SCHECK[i] != 0) {
            throw FixedSyndromeError("Fixed syndrome is't zero");
        }
    }


    vector<Value> decodedMessage;
    for (int i = 0; i < F.size() - 2*m_t; ++i) {
        decodedMessage.push_back(F[i]);
    }

    return decodedMessage;
}

Polynomial Decoder::calculateSyndromePolynomial(const Polynomial &C)
{
    vector<Value> S;
    for (int i = 1; i <= 2 * m_t; ++i) {
        S.push_back(C(Value::pow(2, i)));
    }
//    reverse(S.begin(), S.end());
    return Polynomial(S);
}

Polynomial Decoder::calculateLocatorPolynomial(Polynomial &S)
{
    /*Polynomial LAMBDA({1});
    Polynomial B({1,0});
    int q = 0;
    int L = 0;
    int m = -1;
    Value dq = 0;

    cout << S << endl;

    while(q != 2*m_t) {
        dq = 0;
        for (int i = 0; i <= L; ++i) {
            dq = dq + LAMBDA[LAMBDA.size() - i - 1] * S[q-i];
        }
    }

    exit(1);*/

    // todo: Проверить, то ли я дурак, то ли опечатка в алгоритме
    Polynomial LAMBDA({1});
    Polynomial B({1,0});
    int q = 0;
    int L = 0;
    int m = -1;
    Value dq = 0;

    while(q != 2*m_t) {

        // calculate delta q
        dq = 0;
        for (int i = 0; i <= q; ++i) { // note: in the book q is L
            Value l = 0;
            if(q - i <= LAMBDA.degree()) {
                l = LAMBDA[LAMBDA.degree() - q + i];
            }
            dq = dq + l * S[i]; // note: in the book index is q-i+1
        }
        // calculate delta q

        if(dq != 0) {
            Polynomial LAMBDAA = LAMBDA + dq*B;
            if(L < q - m) {
                int LA = q - m;
                m = q - L;
                L = LA;
                B = dq.get_inverse()*LAMBDA;
            }
            LAMBDA = LAMBDAA;
        }

        B = Polynomial({1,0})*B;

        q = q + 1;
    }

    LAMBDA.debug();

    if(LAMBDA.degree() != L) {
        throw LocatorPolynomialError("Locator polynomial(LAMBDA) did't found");
    }

    return LAMBDA;

}

vector<Value> Decoder::calculateErrorsPosition(Polynomial &LAMBDA)
{
    vector<Value> positions;
    for (int i = 1; i < GF2m::get_field()->get_capacity(); ++i) {
        if(LAMBDA(Value(i)) == 0) {
            Value position = this->log(Value(i).get_inverse());
            if(position.get_value() < 0 || position.get_value() >= m_n) {
                throw LocatorPolynomialError("Locator polynomial(LAMBDA) did't found [3]");
            }
            positions.push_back(position);
        }
    }


    if(positions.size() != LAMBDA.degree()) {
        throw LocatorPolynomialError("Locator polynomial(LAMBDA) did't found [2]");
    }

    return positions;
}

Polynomial Decoder::calculateSigmaPolynomial(Polynomial &S, Polynomial &LAMBDA, vector<Value> errorPositions)
{
    vector<Value> sigma(errorPositions.size());
    for (int q = 0; q < errorPositions.size(); ++q) {
        Value c = 0;
        for (int i = 0; i <= q; ++i) {
            c = c + LAMBDA[LAMBDA.size()-i-1] * S[q-i];
        }
        sigma[q] = c;
    }
    reverse(sigma.begin(), sigma.end());

    return Polynomial(sigma);
}

Polynomial Decoder::calculateLocatorDerivativePolynomial(Polynomial &LAMBDA, vector<Value> &errorsPosition)
{
    vector<Value> derivative(errorsPosition.size());
    for (int j = 1; j < LAMBDA.size(); ++j) {
        if(j%2 == 1) {
            derivative[j] = LAMBDA[j];
        }else{
            derivative[j] = 0;
        }
    }
    return Polynomial(derivative);
}

Polynomial Decoder::calculateCorrectionPolynomial(vector<Value> &codedMessage, Polynomial &SIGMA, Polynomial &LAMBDAD,
                                                  vector<Value> &errorPositions)
{
    vector<Value> corrector(codedMessage.size());
    for (int i = 0; i < codedMessage.size(); ++i) {
        corrector[i] = 0;
    }

    for (int i = 0; i < errorPositions.size(); ++i) {
        int idx = int(codedMessage.size() - errorPositions[i].get_value() - 1);
        Value a = Value::pow(2, errorPositions[i].get_value()).get_inverse();
        corrector[idx] = (SIGMA(a)/LAMBDAD(a));
    }

    return Polynomial(corrector);
}

void Decoder::initLogarithmTable()
{
    m_logarithmsTable = map<int, int>();
    Value a = 2;
    for (int i = 0; i < GF2m::get_field()->get_capacity() - 1; ++i) {
        m_logarithmsTable[Value::pow(a, i).get_value()] = i;
    }

}

Value Decoder::log(const Value &value)
{
    return Value(m_logarithmsTable[value.get_value()]);
}


void Decoder::debug(bool flag)
{
    Polynomial::debug(flag);
}
