//
// Created by metro on 20.02.2024.
//

#ifndef ARBITRARYPRECISIONARITHMETIC_BIGNUM_H
#define ARBITRARYPRECISIONARITHMETIC_BIGNUM_H


#include <xstring>

class BigNum {
public:
    // base arithmetic
    friend BigNum operator+(const BigNum &a, const BigNum &b);
    friend BigNum operator-(const BigNum &a, const BigNum &b);
    friend BigNum operator*(const BigNum &a, const BigNum &b);
    friend BigNum operator/(const BigNum &a, const BigNum &b);

    // comparisons
    friend bool operator==(const BigNum &a, const BigNum &b);
    friend bool operator!=(const BigNum &a, const BigNum &b);
    friend bool operator<(const BigNum &a, const BigNum &b);
    friend bool operator>(const BigNum &a, const BigNum &b);

    // conversion
    [[nodiscard]] std::string toString(size_t precision) const;
};

BigNum operator""_bn(const char *s);

#endif //ARBITRARYPRECISIONARITHMETIC_BIGNUM_H
