#include "Decoder.h"


Decoder::Decoder(int t, int m)
{
    m_t = t;
    m_m = m;
}

vector<Value> Decoder::decode(vector<Value> codedMessage)
{
    vector<Value> decodedMessage = codedMessage;
    vector<Value> syndromeVector = getErrorSyndrome(codedMessage);

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

    for(auto it = errorIndexes.begin(); it != errorIndexes.end(); it++) {
        int index = *it;
        decodedMessage[index] = decodedMessage[index] + errorCorrectionVector[index];
    }


    // todo DFT
    decodedMessage = decodedMessage;


    return decodedMessage;
}


vector<Value> Decoder::getErrorSyndrome(const vector<Value> &codedMessage) {
    return std::vector<Value>();
}

vector<Value> Decoder::detectErrorsIndexes(const vector<Value> &locatorVector) {
    return std::vector<Value>();
}

vector<Value> Decoder::calculateCorrectingVector(const vector<Value> &codedMessage, const vector<Value> &locatorVector) {
    return std::vector<Value>();
}

vector<Value> Decoder::calculateLocatorVector(const vector<Value> &syndromeVector) {
    return std::vector<Value>();
}
