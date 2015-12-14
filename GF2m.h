#pragma once

#include <vector>
#include <map>

using namespace std;

class GF2m {

private:

    vector<vector<int>> polynomials = {
            {1, 1, 1}, // 2
            {1, 0, 1, 1}, // 3
            {1, 0, 0, 1, 1}, // 4
            {1, 0, 0, 1, 0, 1}, // 5
            {1, 0, 0, 0, 0, 1, 1}, // 6
            {1, 0, 0, 0, 1, 0, 0, 1}, // 7
            {1, 0, 0, 0, 1, 1, 1, 0, 1}, // 8
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 1}, // 9
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, // 10
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, // 11
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1}, // 12
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1}, // 13
            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1}, // 14
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, // 15
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1} // 16
    };


    static GF2m *field;
    GF2m() {}

    int m;

public:

    static GF2m *get_field() {
        if(!field)
            field = new GF2m();



        return field;
    }

    void set_m(int dim);

    int get_m();

    int get_capacity();

    vector<int> get_p();
};