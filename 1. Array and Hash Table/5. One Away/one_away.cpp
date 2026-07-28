using namespace std;
#include <string>
#include <iostream>
#include <cmath>
#include <unordered_map>

class OneAway {
    public:
    bool oneAway(string s1, string s2) {
        if (abs(static_cast<int>(s1.length() - s2.length())) >= 2) {
            return false;
        }

        string longer = s1.length() > s2.length() ? s1 : s2;
        string shorter = s1.length() <= s2.length() ? s1 : s2;
        bool diffChar = false;
        for (int idx1 = 0, idx2 = 0; idx1 < longer.length() && idx2 < shorter.length(); idx1++, idx2++) {
            if (longer[idx1] != shorter[idx2]) {
                if (diffChar) {
                    return false;
                }
                diffChar = true;
                idx1 += shorter.length() == longer.length() ? 0 : 1;
            }
        }

        return true;
    }
};

int main() {
    OneAway o;
    cout << boolalpha << o.oneAway("pale", "ple") << endl; // true
    cout << boolalpha << o.oneAway("pale", "bale") << endl; // true
    cout << boolalpha << o.oneAway("pale", "bake") << endl; // false
    cout << boolalpha << o.oneAway("pale", "pe") << endl; // false
    cout << boolalpha << o.oneAway("Cracking the Coding Interview", "Cracking the Coding Intervief") << endl; // true
    cout << boolalpha << o.oneAway("Cracking the Coding Interview", "Cracking the Coding Intervie") << endl; // true
    cout << boolalpha << o.oneAway("Cracking the Coding Interview", "Cracking the Coding Interview") << endl; // true
    return 0;
}
