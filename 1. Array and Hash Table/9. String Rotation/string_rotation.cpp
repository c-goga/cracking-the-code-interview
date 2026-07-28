#include <string>
#include <iostream>
using namespace std;

class StringRotation {
    public:
    bool isStringRotation(string s1, string s2) {
        if (s1.length() != s2.length()) {
            return false; // can't be rotation without same length
        }

        /** my solution
         * 
        bool same = false; // indicator of same sequence of characters between the two strings
        int end = 0; // index of where to end the string to check substring
        int p1 = 0; // pointer for s1
        int p2 = 0; // pointer for s2
        while (p2 < s2.length()) {
            if (!same && s1[p1] == s2[p2]) {
                same = true;
            }

            if (same) {
                // cout << p1 << " " << p2 << endl;
                // cout << s1[p1] << " " << s2[p2] << endl;
                if (s1[p1] != s2[p2]) {
                    same = false;
                    p1 = 0;
                    p2++;
                }
                p1++;
                p2++;
            } else {
                p2++;
                end = p2;
            }
        }

        if (!same) {
            return false;
        }

        // cout << "end" << endl;
        // cout << s2.substr(0, end) << endl;
        return isSubstring(s1, s2.substr(0, end));

        */

        // textbook solution that is better and more thought provoking tbh

        /** if s2 is a rotation will be a substring of the string s1s1 because of the breakpoint 
         * found within s2. imagine s1 as xy and s2 as yx where yx is the opposite of the breakpoint found
         * within s1, if we double s1 to get xyxy, we can see that yx in right in the middle.
        */

        if (s1.length() != 0) {
            string s1s1 = s1 + s1;
            return isSubstring(s1s1, s2);
        }
        return false;
    }

    private:
    bool isSubstring(string s1, string s2) {
        return (s1.find(s2) != string::npos || s2.find(s1) != string::npos);
    }
};

int main() {
    StringRotation r;
    cout << boolalpha << r.isStringRotation("erbottlewat", "waterbottle") << endl; // true
    cout << boolalpha << r.isStringRotation("erbottlewat", "wottle") << endl; // false
    cout << boolalpha << r.isStringRotation("ttlewat", "waterbottle") << endl; // false
    cout << boolalpha << r.isStringRotation("erbottlewat", "wfterbottle") << endl; // false
    cout << boolalpha << r.isStringRotation("efbottlewat", "waterbottle") << endl; // false
    cout << boolalpha << r.isStringRotation("", "") << endl; // false
    return 0;
}