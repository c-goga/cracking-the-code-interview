#include <string>
#include <iostream>
using namespace std;

class Palindrome {
    public:
    bool palindromePermutationCheck(string s) {
        int letterCount[26] = {0};
        for (char c: s) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                letterCount[tolower(c) - 'a']++;  
            }
        }

        bool odd = false;
        for (int i = 0; i < size(letterCount); i++) {
            if (letterCount[i] % 2 == 1) {
                if (!odd) {
                    odd = true;
                } else {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Palindrome p;
    cout << boolalpha << p.palindromePermutationCheck("Tact Coa") << endl;
    cout << boolalpha << p.palindromePermutationCheck("Tacf Coa") << endl;
    cout << boolalpha << p.palindromePermutationCheck("A man? A prisoner! A cage? Iron! Did Noriega care? No, sir! Panama!") << endl;
    return 0;
}