#include "GF2m.h"

GF2m *GF2m::field = 0;

void GF2m::set_m(int dim) {
    m = dim;
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
