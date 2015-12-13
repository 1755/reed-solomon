#include "Decoder.h"


Decoder::Decoder(int t)
{
    m_t = t;
}

vector<Value> Decoder::decode(vector<Value> codedMessage)
{
    cout << "CODED: " << endl;
    for(auto it = codedMessage.begin(); it != codedMessage.end(); it++) {
        cout << (*it).get_value() << " ";
    }
    cout << endl << endl;

    Polynomial C(codedMessage);
    C.name("C");
    cout << C << endl;

    Polynomial S = calculateSyndromePolynomial(C);
    S.name("S");
    cout << S << endl;

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
    cout << LAMBDA << endl;

    /** CALCULATE LOCATOR'S ROOTS **/
    vector<Value> locatorRoots = calculateLocatorRoots(LAMBDA);
    cout << "Locator roots: ";
    for (int i = 0; i < locatorRoots.size(); ++i) {
        cout << locatorRoots[i].get_value() << " ";
    }
    cout << endl;
    /** CALCULATE LOCATOR'S ROOTS **/

    if(locatorRoots.size() != LAMBDA.degree()) {
        throw exception(); // todo: throw "true" exception
    }

    for (int alpha = 0; alpha < GF2m::get_field()->get_capacity(); ++alpha) {
        for (int u = 0; alpha < GF2m::get_field()->get_capacity(); ++u) {
            if(locatorRoots[0] == Value(1)/Value(Value::pow(alpha, u))) {
                cout << u << endl;
            }
        }
    }



    return codedMessage;
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

    if(LAMBDA.degree() != L) {
        throw LocatorPolynomial("Locator polynomial(LAMBDA) did't found");
    }

    return LAMBDA;

}

vector<Value> Decoder::calculateLocatorRoots(Polynomial &LAMBDA)
{
    vector<Value> roots;
    for (int i = 1; i < GF2m::get_field()->get_capacity(); ++i) {
        if(LAMBDA(Value(i)) == 0) {
            roots.push_back(Value(i));
        }
    }
    return roots;
}
