#include "Coder.h"

Coder::Coder(unsigned t) {
    this->t = t;
}

vector<Value> Coder::encode(vector<int> data) {

    unsigned r = t*2;

    vector<Value> G_prev;
    vector<Value> G_cur = vector<Value>(r+1);
    G_prev.push_back(1);
    G_cur[0] = 1;
    for (int i = 1; i <= r; i++) {
        G_prev.push_back(0);
    }

    for (int s = 1; s <= r; s++) {

        for (int j = 0; j <= s; j++) {

            if (j == 0) {
                G_cur[0] = G_prev[0] * Value::pow(2, s);
            }
            else if (j > 0 && j < s) {
                G_cur[j] = G_prev[j-1] + G_prev[j] * Value::pow(2, s);
            }
            else  if (j == s) {
                G_cur[j] = G_prev[j-1];
            }
        }

        G_prev = G_cur;
    }

    vector<Value> G;
    for (int i = 0; i < G_cur.size(); i++) {
        G.push_back(G_cur[G_cur.size() - i - 1]);
    }


    vector<Value> M;
    for (int i = 0; i < data.size(); i++) {
        M.push_back(data[i]);
    }

    vector<Value> R = reminder(M, G);

    for (int i = 0; i < R.size(); i++) {
        M.push_back(R[i]);
    }


//    Value check = 0;
//
//    for (int i = 1; i <= r; i++) {
//        for (int k = 0; k < M.size(); k++) {
//            check = check + M[k]*Value::pow(Value::pow(2, i), M.size() - k - 1);
//        }
//    }

    return M;
}

vector<Value> Coder::reminder(vector<Value> dividend, vector<Value> divider) {

    for (int i = 0; i < t*2; i++) {
        dividend.push_back(0);
    }

    while (dividend.size() >= divider.size()) {

        Value mul = dividend[0];
        Value div = divider[0];

        for (int i = 0; i < divider.size(); i++) {
            dividend[i] = dividend[i] + mul*(divider[i]/div);
        }

        while (dividend.front() == 0 && !dividend.empty()) {
            dividend.erase(dividend.begin());
        }
    }

    return dividend;
}
