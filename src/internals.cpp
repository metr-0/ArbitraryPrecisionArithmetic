//
// Created by m3tr0 on 21.02.2024.
//

#include "../BigNum.h"

void BigNum::normalize() {
    int64_t memo = 0;
    for (int64_t &e : value) {
        e += memo;
        if (e < 0) {
            memo = e / base - 1;
            e = e % base + base;
        } else {
            memo = e / base;
            e %= base;
        }
    }

    while (memo) {
        value.push_back(memo % base);
        memo /= base;
    }

    while (!value.empty() && value.back() == 0)
        value.pop_back();
}

size_t BigNum::decimal_precision() const {
    return _decimal_precision;
}

void BigNum::decimal_precision(size_t x) {
    _decimal_precision = x;
    size_t new_precision = (_decimal_precision + base_exp_ratio - 1) / base_exp_ratio;

    if (new_precision < _precision) *this = *this >> (_precision - new_precision);
    else *this = *this << (new_precision - _precision);
}
