//
// Created by metro on 21.02.2024.
//

#include "BigNum.h"

std::strong_ordering operator<=>(const BigNum &a, const BigNum &b) {
    size_t da, db;
    if (a.precision > b.precision) {
        da = 0; db = a.precision - b.precision;
    } else {
        da = b.precision - a.precision; db = 0;
    }
    const size_t upper = std::max(a.value.size() + da, b.value.size() + db);

    for (size_t i = upper - 1; i >= 0; i--) {
        int64_t av = (i < da || i - da >= a.value.size()) ? 0 : a.value[i - da];
        int64_t bv = (i < db || i - db >= b.value.size()) ? 0 : b.value[i - db];

        if (av == bv) continue;

        if (!a.is_negative && b.is_negative) return std::strong_ordering::greater;
        if (a.is_negative && !b.is_negative) return std::strong_ordering::less;

        if (a.is_negative) return (av > bv) ? std::strong_ordering::less : std::strong_ordering::greater;
        return (av > bv) ? std::strong_ordering::greater : std::strong_ordering::less;
    }

    return std::strong_ordering::equal;
}

bool operator==(const BigNum &a, const BigNum &b) { return (a <=> b) == std::strong_ordering::equal; }
bool operator!=(const BigNum &a, const BigNum &b) { return (a <=> b) != std::strong_ordering::equal; }
bool operator<(const BigNum &a, const BigNum &b) { return (a <=> b) == std::strong_ordering::less; }
bool operator>(const BigNum &a, const BigNum &b) { return (a <=> b) == std::strong_ordering::greater; }
bool operator<=(const BigNum &a, const BigNum &b) { return (a <=> b) != std::strong_ordering::greater; }
bool operator>=(const BigNum &a, const BigNum &b) { return (a <=> b) != std::strong_ordering::less; }
