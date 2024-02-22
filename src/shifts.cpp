//
// Created by m3tr0 on 21.02.2024.
//

#include "../BigNum.h"

BigNum operator<<(const BigNum &a, size_t shift) {
    BigNum result{a.is_negative, a._decimal_precision, a.value};
    if (result.is_zero()) return result;
    while (shift) {
        result.value.push_front(0);
        shift--;
    }
    return result;
}

BigNum operator>>(const BigNum &a, size_t shift) {
    BigNum result{a.is_negative, a._decimal_precision, a.value};
    while (shift && !result.value.empty()) {
        result.value.pop_front();
        shift--;
    }
    return result;
}
