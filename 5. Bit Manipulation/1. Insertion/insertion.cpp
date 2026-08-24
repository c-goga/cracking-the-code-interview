#include <iostream>
#include <bitset>
#include "../bit_tasks.hpp"

using namespace std;

// can assume that M will fit between i and j
void insertion(int &N, int M, int i, int j) { // O(n) time, where n is the number of bits from j to i
    for(int k = j; k >= i; k--) {
        N = Bit::updateBit(N, k, Bit::getBit(M, k - i));
    }
}

// textbook implementation
int insertionT(int N, int M, int i, int j) { // 0(1) time
    if (i > j || i < 0 || j >= 32) return 0; // should have known to do this check... have to check j >= 32 since only used for 32 bit integers

    // Create mask to clear bits i through j in n. ex: i = 2, j = 4. Result should be 11100011 (using 8 bits for simplicity)
    int allOnes = ~0; // sequence of 1s

    // 1s before position j, then 0s. ex: left = 11100000
    int left = j < 31 ? (allOnes << (j + 1)) : 0;

    // 1s after postiion i. ex: right = 00000011
    int right = ((1 << i) - 1); // need to remember that minus 1 will make all bits to the right of i 1

    // all 1s, except for 0s between i and j. ex: mask = 11100011
    int mask = left | right;

    // clear bit j through i then put M in there
    int n_cleared = N & mask; // clear bits j through i;
    int m_shifted = M << i; // move M into correct position

    return n_cleared | m_shifted; // OR them then return
}

int main() {
    int N = 0b10000000000; // 0b lets you type out a number as a bit sequence
    int M = 0b10011;
    int i = 2;
    int j = 6;
    
    cout << "N before (10000000000): " << bitset<11>(N) << endl; // bitset<n> lets you print out bit sequence of a number up to n length
    insertion(N, M, i, j);
    cout << "N after (10001001100): " << bitset<11>(N) << endl;

    N = 0b10000000000;
    cout << "Textbook: N before (10000000000): " << bitset<11>(N) << endl;
    N = insertionT(N, M, i, j);
    cout << "Textbook: N after (10001001100): " << bitset<11>(N) << endl;
    return 0;
}