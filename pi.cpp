//
// Created by m3tr0 on 22.02.2024.
//

#include "BigNum.h"
#include <iostream>
#include <chrono>

BigNum pi(size_t precision) {
    BigNum n0{16, precision + 1}, n1{4, precision + 1},
            n2{2, precision + 1}, n3{1, precision + 1};

    BigNum result{0, precision + 1};

    int k = 0;
    while (true) {
        n0 = n0 / BigNum{16};
        BigNum t0 = (n1 / (8 * k + 1) - n2 / BigNum{8 * k + 4} - n3 / BigNum{8 * k + 5} - n3 / BigNum{8 * k + 6});
        BigNum t = n0 * t0;

        t.decimal_precision(precision + 1);
        if (t == 0_bn) break;
        result = result + t;
        k++;
    }

    return result;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << pi(100) << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << duration.count() << std::endl;
    return 0;
}
