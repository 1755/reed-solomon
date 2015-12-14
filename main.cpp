#include <iostream>
#include <vector>
#include "Value.h"
#include "Coder.h"
#include "Decoder.h"
#include "Channel.h"
#include "Polynomial.h"
#include "Test.h"

#define DEBUG true

using namespace std;

int main()
{
//    Test test;
//    test.run();
//    return 0;
    GF2m::get_field()->set_m(8);

    Decoder decoder(2);
    decoder.debug(true);

    try {
            vector<Value> testMessage = {213-10, 224, 234 + 2, 229, 240, 5, 61, 81, 228}; // 4 6 7
//        vector<Value> testMessage = {135, 220, 143, 126, 93, 115, 141};
//        vector<Value> testMessage = {187, 111, 92, 208, 233, 152, 78};
//        vector<Value> testMessage = {88, 249, 78, 227, 23, 142};
        vector<Value> decoded = decoder.decode(testMessage);
        for (int i = 0; i < decoded.size(); ++i) {
            cout << decoded[i] << " ";
        }
        cout << endl;
    }catch(Error& e) {
        cout << e.message() << endl;
    }




    return 0;
}