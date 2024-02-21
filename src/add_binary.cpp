//
// Created by m3tr0 on 21.02.2024.
//

#include "../BigNum.h"

BigNum operator+(const BigNum &a, const BigNum &b) {
    if (a.is_negative && !b.is_negative) return b - (-a);
    if (b.is_negative && !a.is_negative) return a - (-b);

    size_t da, db;
    if (a.precision > b.precision) {
        da = 0; db = a.precision - b.precision;
    } else {
        da = b.precision - a.precision; db = 0;
    }
    const size_t upper = std::max(a.value.size() + da, b.value.size() + db);

    std::deque<int64_t> new_value;

    for (size_t i = 0; i < upper; i++) {
        int64_t av = (i < da || i - da >= a.value.size()) ? 0 : a.value[i - da];
        int64_t bv = (i < db || i - db >= b.value.size()) ? 0 : b.value[i - db];

        new_value.push_back(av + bv);
    }

    BigNum result{a.is_negative, std::max(a.decimal_precision, b.decimal_precision), new_value};
    result.normalize();
    return result;
}

BigNum operator-(const BigNum &a, const BigNum &b) {
    if (a.is_negative && !b.is_negative) return -(-a + b);
    if (b.is_negative && !a.is_negative) return -b + a;

    if (a.is_negative && a > b) return -(b - a);
    if (!a.is_negative && b > a) return -(b - a);
    // => abs(a) >= abs(b)

    size_t da, db;
    if (a.precision > b.precision) {
        da = 0; db = a.precision - b.precision;
    } else {
        da = b.precision - a.precision; db = 0;
    }
    const size_t upper = std::max(a.value.size() + da, b.value.size() + db);

    std::deque<int64_t> new_value;

    int64_t memo = 0;
    for (size_t i = 0; i < upper; i++) {
        int64_t av = (i < da || i - da >= a.value.size()) ? 0 : a.value[i - da];
        int64_t bv = (i < db || i - db >= b.value.size()) ? 0 : b.value[i - db];

        new_value.push_back(av - bv - memo);
    }

    BigNum result{a.is_negative, std::max(a.decimal_precision, b.decimal_precision), new_value};
    result.normalize();
    return result;
}
