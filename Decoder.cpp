#include "Decoder.h"


Decoder::Decoder(int t, int m)
{
    m_t = t;
    m_m = m;
}

vector<Value> Decoder::decode(vector<Value> codedMessage)
{
    DFT dft;
    updateCodedMessageInfo(codedMessage);


    vector<Value> decodedMessage = dft.forward(codedMessage);
    vector<Value> syndromeVector = getSyndromeVector(codedMessage);

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
    vector<int> errorIndexes = detectErrorsIndexes(locatorVector);
    vector<Value> errorCorrectionVector = calculateCorrectingVector(codedMessage, locatorVector);

    decodedMessage = codedMessage;
    for(auto it = errorIndexes.begin(); it != errorIndexes.end(); it++) {
        int index = *it;
        decodedMessage[index] = codedMessage[index] + errorCorrectionVector[index];
    }


    decodedMessage = dft.forward(decodedMessage);


    return decodedMessage;
}


vector<Value> Decoder::getSyndromeVector(const vector<Value> &codedMessage)
{
    vector<Value> syndromeVector;
    for (int i = m_n; i < syndromeVector.size(); ++i) {
        syndromeVector.push_back(codedMessage[i]);
    }
    return syndromeVector;
}

vector<int> Decoder::detectErrorsIndexes(const vector<Value> &locatorVector)
{
    vector<int> errorsIndexes;
    for (int i = 0; i < pow(2, m_m); ++i) {
        Value x = Value(2); // todo: primirive element in degree
        Value c = Value(1);
        for (int j = 0; j < locatorVector.size(); ++j) {
            c = c + locatorVector[j] * x; // todo: degree
        }
        if(c == Value(0)) {
            errorsIndexes.push_back(i);
        }
    }

    return errorsIndexes;
}

vector<Value> Decoder::calculateCorrectingVector(const vector<Value> &codedMessage, const vector<Value> &locatorVector) {
    return std::vector<Value>();
}

vector<Value> Decoder::calculateLocatorVector(const vector<Value> &syndromeVector)
{
    vector<Value> locatorVector;
    Matrix M(2, m_t);
    Matrix L(m_t, 1);
    Matrix V(m_t, 2);

    for (int i = m_t; i >= 0; --i) {
        M.setValue(0, i, syndromeVector[m_t - i]);
        M.setValue(1, i, syndromeVector[m_t - 1 + (m_t - i)]);
    }

    for (int i = m_t - 2; i < 2*m_t - 2; ++i) {
        L.setValue(i, 0, syndromeVector[i]);
        V.setValue(i, 0, Value(0));
    }


    V = M.reverse() * L;
    locatorVector.push_back(Value(1));
    for (int i = 0; i < V.height(); ++i) {
        locatorVector.push_back(V.getValue(i, 0));
    }


    // todo: transform to the normal form
    reverse(locatorVector.begin(), locatorVector.end());


    return locatorVector;
}

void Decoder::updateCodedMessageInfo(const vector<Value> &codedMessage)
{
    m_n = int(codedMessage.size() - 2*m_t);
    m_o = 2*m_t;

}

vector<Value> Decoder::getInfoVector(const vector<Value> &codedMessage)
{
    vector<Value> infoVector;
    for (int i = 0; i < m_n; ++i) {
        infoVector.push_back(codedMessage[i]);
    }
    return infoVector;
}
