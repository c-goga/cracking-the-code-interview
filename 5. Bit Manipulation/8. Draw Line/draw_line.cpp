#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

/**
 * Draws a horizontal line on the screen from x1 to x2 on row y.
 */
void drawLine(vector<byte> &screen, int w, int x1, int x2, int y) {
    if (w % 8 != 0) return; // width has to be divisble by 8

    int height = screen.size() / (w / 8); // get height of screen by dividing size by how many bytes can fit within the width
    if (y >= height || y < 0) return; // if y not within rang return

    int rowStart = (y * w) / 8; // where the row starts
    int rowLength = w / 8; // how long the row is
    int rowPlace = 1; // where are we in the row
    for (int i = rowStart; i < rowStart + rowLength; i++) {
        int threshold = rowPlace * 8; // get the upper limit of x1 and x2 through multlipying current row place by 8
        if (x1 < threshold && x1 >= threshold - 8) { // if x1 is within range
            int x1Mask = 0; // mask for x1
            if (x1 == threshold - 8) x1Mask = ~0; // if x1 at start, then byte is all 1s
            else x1Mask = (1 << (8 - (x1 % 8))) - 1; // if x1 not at start, put 1s on and to the right of x1 index
            if (x2 < threshold && x2 >= threshold - 8) { // if x2 is also here
                int x2Mask = 0; // mask for x2
                if (x2 == threshold - 1) x2Mask = ~0; // if x2 at end, then byte is all 1s
                else x2Mask = (~0 << (7 - (x2 % 8))); // if x2 not at end, put 1s on and to the left of x2 index
                screen[i] = byte(to_integer<int>(screen[i]) | (x1Mask & x2Mask)); // AND both masks to get 1s from x1 to x2 then AND with screen
                return;
            } else screen[i] = byte(to_integer<int>(screen[i]) | x1Mask); // if x2 not here only use OR with x1 mask
        } else if (x2 < threshold && x2 >= threshold - 8) { // if x2 is within range
            int x2Mask = 0; // mask for x2
            if (x2 == threshold - 1) x2Mask = ~0; // if x2 at end, then byte is all 1s
            else x2Mask = (~0 << (7 - (x2 % 8))); // if x2 not at end, put 1s on and to the left of x2 index
            screen[i] = byte(to_integer<int>(screen[i]) | x2Mask); // OR with screen element
        } else if (x1 < threshold - 8 && x2 >= threshold) { // if x1 has been passed and x2 has not been passed, fill with 1s
            screen[i] = byte(~0); 
        }

        rowPlace++; // increment row place
    }
}

void printScreen(vector<byte> screen, int w) {
    if (w % 8 != 0) return;

    int rowLength = w / 8;
    for (int i = 0; i < screen.size(); i++) {
        if (i != 0 && i % rowLength == 0) cout << endl;
        cout << bitset<8>(to_integer<int>(screen[i]));
    }
}

int main() {
    vector<byte> screen = {byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0},
                           byte{0}, byte{0}, byte{0}};
    cout << "BEFORE:" << endl;
    printScreen(screen, 24);

    drawLine(screen, 24, 4, 19, 5);
    cout << endl << "AFTER (LONG):" << endl;
    printScreen(screen, 24);

    drawLine(screen, 24, 2, 5, 3);
    cout << endl << "AFTER (SHORT):" << endl;
    printScreen(screen, 24);

    drawLine(screen, 24, 0, 23, 8);
    cout << endl << "AFTER (ENTIRE LINE):" << endl;
    printScreen(screen, 24);

    drawLine(screen, 24, 15, 15, 1);
    cout << endl << "AFTER (SAME X1 AND X2):" << endl;
    printScreen(screen, 24);

    drawLine(screen, 20, 15, 15, 1);
    cout << endl << "NO CHANGE (INVALID WIDTH):" << endl;
    printScreen(screen, 24);

    drawLine(screen, 24, 15, 15, 14);
    cout << endl << "NO CHANGE (INVALID HEIGHT):" << endl;
    printScreen(screen, 24);
    return 0;
}