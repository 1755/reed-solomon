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
    cout << endl;


    return codedMessage;
}