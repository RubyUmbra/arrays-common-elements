#include "radixsort.h"

void radixsort(unsigned int array[], unsigned int size) {
    unsigned int* result = new unsigned int[size];
    unsigned int* swapper = nullptr;
    unsigned int j;
    unsigned int bitshift = 1;

    while (bitshift != 0) {
        j = 0;

        for (int i = 0; i < size; ++i) {
            if ((array[i] & bitshift) == 0) {
                result[j++] = array[i];
            }
        }
        for (int i = 0; i < size; ++i) {
            if ((array[i] & bitshift) != 0) {
                result[j++] = array[i];
            }
        }

        swapper = array;
        array = result;
        result = swapper;

        bitshift = bitshift << (unsigned int) 1;
    }

    delete[] result;
}
