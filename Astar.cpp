#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 3;

struct PuzzleState {
    vector<vector<int>> board;
    int x, y; // position of the empty tile (0)
    int g; // cost to reach current node
    int h; // heuristic cost to goal
    string path; // path to reach this node

    PuzzleState(vector<vector<int>> b, int gx, int gy, int gCost, string p) {
        board = b;
        x = gx;
        y = gy;
        g = gCost;
        path = p;
        h = calculateHeuristic();
    }

    // Manhattan distance heuristic
    int calculateHeuristic() {
        int dist = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] != 0) {
                    int val = board[i][j] - 1;
                    int targetX = val / N;
                    int targetY = val % N;
                    dist += abs(i - targetX) + abs(j - targetY);
                }
        return dist;
    }

    bool isGoal() const {
        int val = 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] != 0 && board[i][j] != val++)
                    return false;
        return board[N - 1][N - 1] == 0;
    }

    bool operator>(const PuzzleState &other) const {
        return (g + h) > (other.g + other.h);
    }

    string boardToString() const {
        string s;
        for (auto &row : board)
            for (int cell : row)
                s += to_string(cell);
        return s;
    }
};

vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<char> moveChar = {'U', 'D', 'L', 'R'};

void solvePuzzle(vector<vector<int>> startBoard) {
    int x = 0, y = 0;

    // Find position of empty tile
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (startBoard[i][j] == 0) {
                x = i;
                y = j;
            }

    priority_queue<PuzzleState, vector<PuzzleState>, greater<>> openList;
    unordered_set<string> visited;

    PuzzleState start(startBoard, x, y, 0, "");
    openList.push(start);

    while (!openList.empty()) {
        PuzzleState current = openList.top();
        openList.pop();

        string stateStr = current.boardToString();
        if (visited.count(stateStr))
            continue;
        visited.insert(stateStr);

        if (current.isGoal()) {
            cout << "Solved in " << current.g << " moves.\n";
            cout << "Path: " << current.path << endl;
            return;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + directions[i].first;
            int newY = current.y + directions[i].second;

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                vector<vector<int>> newBoard = current.board;
                swap(newBoard[current.x][current.y], newBoard[newX][newY]);

                PuzzleState neighbor(newBoard, newX, newY, current.g + 1, current.path + moveChar[i]);

                if (!visited.count(neighbor.boardToString()))
                    openList.push(neighbor);
            }
        }
    }

    cout << "No solution found." << endl;
}

int main() {
    vector<vector<int>> initial = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    solvePuzzle(initial);

    return 0;
}
