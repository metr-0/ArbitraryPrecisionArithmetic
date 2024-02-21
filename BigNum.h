//
// Created by metro on 20.02.2024.
//

#pragma once

#ifndef BIGNUM_BIGNUM_H
#define BIGNUM_BIGNUM_H

#include <string>
#include <deque>
#include <iostream>
#include <compare>

class BigNum {
private:
    explicit BigNum(bool _is_negative, size_t _decimal_precision, std::deque<int64_t>  _value);

    static const int64_t base = 1000000000LL;
    static const int64_t decimal_base = 10LL;
    static const int64_t base_exp_ratio = 9LL;

    bool is_negative;
    size_t precision, decimal_precision;
    std::deque<int64_t> value;

    void normalize();
public:
    explicit BigNum();
    explicit BigNum(const char *s);

    friend BigNum operator+(const BigNum &a);
    friend BigNum operator-(const BigNum &a);

    // base arithmetic
    friend BigNum operator+(const BigNum &a, const BigNum &b);
    friend BigNum operator-(const BigNum &a, const BigNum &b);
    friend BigNum operator*(const BigNum &a, const BigNum &b);
    friend BigNum operator/(const BigNum &a, const BigNum &b);

    // comparisons
    friend std::strong_ordering operator<=>(const BigNum &a, const BigNum &b);
    friend bool operator==(const BigNum &a, const BigNum &b);
    friend bool operator!=(const BigNum &a, const BigNum &b);
    friend bool operator<(const BigNum &a, const BigNum &b);
    friend bool operator>(const BigNum &a, const BigNum &b);
    friend bool operator<=(const BigNum &a, const BigNum &b);
    friend bool operator>=(const BigNum &a, const BigNum &b);

    // shifts
    friend BigNum operator<<(const BigNum &a, size_t shift);
    friend BigNum operator>>(const BigNum &a, size_t shift);

    // output
    friend std::ostream &operator<<(std::ostream &out, const BigNum &a);
    [[nodiscard]] std::string to_string() const;
};

BigNum operator""_bn(const char *s);

#endif //BIGNUM_BIGNUM_H