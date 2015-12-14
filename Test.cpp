//
// Created by sergey on 15.12.15.
//

#include "Test.h"

void Test::run()
{
    GF2m::get_field()->set_m(8);

    for (int l = 3; l < 10; ++l) {
        for (int t = 2; t <= l; ++t) {
            cout << "Run test: info.length=" << l << ", t=" << t << ":";
            Coder coder(t);
            Channel channel(t);
            Decoder decoder(t);

            for (int i = 0; i < 1000; ++i) {
                vector<int> infoMessage(l);
                for (int j = 0; j < infoMessage.size(); ++j) {
                    infoMessage[j] = rand()%(GF2m::get_field()->get_capacity() - 1);
                }

                vector<Value> code;
                vector<Value> codeWithErrors;
                vector<Value> decode;
                try {

                    code = coder.encode(infoMessage);
                    channel.add_message(code);
                    codeWithErrors = channel.get_message();
                    decode = decoder.decode(codeWithErrors);


                }catch(Error& e) {
                    cout << "\n [" << i << "] Error: " << e.message() << endl;

                    cout << "I: ";
                    for (int j = 0; j < infoMessage.size(); ++j) {
//                        cout << infoMessage[j] << " ";
                        printf("%3d ", infoMessage[j]);
                    }
                    cout << endl;

                    cout << "C: ";
                    for (int j = 0; j < code.size(); ++j) {
//                        cout << code[j] << " ";
                        printf("%3d ", code[j].get_value());
                    }
                    cout << endl;

                    cout << "E: ";
                    for (int j = 0; j < codeWithErrors.size(); ++j) {
//                        cout << codeWithErrors[j] << " ";
                        printf("%3d ", codeWithErrors[j].get_value());

                    }
                    cout << endl;

                    cout << "D: ";
                    for (int j = 0; j < decode.size(); ++j) {
//                        cout << decode[j] << " ";
                        printf("%3d ", decode[j].get_value());
                    }
                    cout << endl;


                    exit(100);
                    break;
                }
            }
            cout << endl;
        }
    }
}
