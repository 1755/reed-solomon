#pragma once
#include <vector>

using namespace std;


class Coder {

protected:

    int m;
    int t;


public:

    Coder(int m, int t);

    vector<int> encode(vector<int> data);

};
