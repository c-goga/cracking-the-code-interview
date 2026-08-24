#include <iostream>
#include <bitset>

#include "../bit_tasks.hpp"

using namespace std;

// turning a decimal between 0 and 1 to a binary sequence within a string to print out
string binaryToString(double n) {
    if (n > 1 || n < 0) return "";

    string res = ".";
    int length = 0; // number of bits it will take to represent n
    double value = .5;
    while (n != 0) {
        if (length >= 32) return "ERROR";

        if (n >= value) {
            n -= value;
            res += "1";
        } else {
            res += "0";
        }
        value /= 2;
        length++;
    }
    
    return res;
}

int main() {
    cout << ".5 (.1): " << binaryToString(.5) << endl; // .1
    cout << ".125 (.001): " << binaryToString(.125) << endl; // .001
    cout << ".625 (.101): " << binaryToString(.625) << endl; // .101
    cout << ".72 (ERROR): " << binaryToString(.72) << endl; // ERROR
    return 0;
}