#include <string>
#include <iostream>
using namespace::std;

class URL {
    public:
    void URLify(string &s, int length) {
        int l = length - 1;
        int r = s.length() - 1;
        cout << s[l] << endl;
        while(l < r && l >= 0) {
            if (s[l] == ' ') {
                s[r] = '0';
                s[r-1] = '2';
                s[r-2] = '%';
                r -= 2;
            } else {
                s[r] = s[l];
            }
            l--;
            r--;
        }
    }
};


int main() {
    URL url;
    string s = "Cracking the Coding Interview For Realsies          ";
    url.URLify(s, 42);
    cout << s << endl;
    return 0;
}