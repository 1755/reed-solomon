#include "Channel.h"
#include <random>
#include <ctime>


Channel::Channel(int t) {
    this->t = t;
}


void Channel::add_message(vector<Value> message) {

    if(this->t > 0) {
        srand((unsigned) (clock() + time(0)));

        int freak = message.size() / t;


        for (int i = 0; i < t; i++) {
            int position = rand() % freak + freak * i;
            message[position] = message[position] + Value(1 + rand() % (GF2m::get_field()->get_capacity() - 1));
        }

    }
    messages.push_back(message);
}


vector<Value> Channel::get_message() {

    if (messages.empty())
        return vector<Value>();

    vector<Value> message = messages.front();
    messages.erase(messages.begin());

    return message;
}
