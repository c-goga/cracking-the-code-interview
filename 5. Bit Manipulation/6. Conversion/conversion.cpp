#include <iostream>
#include <bitset>

using namespace std;

/**
 * Determines number of bits that need to be flipped to convert integer A to integer B.
 */
int conversion(int A, int B) {
    int numOfBitsFlipped = 0;
    int i = 0;
    while ((A >> i) != 0 || (B >> i) != 0) {
        if (((A >> i) & 1) ^ ((B >> i) & 1) != 0) {
            numOfBitsFlipped++;
        }
        i++;
    }
    return numOfBitsFlipped;
}

int main() {
    // textbook example
    cout << "A: " << bitset<8>(29) << "(29)" << endl;
    cout << "B: " << bitset<8>(15) << "(15)" << endl;
    cout << "Output (2): " << conversion(29, 15) << endl;

    // random example
    cout << "A: " << bitset<8>(37) << "(37)" << endl;
    cout << "B: " << bitset<8>(8) << "(8)" << endl;
    cout << "Output (4): " << conversion(37, 8) << endl;
    return 0;
}