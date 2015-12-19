#include "Value.h"

GF2m *GF2m::field = 0;

void GF2m::set_m(int dim) {
    m = dim;

    for(int i = 0; i < get_capacity(); i++)
        inverse.push_back(Value::pow(Value(i), get_capacity() - 2));

}


int GF2m::get_m() {
    return m;
}


int GF2m::get_capacity() {
    return 1 << m;
}


vector<int> GF2m::get_p() {
    return polynomials[m - 2];
}
