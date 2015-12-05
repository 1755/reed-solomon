#include <iostream>
#include <vector>
#include "Value.h"
#include "Coder.h"
#include "Decoder.h"

using namespace std;

int main()
{

    /*Matrix test(4,4);

    srand(123456);
    for (int i = 0; i < test.height(); ++i) {
        for (int j = 0; j < test.width(); ++j) {
            test.setValue(i,j, Value(1+rand()%6) + Value(i) * Value(j));
        }
    }

    cout << "A" << endl;
    cout << test;
    cout << "B" << endl;
    cout << test.reverse();
    cout << "C" << endl;
    cout << test.reverse() * test;


    Matrix test2(2,2);
    test2.setValue(0, 0, Value(5));
    test2.setValue(0, 1, Value(6));
    test2.setValue(1, 0, Value(5));
    test2.setValue(1, 1, Value(5));
    cout << test2;
    cout << test2.reverse();
    cout << test2.reverse() * test2;


    exit(1);*/

    GF2m::get_field()->set_m(3);

    Coder coder = Coder(2);
    Decoder decoder = Decoder(2);

//    vector<Value> message = coder.encode({4, 6, 7});
    vector<Value> message = coder.encode({7, 7, 7});

    for (int i = 0; i < message.size(); i++)
        cout << message[i].get_value() << " ";
    cout << endl;

//    vector<Value> code = {5,2,5,3,3,2,4};

    // add errors
    message[2] = message[2] + Value(5);
    message[4] = message[4] + Value(3);


    vector<Value> decoded = decoder.decode(message);
    cout << "DCODED: " << endl;
    for(auto it = decoded.begin(); it != decoded.end(); it++) {
        cout << (*it).get_value() << " ";
    }
    cout << endl;

    return 0;
}