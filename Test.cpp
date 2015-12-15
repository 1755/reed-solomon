//
// Created by sergey on 15.12.15.
//

#include "Test.h"

void Test::run()
{
    GF2m::get_field()->set_m(8);

    int max_iter = 500;
    int over_t = 2;
    int max_info_length = 5;

    for (int l = 3; l <= max_info_length; ++l) {
        for (int t = 2; t <= l; ++t) {
            Coder coder(t);
            Decoder decoder(t);
            for (int tao = 0; tao <= t + over_t; ++tao) {
                cout << "Run test: info.length=" << l << ", t=" << t << ", tao=:" << tao << flush;
                Channel channel(tao);

                int errors = 0;
                clock_t begin_time = clock();
                for (int i = 0; i < max_iter; ++i) {
                    vector<int> infoMessage(l);
                    for (int j = 0; j < infoMessage.size(); ++j) {
//                        infoMessage[j] = rand()%(GF2m::get_field()->get_capacity() - 1);
                        infoMessage[j] = 32 + rand()%(127);
                    }

                    vector<Value> code;
                    vector<Value> codeWithErrors;
                    vector<Value> decode;
                    try {

                        code = coder.encode(infoMessage);
                        channel.add_message(code);
                        codeWithErrors = channel.get_message();


                        decode = decoder.decode(codeWithErrors);

                        if(infoMessage.size() != decode.size()) {
                            throw Error("Is't equal");
                        }
                        for (int loa = 0; loa < infoMessage.size(); ++loa) {
                            if(infoMessage[loa] != decode[loa].get_value()) {
                                throw Error("Is't equal");
                            }
                        }
//                        cout << endl;
//
//                        for (int loa = 0; loa < decode.size(); ++loa) {
//                            cout << decode[loa] << " ";
//                        }
//                        cout << endl;
//
//                        exit(222);

                    }catch(Error& e) {
//                        if(e.message() == "Is't equal") {
//                            cout << "FUCK!" << endl;
//                        }

                        /*cout << "\n [" << i << "] Error: " << e.message() << endl;

                        cout << "I: ";
                        for (int j = 0; j < infoMessage.size(); ++j) {
                            printf("%3d ", infoMessage[j]);
                        }
                        cout << endl;

                        cout << "C: ";
                        for (int j = 0; j < code.size(); ++j) {
                            printf("%3d ", code[j].get_value());
                        }
                        cout << endl;

                        cout << "E: ";
                        for (int j = 0; j < codeWithErrors.size(); ++j) {
                            printf("%3d ", codeWithErrors[j].get_value());

                        }
                        cout << endl;

                        cout << "D: ";
                        for (int j = 0; j < decode.size(); ++j) {
                            printf("%3d ", decode[j].get_value());
                        }
                        cout << endl;*/
                        errors++;


//                    exit(100);
//                    break;
                    }catch(Polynomial::IndexError& e) {
                        cout << "\n [" << i << "] Error: " << e.message() << endl;

                        cout << "I: ";
                        for (int j = 0; j < infoMessage.size(); ++j) {
                            printf("%3d ", infoMessage[j]);
                        }
                        cout << endl;

                        cout << "C: ";
                        for (int j = 0; j < code.size(); ++j) {
                            printf("%3d ", code[j].get_value());
                        }
                        cout << endl;

                        cout << "E: ";
                        for (int j = 0; j < codeWithErrors.size(); ++j) {
                            printf("%3d ", codeWithErrors[j].get_value());

                        }
                        cout << endl;

                        cout << "D: ";
                        for (int j = 0; j < decode.size(); ++j) {
                            printf("%3d ", decode[j].get_value());
                        }
                        cout << endl;
                        errors++;
                    }
                }
                clock_t end_time = clock();
                cout << " finished. ";
                cout << "Accuracy: " << double(max_iter - errors)/max_iter << ". ";
                cout << "Time: " << double(end_time - begin_time)/CLOCKS_PER_SEC << endl;
            }

            cout << endl;
        }
    }
}
