#include "Decoder.h"


Decoder::Decoder(int t, int m)
{
    m_t = t;
    m_m = m;
}

vector<Value> Decoder::decode(vector<Value> codedMessage)
{
    cout << "CODED: " << endl;
    for(auto it = codedMessage.begin(); it != codedMessage.end(); it++) {
        cout << (*it).get_value() << " ";
    }
    cout << endl;

    DFT dft;
    updateCodedMessageInfo(codedMessage);


    vector<Value> decodedMessage = dft.forward(codedMessage);
    vector<Value> syndromeVector = getSyndromeVector(decodedMessage);
    bool isZeroSyndrome = true;
    for(auto it = syndromeVector.begin(); it != syndromeVector.end(); it++) {
        if(*it != Value(0)) {
            isZeroSyndrome = false;
            break;
        }
    }
    if(isZeroSyndrome) {
        return decodedMessage;
    }

    vector<Value> locatorVector = calculateLocatorVector(syndromeVector);
    cout << "LOCATOR: " << endl;
    for(auto it = locatorVector.begin(); it != locatorVector.end(); it++) {
        cout << (*it).get_value() << " ";
    }
    cout << endl;
    
    vector<int> errorIndexes = detectErrorsIndexes(locatorVector);
    cout << "ERROR INDEXES: " << endl;
    for(auto it = errorIndexes.begin(); it != errorIndexes.end(); it++) {
        cout << (*it) << " ";
    }
    cout << endl;

    vector<Value> errorCorrectionVector = calculateCorrectingVector(decodedMessage, locatorVector);
    cout << "CORRECTOR VECTOR: " << endl;
    for(auto it = errorCorrectionVector.begin(); it != errorCorrectionVector.end(); it++) {
        cout << (*it).get_value() << " ";
    }
    cout << endl;


    decodedMessage = codedMessage;
    for (int i = 0; i < errorCorrectionVector.size(); ++i) {
        decodedMessage[i] = decodedMessage[i] + correctorPolynomial(errorCorrectionVector, Value::pow(Value(2), i));
    }


    decodedMessage = dft.forward(decodedMessage);

    return decodedMessage;
}


vector<Value> Decoder::getSyndromeVector(const vector<Value> &decodedMessage)
{
    vector<Value> syndromeVector;
    for (int i = m_n; i < decodedMessage.size(); ++i) {
        syndromeVector.push_back(decodedMessage[i]);
    }
    return syndromeVector;
}

vector<int> Decoder::detectErrorsIndexes(const vector<Value> &locatorVector)
{
    vector<int> errorsIndexes;
    for (int i = 0; i < m_codedMessageSize; ++i) {
        Value v = locatorPolinomial(locatorVector, Value::pow(Value(2), i));
        if(v == Value(0)) {
            errorsIndexes.push_back(i);
        }
    }

    return errorsIndexes;
}

vector<Value> Decoder::calculateCorrectingVector(const vector<Value> &decodedMessage, const vector<Value> &locatorVector)
{
    vector<Value> correctorVector = decodedMessage;
    for (int i = m_n - 1; i >= 0; --i) {
        correctorVector[i] = 0;
        for (int j = 1; j < locatorVector.size(); ++j) {
            correctorVector[i] = correctorVector[i] + locatorVector[j]*correctorVector[i + j];
        }
        correctorVector[i] = correctorVector[i] * locatorVector[0].get_inverse();
    }


    return correctorVector;
}

vector<Value> Decoder::calculateLocatorVector(const vector<Value> &syndromeVector)
{
    vector<Value> locatorVector;
    Matrix M(2, m_t);
    Matrix L(m_t, 1);

    for (int i = m_t; i > 0; --i) {
        M.setValue(0, i-1, syndromeVector[m_t - i]);
        M.setValue(1, i-1, syndromeVector[m_t - 1 + (m_t - i)]);
    }

    int j = 0;
    for (int i = int(syndromeVector.size() - m_t); i < int(syndromeVector.size()); ++i) {
        L.setValue(j, 0, syndromeVector[i]);
        j++;
    }

    Matrix V = M.reverse() * L;


    for (int i = V.height() - 1; i >= 0; --i) {
        locatorVector.push_back(V.getValue(i, 0));
    }
    locatorVector.push_back(Value(1));


    // transform to the normal form
    Value inv = locatorVector[0].get_inverse();
    for (int i = 0; i < locatorVector.size(); ++i) {
        locatorVector[i] = locatorVector[i] * inv;
    }

    return locatorVector;
}

void Decoder::updateCodedMessageInfo(const vector<Value> &codedMessage)
{
    m_n = int(codedMessage.size() - 2*m_t);
    m_o = 2*m_t;
    m_codedMessageSize = int(codedMessage.size());

}

vector<Value> Decoder::getInfoVector(const vector<Value> &codedMessage)
{
    vector<Value> infoVector;
    for (int i = 0; i < m_n; ++i) {
        infoVector.push_back(codedMessage[i]);
    }
    return infoVector;
}

Value Decoder::locatorPolinomial(const vector<Value> &locatorVector, Value x) {
    Value v = Value(0);
    for (int i = 0; i < locatorVector.size(); ++i) {
        v = v + locatorVector[i] * Value::pow(x, int(locatorVector.size() - i - 1));
    }

    return v;
}

Value Decoder::correctorPolynomial(const vector<Value> &correctorVector, Value x)
{
    Value v = Value(0);
    for (int i = 0; i < correctorVector.size(); ++i) {
        v = v + correctorVector[i] * Value::pow(x, i);
    }

    return v;
}
