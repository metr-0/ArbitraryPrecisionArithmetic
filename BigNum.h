//
// Created by metro on 20.02.2024.
//

#ifndef BIGNUM_BIGNUM_H
#define BIGNUM_BIGNUM_H


#include <string>
#include <deque>
#include <iostream>

class BigNum {
private:
    static const int64_t base = 1000000000LL;
    static const int64_t decimal_base = 10LL;
    static const int64_t base_exp_ratio = 9LL;

    bool is_negative;
    size_t precision, decimal_precision;
    std::deque<int64_t> value;
public:
    explicit BigNum(const char *s);

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

    friend std::ostream &operator<<(std::ostream &out, const BigNum &a);

    // conversion
    [[nodiscard]] std::string to_string() const;
};

BigNum operator""_bn(const char *s);

#endif //BIGNUM_BIGNUM_H
