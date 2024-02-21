//
// Created by m3tr0 on 21.02.2024.
//

#include "../BigNum.h"

BigNum operator+(const BigNum &a) {
    return BigNum{a.is_negative, a._decimal_precision, a.value};
}

BigNum operator-(const BigNum &a) {
    return BigNum{!a.is_negative, a._decimal_precision, a.value};
}
