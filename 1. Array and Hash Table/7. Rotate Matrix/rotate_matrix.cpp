#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Rotate {
    public:
    void rotateMatrix(vector<vector<int>> &matrix) {
        // has to be a square 
        if (matrix.empty() || matrix.size() != matrix[0].size()) {
            return;
        }

        int length = matrix.size();
        // start at the top left corner and go diagonally down to the right
        for (int i = 0; i < length / 2; i++) { // only need to halfway down the matrix for rows
            for (int j = i; j < length - i - 1; j++) { // stop at unchanged value within the row
                // go around the matrix till each value is replaced then move on to the next;
                int top = matrix[i][j];
                matrix[i][j] = matrix[length - 1 - j][i];
                matrix[length - 1 - j][i] = matrix[length - 1 - i][length - 1 - j];
                matrix[length - 1 - i][length - 1 - j] = matrix[j][length - 1 - i];
                matrix[j][length - 1 - i] = top;
            }
        }
    }
};

int main() {
    Rotate r;
    vector<vector<int>> matrix = {{1, 3, 5, 6, 9},
                                  {8, 2, 5, 4, 3},
                                  {7, 9, 1, 4, 5},
                                  {7, 6, 5, 2, 1},
                                  {1, 3, 6, 5, 5}};
    r.rotateMatrix(matrix);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    return 0;
}