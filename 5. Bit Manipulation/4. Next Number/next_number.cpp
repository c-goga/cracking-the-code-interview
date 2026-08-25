#include <iostream>
#include <vector>
#include <bitset>
#include "../bit_tasks.hpp"

using namespace std;

/**
 * Finds the next smallest number and next largest number with the same number of one bits. The smallest is in index 0 and the
 * largest is in index 1. We find the smallest by clearing the leftmost 1 bit and setting the leftmost 0 bit seen to the right
 * of the that leftmost 1 bit (ex: 0101 (5), leftmost 1 bit is at index 2, leftmost 0 bit to the right of it is at index 1, by 
 * clearing then setting we get 0011 (3)). We find the largest by clearing the rightmost 1 bit and setting the rightmost 0 bit 
 * seen to the left of the that rightmost 1 bit (ex: 0101 (5), rightmost 1 bit is at index 0, rightmost 0 bit to the left of it 
 * is at index 1, by clearing then setting we get 0110 (6)). If a sequence is all 1s then the smallest number is the same as the
 * input.
 */
vector<int> nextNumber(int n) {
    if (n == 0) return {0, 0}; // if 0, no next number so return both 0

    // let both our smallest and largest next number equal to the input
    int small = n;
    int large = n;

    int lastZeroSeen = -1; // as we iterate through the bits from right to left, we will keep track of the last zero seen.
                           // this is used to replace it the bit with a 1 once we get to the end of iterating (gives us our small number)
    bool lookForZero = false; // once we find a 1 bit, we want to find the next 0 bit to replace it with a 1 for the large number
    bool largeFound = false; // once the next largest number has been found, no need to look anymore and only iterate to get the last seen zero

    int i = 0; // used for bit shifting
    while ((n >> i) != 0) {
        if (!lookForZero && Bit::getBit(n, i)) { // if not looking for zero and a bit with 1 is found
            large = Bit::clearBit(large, i); // clear the bit to maek it 0
            lookForZero = true; // now looking for next 0
        } else if (!Bit::getBit(n, i)) { // if a bit with 0 is found
            lastZeroSeen = i; // update lastZeroSeen
            if (!largeFound && lookForZero) { // if large hasn't been found and currently looking for a 0
                large = Bit::setBit(large, i); // set the bit to 1
                largeFound = true; // large has been found
            }
        }
        i++;
    }

    if (lastZeroSeen != -1) { // if a 0 was found
        small = Bit::clearBit(n, i - 1); // clear the leftmost 1 bit
        small = Bit::setBit(small, lastZeroSeen); // set the 1 to a 0
    }

    if (!largeFound) { // if large was never found it must mean that it was a sequence of only 1s
        large = Bit::setBit(large, i); // add a 1 to the front of the sequence
    }

    return {small, large};
}

int main() {
    vector<int> res = nextNumber(5); // testing my notebook example
    cout << "input: " << bitset<32>(5) << " (5)" << endl << "small: " << bitset<32>(res[0]) << " (" << res[0] << ")" << endl << "large: " << bitset<32>(res[1]) << " (" << res[1] << ")"<< endl;

    res = nextNumber(1582); // testing random number
    cout << "input: " << bitset<32>(1582) << " (1582)" << endl << "small: " << bitset<32>(res[0]) << " (" << res[0] << ")" << endl << "large: " << bitset<32>(res[1]) << " (" << res[1] << ")"<< endl;

    res = nextNumber(15); // testing all 1s (small num must be the same as num)
    cout << "input: " << bitset<32>(15) << " (15)" << endl << "small: " << bitset<32>(res[0]) << " (" << res[0] << ")" << endl << "large: " << bitset<32>(res[1]) << " (" << res[1] << ")"<< endl;

    res = nextNumber(0); // testing all 0s
    cout << "input: " << bitset<32>(0) << " (0)" << endl << "small: " << bitset<32>(res[0]) << " (" << res[0] << ")" << endl << "large: " << bitset<32>(res[1]) << " (" << res[1] << ")"<< endl;
    return 0;
}