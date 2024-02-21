//
// Created by m3tr0 on 21.02.2024.
//

#include "BigNum.h"

BigNum BigNum::operator+() const {
    return BigNum{is_negative, decimal_precision, value};
}

BigNum BigNum::operator-() const {
    return BigNum{!is_negative, decimal_precision, value};
}
