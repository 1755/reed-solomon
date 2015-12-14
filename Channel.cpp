#include "Channel.h"
#include <random>
#include <ctime>


Channel::Channel(int t) {
    this->t = t;
}


void Channel::add_message(vector<Value> message) {

    srand((unsigned)(clock() + time(0)));

    int freak = message.size() / t;


    for (int i=0; i<t; i++) {
        int position = rand() % freak + freak * i;
        message[position] = message[position] + Value(rand() % message.size());
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
