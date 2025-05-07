#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int row, int col, vector<string> &board, int n) {
    // Check vertical
    for (int i = 0; i < row; ++i)
        if (board[i][col] == 'Q') return false;

    // Check diagonal (top-left)
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
        if (board[i][j] == 'Q') return false;

    // Check diagonal (top-right)
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
        if (board[i][j] == 'Q') return false;

    return true;
}

void solveBT(int row, vector<string> &board, int n, vector<vector<string>> &solutions) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col, board, n)) {
            board[row][col] = 'Q';
            solveBT(row + 1, board, n, solutions);
            board[row][col] = '.';
        }
    }
}

void nQueensBacktracking(int n) {
    vector<vector<string>> solutions;
    vector<string> board(n, string(n, '.'));
    solveBT(0, board, n, solutions);

    cout << "Solutions using Backtracking:\n";
    for (const auto &sol : solutions) {
        for (const auto &row : sol)
            cout << row << endl;
        cout << endl;
    }
}

int main() {
    int n = 8;

    nQueensBacktracking(n);
    cout << "-----------------------------\n";
    //nQueensBranchAndBound(n);

    return 0;
}
