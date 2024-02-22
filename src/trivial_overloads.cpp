//
// Created by m3tr0 on 22.02.2024.
//

#include "../BigNum.h"

BigNum operator+(const BigNum &a, int64_t b) {
    return a + BigNum{b};
}

BigNum operator-(const BigNum &a, int64_t b) {
    return a - BigNum{b};
}

BigNum operator*(const BigNum &a, int64_t b) {
    return a * BigNum{b};
}

BigNum operator/(const BigNum &a, int64_t b) {
    return a / BigNum{b};
}

BigNum operator%(const BigNum &a, int64_t b) {
    return a % BigNum{b};
}

BigNum &operator+=(BigNum &a, const BigNum &b) {
    return a = a + b;
}

BigNum &operator+=(BigNum &a, int64_t b) {
    return a = a + b;
}

BigNum &operator-=(BigNum &a, const BigNum &b) {
    return a = a - b;
}

BigNum &operator-=(BigNum &a, int64_t b) {
    return a = a - b;
}

BigNum &operator*=(BigNum &a, const BigNum &b) {
    return a = a * b;
}

BigNum &operator*=(BigNum &a, int64_t b) {
    return a = a * b;
}

BigNum &operator/=(BigNum &a, const BigNum &b) {
    return a = a / b;
}

BigNum &operator/=(BigNum &a, int64_t b) {
    return a = a / b;
}

BigNum &operator%=(BigNum &a, const BigNum &b) {
    return a = a % b;
}

BigNum &operator%=(BigNum &a, int64_t b) {
    return a = a % b;
}

BigNum &operator<<=(BigNum &a, size_t shift) {
    return a = a << shift;
}

BigNum &operator>>=(BigNum &a, size_t shift) {
    return a = a >> shift;
}
