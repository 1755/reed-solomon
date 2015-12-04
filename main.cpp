#include <iostream>
#include <vector>
#include "Value.h"
#include "Coder.h"
#include "Decoder.h"

using namespace std;

int main() {

    Coder coder = Coder(3, 2);
    Decoder decoder = Decoder(2, 3);

    vector<int> message = coder.encode({4, 6, 7, 0, 0, 0, 0});

    for (int i = 0; i < message.size(); i++)
        cout << message[i] << " ";


    vector<Value> testCode = {5,2,5,3,3,2,4};
    vector<Value> decoded = decoder.decode(testCode);

    return 0;
}