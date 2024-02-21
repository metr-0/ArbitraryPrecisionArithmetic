//
// Created by m3tr0 on 21.02.2024.
//

#include "../BigNum.h"

// Karatsuba multiplication. Source https://habr.com/ru/articles/124258/
BigNum operator*(const BigNum &a, const BigNum &b) {
    static const size_t min_size = 5;

    if (a.is_negative || b.is_negative || a.precision || b.precision) {
        BigNum na{false, 0, a.value}, nb{false, 0, b.value};
        BigNum res = na * nb;

        res.is_negative = a.is_negative != b.is_negative;
        res.decimal_precision = a.decimal_precision + b.decimal_precision;
        res.precision = (res.decimal_precision + BigNum::base_exp_ratio - 1) / BigNum::base_exp_ratio;
        for (int i = 0; i < a.precision + b.precision - res.precision; i++)
            res.value.pop_front();

        return res;
    }
    // => a, b positive and integer

    // recursion base:
    if (a.value.size() < min_size || b.value.size() < min_size) {
        BigNum result{false, 0, std::deque<int64_t>(
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

BigNum operator/(const BigNum &a, const BigNum &b) {
    return a;
}
