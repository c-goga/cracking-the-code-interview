#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

int flipBitToWin(int n) {
    int seq = 0; // current sequence 1 length
    int pastSeq = 0; // past sequence 1 length
    int maxSeq = 1; // max sequence length found
    int i = 0; // number of bits to shift on each loop
    while ((n >> i) > 0) { // when there are only zeros left in the sequence, stop the loop
        // cout << endl << "start: " << seq << endl;
        // cout << "idx: " << i << endl;
        // cout << bitset<14>(n) << endl;
        // cout << bitset<14>(n >> i) << endl;

        if (((n >> i) & 1) != 1) { // if bit is a zero
            pastSeq = seq; // length of past sequence of 1s
            seq = 0; // reset current sequence
        } else {
            seq++; // increment sequence length
        }

        i++; // increment bit shift
        maxSeq = max(maxSeq, seq + pastSeq + 1); // set maxSeq to seq if is seq > maxSeq
    }

    return maxSeq; // return max of maxSeq or seq since loop could end without maxSeq being set
}

int main() {
    cout << "1775 / 11011101111 (8): " << flipBitToWin(1775) << endl;
    cout << "612 / 1001100100 (3): " << flipBitToWin(612) << endl;
    cout << "0 / 0 (1): " << flipBitToWin(0) << endl;
    cout << "9043 / 10001101010011 (4): " << flipBitToWin(9043) << endl;
    return 0;
}