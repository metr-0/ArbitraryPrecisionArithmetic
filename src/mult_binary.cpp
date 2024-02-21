//
// Created by m3tr0 on 21.02.2024.
//

#include "../BigNum.h"

// Karatsuba multiplication. Source https://habr.com/ru/articles/124258/
BigNum operator*(const BigNum &a, const BigNum &b) {
    static const size_t min_size = 5;

    if (a.is_negative || b.is_negative || a._precision || b._precision) {
        BigNum na{a.value}, nb{b.value};
        BigNum res = na * nb;

        res.is_negative = a.is_negative != b.is_negative;
        res._decimal_precision = a._decimal_precision + b._decimal_precision;
        res._precision = (res._decimal_precision + BigNum::base_exp_ratio - 1) / BigNum::base_exp_ratio;
        for (int i = 0; i < a._precision + b._precision - res._precision; i++)
            res.value.pop_front();

        return res;
    }
    // => a, b positive and integer

    // recursion base:
    if (a.value.size() < min_size || b.value.size() < min_size) {
        BigNum result{std::deque<int64_t>(
                a.value.size() + b.value.size() - 1, 0)};
        for (size_t ai = 0; ai < a.value.size(); ai++)
            for (size_t bi = 0; bi < b.value.size(); bi++)
                result.value[ai + bi] += a.value[ai] * b.value[bi];

        result.normalize();
        return result;
    }

    BigNum a1, a2, b1, b2;
    size_t n = std::max(a.value.size(), b.value.size());
    if (n % 2) n++;
    size_t m = n / 2;
    for (size_t i = 0; i < n; i++) {
        int64_t ta = (i >= a.value.size()) ? 0 : a.value[i];
        int64_t tb = (i >= b.value.size()) ? 0 : b.value[i];
        if (i < m) {
            a1.value.push_back(ta);
            b1.value.push_back(tb);
        } else {
            a2.value.push_back(ta);
            b2.value.push_back(tb);
        }
    }

    BigNum t1 = a1 * b1, t2 = a2 * b2;
    return t1 + (((a1 + a2) * (b1 + b2) - t1 - t2) << m) + (t2 << (m * 2));
}

std::pair<BigNum, BigNum> div_mod(const BigNum &a, const BigNum &b) {
    if (b == 0_bn) {
        throw std::runtime_error("Division by zero");
    }
    // => b != 0

    if (a.is_negative || b.is_negative || a._precision || b._precision) {
        BigNum na{a.value}, nb{b.value};
        na = na << b._precision;

        std::pair<BigNum, BigNum> res = div_mod(na, nb);
        res.first._precision = a._precision, res.first._decimal_precision = a._decimal_precision;
        res.first.is_negative = a.is_negative != b.is_negative;

        return res;
    }
    // => a, b positive and integer

    if (b > a) return std::pair<BigNum, BigNum>{BigNum{}, a};

    std::pair<BigNum, BigNum> t = div_mod(a >> 1, b);
    t.second = t.second << 1;
    t.second.value[0] = a.value[0];

    // b * le always <= t.second; b * ri always > t.second
    int64_t le = 0, ri = BigNum::base, mid;
    while (ri - le != 1) {
        mid = (le + ri) / 2;
        BigNum test = BigNum{mid};
        if (b * BigNum{mid} <= t.second) le = mid;
        else ri = mid;
    }

    t.first = t.first << 1;
    t.first.value[0] = le;
    t.second = t.second - b * BigNum{mid};

    return t;
}

BigNum operator/(const BigNum &a, const BigNum &b) {
    std::pair<BigNum, BigNum> res = div_mod(a, b);
    return res.first;
}

BigNum operator%(const BigNum &a, const BigNum &b) {
    std::pair<BigNum, BigNum> res = div_mod(a, b);
    return res.second;
}
