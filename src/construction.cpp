//
// Created by m3tr0 on 21.02.2024.
//

#include "BigNum.h"

BigNum::BigNum(bool _is_negative, size_t _decimal_precision, std::deque<int64_t>  _value)
        : is_negative(_is_negative), decimal_precision(_decimal_precision), value(std::move(_value)) {
    precision = (decimal_precision + base_exp_ratio - 1) / base_exp_ratio;
}

BigNum::BigNum(const char *s) {
    if (s == nullptr) {
        is_negative = false;
        decimal_precision = precision = 0;
        value.push_front(0);
        return;
    }

    char *ptr = const_cast<char *>(s);
    const char *dot = strchr(ptr, '.');

    is_negative = *ptr == '-';
    if (is_negative) ptr++;
    while (*ptr != '\0' && ptr != dot && (*ptr <= '0' || *ptr > '9')) ptr++;

    const size_t length = strlen(ptr);
    decimal_precision = (dot == nullptr) ? 0 : (length - 1 - (dot - ptr));
    precision = (decimal_precision + base_exp_ratio - 1) / base_exp_ratio;
    const size_t int_part_length = (dot == nullptr) ? length : (length - 1 - decimal_precision);

    int64_t cur = 0, rem = (int64_t)int_part_length % base_exp_ratio;
    if (rem == 0 && int_part_length) rem = base_exp_ratio;
    while (true) {
        if (rem == 0 || *ptr == '\0') {
            value.push_front(cur);
            cur = 0, rem = base_exp_ratio;
        }

        if (*ptr == '\0') break;
        if (ptr == dot) {
            ptr++;
            if (*ptr == '\0') break;
            continue;
        }

        int64_t number = (*ptr < '0' || '9' < *ptr) ? 0 : (*ptr - '0');
        cur = cur * decimal_base + number;
        ptr++, rem--;
    }

    for (int i = 0; i < base_exp_ratio * precision - decimal_precision; i++)
        value[0] *= 10;
}

BigNum operator""_bn(const char *s) {
    return BigNum{s};
}
