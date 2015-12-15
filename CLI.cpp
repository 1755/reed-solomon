//
// Created by sergey on 15.12.15.
//

#include "CLI.h"

void CLI::run()
{
    int t = 0;
    int min_t = 1;
    string message;
    string messageWithError;
    string messageDecoded;
    string garbage;

    cout << "CLI RUNNED" << endl;
    while(t <= min_t) {
        cout << "Enter t: ";
        cin >> t;
        if(t <= min_t) {
            cout << "t must be greater then " << min_t << endl;
            exit(111);
        }
    }

    GF2m::get_field()->set_m(8);
    Coder coder(t);
    Decoder decoder(t);

    while(true) {
        cout << "Enter message: ";
//        cin.clear();
        cin.ignore(256, '\n');
        getline(cin, message);
        message = message.substr(0, (unsigned long) (255 - 2*t));
        if(message == "exit") {
            break;
        }
        if(message.empty()) {
            continue;
        }
        cout << "M:  " << message << " (" << message.length() << ") " << endl << flush;

        // encode
        vector<int> data;
        for (int i = 0; i < message.length(); ++i) {
            data.push_back(int(message[i]));
        }
        vector<Value> codeVector = coder.encode(data);
        // encode

        for (int tao = 0; tao <= t; ++tao) {
            cout << "tao = " << tao << endl;
            Channel channel(tao);

            // corrupt message
            channel.add_message(codeVector);
            vector<Value> corruptedVector = channel.get_message();
            messageWithError.clear();
            for (int i = 0; i < message.length(); ++i) {
                messageWithError.push_back(char(corruptedVector[i].get_value()));
            }

            cout << "   ME: " << messageWithError  << " (" << messageWithError.length() << ") " << endl << flush;
            // corrupt message

            try {
                // repair message
                vector<Value> decodeVector = decoder.decode(corruptedVector);
                messageDecoded.clear();
                for (int i = 0; i < message.length(); ++i) {
                    messageDecoded.push_back(char(decodeVector[i].get_value()));
                }
                cout << "   MD: " << messageDecoded << " (" << messageDecoded.length() << ") " << endl << flush;
                // repair message
            }catch (Error& e) {
                cout << e.message() << endl;
            }
            cout << endl;

        }

    }

}
