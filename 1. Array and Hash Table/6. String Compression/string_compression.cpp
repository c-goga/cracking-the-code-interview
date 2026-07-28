#include <iostream>
#include <string>
using namespace std;

class Compress {
    public:
    string compressString(string original) {
        if (original.length() < 2) {
            return original;
        }

        if (getCompressedLength(original) >= original.length()) { // a way to save space on string use is to check for length first
                                                                  // although it does lead to almost mirrored code
            return original;
        }

        string s = "";
        char letter = original[0];
        s += letter;
        int count = 0;
        for (int i = 0; i < original.length(); i++) {
            if (original[i] == letter) {
                count++;
            } else {
                s += to_string(count);
                s += original[i];
                letter = original[i];
                count = 1;
            }
        }
        s += to_string(count);

        return s;
    }

    private:
    int getCompressedLength(string s) {
        char letter = s[0];
        int length = 1;
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == letter) {
                count++;
            } else {
                length += to_string(count).length() + 1;
                letter = s[i];
                count = 1;
            }
        }
        return length + 1;
    }
};

int main() {
    Compress c;
    cout << c.compressString("aabcccccaaa") << endl; // should be a2b1c5a3
    cout << c.compressString("abcdefg") << endl; // should be abcdefg
    cout << c.compressString("PPPPPBEFSSSSSSJEEEEEEEEEEEEEE") << endl; // should be P5B1E1F1S6J1E14
    return 0;
}