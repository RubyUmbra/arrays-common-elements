#include <iostream>
#include <random>
#include <vector>
#include <limits.h>
#include <algorithm>

#include "arraycomparators.h"

// base test

int arrays[5][32] = {
        // sorted 0..31
        {0,   1,   2,   3,   4,   5,   6,  7,  8,  9,   10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,
         23,  24,  25,  26,  27,  28,  29,  30,  31},

        //reversed 0..31
        {31,  30,  29,  28,  27,  26,  25, 24, 23, 22,  21,  20,  19,  18,  17,  16,  15,  14,  13,  12,  11,  10,  9,
         8,   7,   6,   5,   4,   3,   2,   1,   0},

        //neg and pos -15..16
        {-15, -14, -13, -12, -11, -10, -9, -8, -7, -6,  -5,  -4,  -3,  -2,  -1,  0,   1,   2,   3,   4,   5,   6,   7,
         8,   9,   10,  11,  12,  13,  14,  15,  16},

        //neg -1..-32
        {-1,  -2,  -3,  -4,  -5,  -6,  -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20, -21, -22,
         -23, -24, -25, -26, -27, -28, -29, -30, -31, -32},

        // extreme test
        {INT_MIN, INT_MIN + 1, INT_MIN + 2, INT_MIN + 3, INT_MIN + 4, INT_MIN + 5, INT_MIN + 6, INT_MIN + 7,
         INT_MIN + 8,INT_MIN + 9, INT_MIN + 10, INT_MIN + 11, INT_MIN + 12, INT_MIN + 13, INT_MIN + 14, INT_MIN + 15,
         INT_MAX, INT_MAX - 1, INT_MAX - 2, INT_MAX - 3, INT_MAX - 4, INT_MAX - 5, INT_MAX - 6, INT_MAX - 7,
         INT_MAX - 8, INT_MAX - 9, INT_MAX - 10, INT_MAX - 11, INT_MAX - 12,INT_MAX - 13, INT_MAX - 14, INT_MAX - 15}
};

int answers[5][5] = {{32, 32, 17, 00, 00},
                     {32, 32, 17, 00, 00},
                     {17, 17, 32, 15, 00},
                     {00, 00, 15, 32, 00},
                     {00, 00, 00, 00, 32}};


bool basetest(unsigned int(* f)(int*, unsigned int, int*, unsigned int)) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            int arr1[32];
            std::copy(std::begin(arrays[i]), std::end(arrays[i]), std::begin(arr1));

            int arr2[32];
            std::copy(std::begin(arrays[j]), std::end(arrays[j]), std::begin(arr2));

            unsigned int res = f(arr1, 32, arr2, 32);

            if (res != answers[i][j]) {
                std::cout << "test " << i << " " << j << " failed" << std::endl;
                return false;
            }
        }
    }
    return true;
}

// base test end

// random test

const int bound = 100000;
std::vector<int> base; // base for random arrays

void init_base() {
    for (int i = -bound; i <= bound; ++i) {
        base.push_back(i);
    }
}

std::mt19937 gen((std::random_device()) ());
std::uniform_int_distribution<> dis(1000, bound);

bool singlerandomtest(unsigned int(* f)(int*, unsigned int, int*, unsigned int)) {
    if (base.empty()) {
        init_base();
    }
    unsigned int len1 = dis(gen);
    std::vector<int> arr1(base);
    std::shuffle(arr1.begin(), arr1.end(), gen);
    arr1.erase(arr1.begin() + len1, arr1.end());

    unsigned int len2 = dis(gen);
    std::vector<int> arr2(base);
    std::shuffle(arr2.begin(), arr2.end(), gen);
    arr2.erase(arr2.begin() + len2, arr2.end());

    unsigned int trueres = compareslow(arr1.data(), len1, arr2.data(), len2);
    unsigned int res = f(arr1.data(), len1, arr2.data(), len2);

    if (trueres != res) {
        std::cout << "test failed" << std::endl;
        std::cout << "len1" << len1 << std::endl;
        for (int e:arr1) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
        std::cout << "len2" << len2 << std::endl;
        for (int e:arr2) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
    return trueres == res;
}

bool randomtest(unsigned int(* f)(int*, unsigned int, int*, unsigned int)) {
    for (int i = 0; i < 16; ++i) {
        if (!singlerandomtest(f)) {
            return false;
        }
    }
    return true;
}

// random test end

bool test(unsigned int(* f)(int*, unsigned int, int*, unsigned int)) {
    return basetest(f) && randomtest(f);
}

unsigned int compare(int arr1[], unsigned int size1, int arr2[], unsigned int size2) {
    if (size1 < 100000 || size2 < 100000) {
        return comparebyavl(arr1, size1, arr2, size2);
    } else {
        return comparebysort(arr1, size1, arr2, size2);
    }
}

int main() {
    if (test((unsigned int (*)(int*, unsigned int, int*, unsigned int)) *comparebyavl)) {
        std::cout << "comparebyavl pass tests" << std::endl;
    } else {
        std::cout << "comparebyavl fail tests" << std::endl;
    }
    if (test((unsigned int (*)(int*, unsigned int, int*, unsigned int)) *comparebysort)) {
        std::cout << "comparebysort pass tests" << std::endl;
    } else {
        std::cout << "comparebysort fail tests" << std::endl;
    }
    if (test((unsigned int (*)(int*, unsigned int, int*, unsigned int)) *compare)) {
        std::cout << "compare pass tests" << std::endl;
    } else {
        std::cout << "compare fail tests" << std::endl;
    }
    return 0;
}
