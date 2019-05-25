#include "arraycomparators.h"

#include "radixsort.h"
#include "avltree.h"

unsigned int compareslow(const int arr1[], unsigned int size1, const int arr2[], unsigned int size2) {
    unsigned int res = 0;
    for (int i1 = 0; i1 < size1; ++i1) {
        for (int i2 = 0; i2 < size2; ++i2) {
            if (arr1[i1] == arr2[i2]) {
                ++res;
                break;
            }
        }
    }
    return res;
}


unsigned int comparebysort(int arr1[], unsigned int size1, int arr2[], unsigned int size2) {
    return comparebysort((unsigned int*) arr1, size1, (unsigned int*) arr2, size2);
}

unsigned int comparebysort(unsigned int arr1[], unsigned int size1, unsigned int arr2[], unsigned int size2) {
    radixsort(arr1, size1);
    radixsort(arr2, size2);

    unsigned int res = 0;
    for (int i1 = 0, i2 = 0; i1 < size1 && i2 < size2;) {
        if (arr1[i1] < arr2[i2]) {
            ++i1;
        } else if (arr2[i2] < arr1[i1]) {
            ++i2;
        } else {
            ++res;
            ++i1;
            ++i2;
        }
    }

    return res;
}


unsigned int comparebyavl(const int arr1[], unsigned int size1, const int arr2[], unsigned int size2) {
    if (size1 > size2) {
        return comparebyavl(arr2, size2, arr1, size1);
    }

    avlnode* root = nullptr;
    for (int i = 0; i < size1; ++i) {
        root = avlinsert(root, arr1[i]);
    }

    int res = 0;
    for (int i = 0; i < size2; ++i) {
        if (avlexists(root, arr2[i])) {
            ++res;
        }
    }
    return res;
}

