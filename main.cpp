#include <iostream>
#include <vector>
#include "Value.h"
#include "Coder.h"
#include "Decoder.h"
#include "Channel.h"

using namespace std;

int main()  {

    GF2m::get_field()->set_m(8);

    Coder coder = Coder(2);

    vector<Value> message = coder.encode({4, 6, 7});

    for (int i = 0; i < message.size(); i++) {
        cout << message[i].get_value() << " ";
    }

    return 0;
}