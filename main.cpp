#include <iostream>
#include "Decoder.h"

using namespace std;

int main() {

    Decoder decoder(3, 8);
    vector<int> coded_message = {1,2,3,4,5};
    vector<int> decoded_message = decoder.decode(coded_message);
    for(auto it = decoded_message.begin(); it != decoded_message.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";

//    cout << decoder.decode();

    return 0;
}