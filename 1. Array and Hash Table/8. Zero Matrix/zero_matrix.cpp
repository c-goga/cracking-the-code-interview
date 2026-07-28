#include <iostream>
#include <vector>
using namespace std;

class Zero {
    public:
    void zeroMatrix(vector<vector<int>> &matrix) {
        if (matrix.empty()) { return; }

        vector<int> cols;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    fillRow(matrix, i);
                    cols.push_back(j);
                    break;
                }
            }
        }

        fillColumns(matrix, cols);
    }

    private:
    void fillRow(vector<vector<int>> &matrix, int row) {
        for (int j = 0; j < matrix[row].size(); j++) {
            matrix[row][j] = 0;
        }
    }

    // phil collins ?
    void fillColumns(vector<vector<int>> &matrix, vector<int> cols) {
        for (int j = 0; j < cols.size(); j++) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][cols[j]] = 0;
            }
        }
    }
};

int main() {
    Zero z;
    vector<vector<int>> matrix = {{1, 2, 3, 4},
                                  {7, 8, 0, 9},
                                  {0, 1, 5, 4}};
    z.zeroMatrix(matrix);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    return 0;
}