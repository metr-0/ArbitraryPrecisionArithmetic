//
// Created by metro on 20.02.2024.
//

#include "BigNum.h"

BigNum::BigNum(const char *s) {
    char *ptr = const_cast<char *>(s);
    const char *dot = strchr(ptr, '.');

    is_negative = *ptr == '-';
    if (is_negative) ptr++;
    while (ptr != dot && (*ptr <= '0' || *ptr > '9')) ptr++;

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

BigNum operator+(const BigNum &a, const BigNum &b) {
    return a;
}

BigNum operator-(const BigNum &a, const BigNum &b) {
    return a;
}

BigNum operator*(const BigNum &a, const BigNum &b) {
    return a;
}

BigNum operator/(const BigNum &a, const BigNum &b) {
    return a;
}

bool operator==(const BigNum &a, const BigNum &b) {
    return false;
}

bool operator!=(const BigNum &a, const BigNum &b) {
    return false;
}

bool operator<(const BigNum &a, const BigNum &b) {
    return false;
}

bool operator>(const BigNum &a, const BigNum &b) {
    return false;
}

std::string BigNum::to_string() const {
    std::string result;
    if (is_negative) result += '-';

    for (int i = (int)value.size() - 1; i >= (int)precision; i--) {
        std::string t = std::to_string(value[i]);
        std::string et = std::string(base_exp_ratio - t.length(), '0') + t;
        result += (i == value.size() - 1) ? t : et;
    }

    int trailing_zeros;
    for (trailing_zeros = 0; trailing_zeros < (int)precision && value[trailing_zeros] == 0; trailing_zeros++);

    for (int i = (int)precision - 1; i >= trailing_zeros; i--) {
        if (i == (int)precision - 1) result += '.';

        std::string t = std::to_string(value[i]);
        std::string et = std::string(base_exp_ratio - t.length(), '0') + t;
        if (i == trailing_zeros) {
            while (et.length() && et[et.length() - 1] == '0')
                et.erase(et.length() - 1);
        }
        result += et;
    }

    return result;
}

std::ostream &operator<<(std::ostream &out, const BigNum &a) {
    return out << a.to_string();
}

BigNum operator""_bn(const char *s) {
    return BigNum{s};
}
