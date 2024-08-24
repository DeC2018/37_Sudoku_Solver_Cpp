#include <iostream>
#include <vector>

class Solution {
    int n = 3;
    int N = n * n;
    std::vector<std::vector<int>> rows, cols, boxes;
    std::vector<std::vector<char>> board;
    bool sudoku_solved = false;

public:
    Solution() : rows(N, std::vector<int>(N + 1, 0)), cols(N, std::vector<int>(N + 1, 0)), boxes(N, std::vector<int>(N + 1, 0)) {}

    bool could_place(int d, int row, int col) {
        int idx = (row / n) * n + col / n;
        return rows[row][d] == 0 && cols[col][d] == 0 && boxes[idx][d] == 0;
    }

    void place_or_remove(int d, int row, int col, bool place) {
        int idx = (row / n) * n + col / n;
        int delta = place ? 1 : -1;
        rows[row][d] += delta;
        cols[col][d] += delta;
        boxes[idx][d] += delta;
        board[row][col] = place ? d + '0' : '.';
    }

    void backtrack(int row = 0, int col = 0) {
        if (col == N) col = 0, row++;
        if (row == N) {
            sudoku_solved = true;
            return;
        }

        if (board[row][col] == '.') {
            for (int d = 1; d <= 9 && !sudoku_solved; d++) {
                if (could_place(d, row, col)) {
                    place_or_remove(d, row, col, true);
                    backtrack(row, col + 1);
                    if (!sudoku_solved) place_or_remove(d, row, col, false);
                }
            }
        } else
            backtrack(row, col + 1);
    }

    void solveSudoku(std::vector<std::vector<char>>& in_board) {
        board = in_board;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] != '.') {
                    int d = board[i][j] - '0';
                    place_or_remove(d, i, j, true);
                }
            }
        }
        backtrack();
        in_board = board;
    }
};

int main() {
    std::vector<std::vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    Solution sol;
    sol.solveSudoku(board);

    for (auto& row : board) {
        for (auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}