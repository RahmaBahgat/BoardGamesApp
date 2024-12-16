#ifndef _ULTIMATE_TIC_TAC_TOE_H
#define _ULTIMATE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>

// X_O_Board class
class X_O_Board : public Board<char> {
private:
    char board[9][9]; // 9x9 board for ultimate tic-tac-toe
    int moves = 0; // Number of moves made
    int subGridWinner[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}; // -1: unclaimed, 0: X, 1: O

    // Check if a player has won in a 3x3 grid
    bool checkWinInSmall(int startRow, int startCol, char symbol) {
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

    // Check if a player has won three grids in a row
    bool checkWinInUltimate(int player) {
        // Check horizontal and vertical
        for (int i = 0; i < 3; ++i) {
            if ((subGridWinner[i][0] == player && subGridWinner[i][1] == player && subGridWinner[i][2] == player) ||
                (subGridWinner[0][i] == player && subGridWinner[1][i] == player && subGridWinner[2][i] == player)) {
                return true;
            }
        }
        // Check diagonals
        if ((subGridWinner[0][0] == player && subGridWinner[1][1] == player && subGridWinner[2][2] == player) ||
            (subGridWinner[0][2] == player && subGridWinner[1][1] == player && subGridWinner[2][0] == player)) {
            return true;
        }
        return false;
    }

public:
    // Constructor to initialize the board
    X_O_Board() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = ' '; // Initialize all cells to empty
            }
        }
    }

    // Update the board with a move
    bool update_board(int x, int y, char symbol) override {
        // Validate the move
        if (x < 0 || x >= 9 || y < 0 || y >= 9 || board[x][y] != ' ') {
            return false;
        }
        board[x][y] = toupper(symbol); // Place the symbol on the board
        moves++; // Increment the move count

        // Update subGridWinner if a 3x3 grid is won
        int gridRow = x / 3;
        int gridCol = y / 3;
        if (subGridWinner[gridRow][gridCol] == -1 && checkWinInSmall(gridRow * 3, gridCol * 3, toupper(symbol))) {
            subGridWinner[gridRow][gridCol] = (toupper(symbol) == 'X') ? 0 : 1;
        }
        return true;
    }

    // Display the board
    void display_board() override {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != ' ') {
                    std::cout << " " << board[i][j] << " "; // Display the symbol if the cell is occupied
                } else {
                    std::cout << "(" << i << "," << j << ")"; // Display the cell coordinates if the cell is empty
                }
                if ((j + 1) % 3 == 0 && j != 8) std::cout << " | "; // Add vertical separators between grids
            }
            std::cout << "\n";
            if ((i + 1) % 3 == 0 && i != 8)
                std::cout << "------------------------------------------------\n"; // Add horizontal separators between grids
        }
        std::cout << "\n";
    }

    // Check if a player has won the game
    bool is_win_for_player(int player) {
        return checkWinInUltimate(player);
    }

    // Check if there is a win
    bool is_win() override {
        return is_win_for_player(0) || is_win_for_player(1);
    }

    // Check if the game is a draw
    bool is_draw() override {
        return moves == 81;
    }

    // Check if the game is over
    bool game_is_over() override {
        return is_win_for_player(0) || is_win_for_player(1) || is_draw();
    }
};

// X_O_Player class definition
class X_O_Player : public Player<char> {
public:
    // Constructor
    X_O_Player(const std::string& name, char symbol) : Player<char>(name, symbol) {}

    // Get the player's move
    void getmove(int& x, int& y) override {
        std::cout << this->getname() << "'s turn (" << this->getsymbol() << "). Enter row and column: ";
        std::cin >> x >> y;
    }
};

// X_O_Random_Player class definition
class X_O_Random_Player : public Player<char> {
public:
    // Constructor
    X_O_Random_Player(char symbol) : Player<char>("Random Computer", symbol) {
        std::srand(std::time(nullptr));
    }

    // Get a random move
    void getmove(int& x, int& y) override {
        x = std::rand() % 9;
        y = std::rand() % 9;
        std::cout << this->getname() << " chooses (" << x << ", " << y << ").\n";
    }
};

#endif //_ULTIMATE_TIC_TAC_TOE_H