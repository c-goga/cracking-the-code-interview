#include <iostream>
#include <bitset>
#include <limits>
#include "../bit_tasks.hpp"

using namespace std;

/**
 * Swaps the odds bits with even bits (bit 0 swapped with bit 1, bit 2 swapped with bit 3, and so on).
 * 
 * I have to come a realization:
 * You can create a mask to get every even bit and every odd bit in two different cases depending on total bit length.
 *      Available Bit Length == Odd (in this case since available bits is 31):
 *          OddMask = Max number of available bit length (all 1s) * (1/3)
 *          EvenMask = Max number of available bit length (all 1s) * (2/3) + 1
 *      Available Bit Length == Even:
 *          OddMask = Max number of available bit length (all 1s) * (2/3) + 1
 *          EvenMask = Max number of available bit length (all 1s) * (1/3)
 * 
 * You can use these masks to get every even and odd bit. Then clear all bits from n then use AND to set them to bot the evenBits after
 * shifting them 1 to the left and the oddBits after shifting them 1 to the right.
 */
int pairwiseSwap(int n) {
    int oddMask = numeric_limits<int>::max() / 3;
    int evenMask = oddMask * 2 + 1;

    int oddBits = oddMask & n;
    int evenBits = evenMask & n;

    n = (n & 0) | (evenBits << 1);
    n = n | (oddBits >> 1);
    return n;
}

/**
 * The textbook did it in one line... a = 1010 and 5 = 0101 so they use it to make a mask that fits 32 bit integers 
 * a is used for even mask, 5 is used for odd mask
 */
int pairwiseSwapT(int n) {
    return (((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1));
}

int main() {
    // notebook examples
    cout << bitset<8>(5) << endl;
    cout << bitset<8>(pairwiseSwapT(5)) << endl << endl;

    cout << bitset<8>(3) << endl;
    cout << bitset<8>(pairwiseSwapT(3)) << endl << endl;

    cout << bitset<8>(7) << endl;
    cout << bitset<8>(pairwiseSwapT(7)) << endl << endl;

    // random example   
    cout << bitset<16>(1163) << endl;
    cout << bitset<16>(pairwiseSwapT(1163)) << endl << endl;
    return 0;
}