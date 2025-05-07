#include <iostream>
#include <vector>

using namespace std;

void solveBB(int row, vector<string> &board, int n, vector<int> &cols,
             vector<int> &diag1, vector<int> &diag2, vector<vector<string>> &solutions) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (cols[col] || diag1[row - col + n - 1] || diag2[row + col])
            continue;

        board[row][col] = 'Q';
        cols[col] = diag1[row - col + n - 1] = diag2[row + col] = 1;

        solveBB(row + 1, board, n, cols, diag1, diag2, solutions);

        board[row][col] = '.';
        cols[col] = diag1[row - col + n - 1] = diag2[row + col] = 0;
    }
}

void nQueensBranchAndBound(int n) {
    vector<vector<string>> solutions;
    vector<string> board(n, string(n, '.'));
    vector<int> cols(n, 0);
    vector<int> diag1(2 * n - 1, 0);
    vector<int> diag2(2 * n - 1, 0);

    solveBB(0, board, n, cols, diag1, diag2, solutions);

    cout << "Solutions using Branch and Bound:\n";
    for (const auto &sol : solutions) {
        for (const auto &row : sol)
            cout << row << endl;
        cout << endl;
    }
}

int main() {
    int n = 8;

    //nQueensBacktracking(n);
    cout << "-----------------------------\n";
    nQueensBranchAndBound(n);

    return 0;
}
