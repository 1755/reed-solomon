#pragma once

class GF2m {

private:
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
};