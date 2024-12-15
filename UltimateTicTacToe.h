#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>

class X_O_Board_ : public Board<char> {
    char board[9][9]; // 9x9 board for ultimate tic-tac-toe
    int moves = 0;
    int gridOwners[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}; // -1: unclaimed, 0: X, 1: O

    bool check_win_in_grid(int startRow, int startCol, char symbol) {
        for (int i = 0; i < 3; ++i) {
            if ((board[startRow + i][startCol] == symbol &&
                 board[startRow + i][startCol + 1] == symbol &&
                 board[startRow + i][startCol + 2] == symbol) ||
                (board[startRow][startCol + i] == symbol &&
                 board[startRow + 1][startCol + i] == symbol &&
                 board[startRow + 2][startCol + i] == symbol)) {
                return true;
            }
        }
        if ((board[startRow][startCol] == symbol &&
             board[startRow + 1][startCol + 1] == symbol &&
             board[startRow + 2][startCol + 2] == symbol) ||
            (board[startRow][startCol + 2] == symbol &&
             board[startRow + 1][startCol + 1] == symbol &&
             board[startRow + 2][startCol] == symbol)) {
            return true;
        }
        return false;
    }

    bool check_three_grids_in_a_row(int player) {
        // Check rows and columns
        for (int i = 0; i < 3; ++i) {
            if ((gridOwners[i][0] == player && gridOwners[i][1] == player && gridOwners[i][2] == player) ||
                (gridOwners[0][i] == player && gridOwners[1][i] == player && gridOwners[2][i] == player)) {
                return true;
            }
        }
        // Check diagonals
        if ((gridOwners[0][0] == player && gridOwners[1][1] == player && gridOwners[2][2] == player) ||
            (gridOwners[0][2] == player && gridOwners[1][1] == player && gridOwners[2][0] == player)) {
            return true;
        }
        return false;
    }

public:
    X_O_Board_() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= 9 || y < 0 || y >= 9 || board[x][y] != ' ') {
            return false;
        }
        board[x][y] = toupper(symbol);
        moves++;

        // Update grid owner if a 3x3 grid is won
        int gridRow = x / 3;
        int gridCol = y / 3;
        if (gridOwners[gridRow][gridCol] == -1 && check_win_in_grid(gridRow * 3, gridCol * 3, toupper(symbol))) {
            gridOwners[gridRow][gridCol] = (toupper(symbol) == 'X') ? 0 : 1;
        }
        return true;
    }

    void display_board() override {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                std::cout << "(" << i << "," << j << ")";
                if (board[i][j] != ' ') {
                    std::cout << board[i][j];
                }
                if ((j + 1) % 3 == 0 && j != 8) std::cout << " | ";
            }
            std::cout << "\n";
            if ((i + 1) % 3 == 0 && i != 8)
                std::cout << "------------------------------------------------\n";
        }
        std::cout << "\n";
    }

    bool is_win_for_player(int player) {
        return check_three_grids_in_a_row(player);
    }

    bool is_win() override {
        return is_win_for_player(0) || is_win_for_player(1);
    }

    bool is_draw() override {
        return moves == 81;
    }

    bool game_is_over() override {
        return is_win_for_player(0) || is_win_for_player(1) || is_draw();
    }
};

class X_O_Player_ : public Player<char> {
public:
    X_O_Player_(const std::string& name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        std::cout << this->getname() << "'s turn (" << this->getsymbol() << "). Enter row and column: ";
        std::cin >> x >> y;
    }
};

class X_O_Random_Player_ : public Player<char> {
public:
    X_O_Random_Player_(char symbol) : Player("Random Computer", symbol) {
        std::srand(std::time(nullptr));
    }

    void getmove(int& x, int& y) override {
        x = std::rand() % 9;
        y = std::rand() % 9;
        std::cout << this->getname() << " chooses (" << x << ", " << y << ").\n";
    }
};

#endif //ULTIMATE_TIC_TAC_TOE_H