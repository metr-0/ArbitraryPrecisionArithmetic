//
// Created by m3tr0 on 22.02.2024.
//

#include "BigNum.h"
#include <iostream>

BigNum pi(size_t precision) {
    BigNum n0 = 16_bn, n1 = 4_bn, n2 = 2_bn, n3 = 1_bn;
    n0.decimal_precision(precision + 1);
    n1.decimal_precision(precision + 1);
    n2.decimal_precision(precision + 1);
    n3.decimal_precision(precision + 1);

    BigNum result;
    result.decimal_precision(precision + 1);

    int k = 0;
    while (true) {
        n0 = n0 / BigNum{16};
        BigNum t0 = (n1 / BigNum{8 * k + 1} - n2 / BigNum{8 * k + 4} - n3 / BigNum{8 * k + 5} - n3 / BigNum{8 * k + 6});
        BigNum t = n0 * t0;

        t.decimal_precision(precision + 1);
        if (t == 0_bn) break;
        result = result + t;
        k++;
    }

    std::cout << k << std::endl;
    return result;
}

int main() {
    std::cout << pi(100) << std::endl;
    return 0;
}
