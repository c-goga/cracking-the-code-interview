#ifndef BIT_TASKS
#define BIT_TASKS

#include <iostream>

class Bit {
    public:
    // get bit
    static bool getBit(int num, int i) {
        return ((num & (1 << i)) != 0);
    }

    // set bit
    static int setBit(int num, int i) {
        return num | (1 << i);
    }

    // clear single bit
    static int clearBit(int num, int i) {
        int mask = ~(1 << i); // ex: i = 4, 11101111
        return num & mask;
    }

    // clear most signifcant bits to i
    static int clearBitsMSBthroughI(int num, int i) {
        int mask = (1 << i) - 1; // ex: i = 4, 00001111
        return num & mask;
    }

    // clear bits from i to 0
    static int clearBitsIthrough0(int num, int i) {
        int mask = (-1 << (i + 1)); // ex: i = 4, 11100000
        return num & mask;
    }

    // update bit
    static int updateBit(int num, int i, bool bitIs1) {
        int value = bitIs1 ? 1 : 0; // value we are setting the bit to
        int mask = ~(1 << i); // use mask to clear bit
        return (num & mask) | (value << i); // clears the bit then uses or to set bit to 1 or 0 depending on value
    }

    static void printIthrough0Bits(int num, int i) {
        for (int j = i; j >= 0; j--) {
            int bit = (num >> j) & 1;
            std::cout << bit;
        }
        std::cout << std::endl;
    }
};

#endif