#pragma once

#include <vector>
#include "Value.h"

using namespace std;

class Channel {
private:

    int t;
    vector<vector<Value>> messages;

public:

    Channel(int t);

    void add_message(vector<Value> message);

    vector<Value> get_message();

};