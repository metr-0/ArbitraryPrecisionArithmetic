//
// Created by m3tr0 on 21.02.2024.
//

#include "../BigNum.h"

std::string BigNum::to_string() const {
    if (value.empty()) return "0";

    std::string result;
    if (is_negative) result += '-';

    for (int i = (int)value.size() - 1; i >= (int)_precision; i--) {
        std::string t = std::to_string(value[i]);
        std::string et = std::string(base_exp_ratio - t.length(), '0') + t;
        result += (i == value.size() - 1) ? t : et;
    }

    int trailing_zeros;
    for (trailing_zeros = 0; trailing_zeros < (int)_precision && value[trailing_zeros] == 0; trailing_zeros++);

    for (int i = (int)_precision - 1; i >= trailing_zeros; i--) {
        if (i == (int)_precision - 1) result += '.';

        std::string t = std::to_string(value[i]);
        std::string et = std::string(base_exp_ratio - t.length(), '0') + t;
        if (i == trailing_zeros) {
            while (et.length() && et.back() == '0')
                et.erase(et.length() - 1);
        }
        result += et;
    }

    return result;
}

std::ostream &operator<<(std::ostream &out, const BigNum &a) {
    return out << a.to_string();
}
