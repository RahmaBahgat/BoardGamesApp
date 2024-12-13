//
// Created by MALAK on 12/13/2024.
//

#ifndef ULTIMATETICTACTOE_H
#define ULTIMATETICTACTOE_H
#include "BoardGame_Classes.h"

template<typename T>
class UltimateTicTacToe_Board : public Board<T> {
public:
    UltimateTicTacToe_Board();
    // ~UltimateTicTacToe_Board(); // Destructor for cleanup
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool check_sub_board_win(int row, int col, char player) const;
};

template <typename T>
class UltimateTicTacToe_Player : public Player<T> {
public:
    UltimateTicTacToe_Player (string name , T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class UltimateTicTacToe_RandomPlayer : public RandomPlayer<T> {
public:

    UltimateTicTacToe_RandomPlayer (T symbol);
    void getmove(int& x, int& y) override;
};

//------------- IMPLEMENTATION-------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

//Constructor for NumericalTicTacToe board
template<typename T>
UltimateTicTacToe_Board<T>::UltimateTicTacToe_Board() {
    this->columns = 9;
    this->rows = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns]{' '};
    }
    this->n_moves = 0;

}

template<typename T>
bool UltimateTicTacToe_Board<T>::update_board(int x, int y, T symbol) {
    if ( x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != ' ') {
        cout << "Invalid input" << endl;
        return false;
    }
    if (check_sub_board_win(x, y, symbol)) {
        this->board[x][y] = toupper(symbol);
        ++this->n_moves;
        return true;
    }

}


template<typename T>
void UltimateTicTacToe_Board<T>::display_board() {
    constexpr int sub_board_size = 3; // Each smaller board is 3x3
    constexpr int ultimate_size = sub_board_size * sub_board_size; // Total size is 9x9

    for (int ultimate_row = 0; ultimate_row < sub_board_size; ultimate_row++) {
        for (int sub_row = 0; sub_row < sub_board_size; sub_row++) {
            for (int ultimate_col = 0; ultimate_col < sub_board_size; ultimate_col++) {
                cout << "|";
                for (int sub_col = 0; sub_col < sub_board_size; sub_col++) {
                    // Map the smaller board's indices to the ultimate board's index
                    int i = ultimate_row * sub_board_size + sub_row;
                    int j = ultimate_col * sub_board_size + sub_col;

                    // Print each cell with indices
                    cout << " [" << i << "," << j << "]  ";
                }
                cout << " | ";
            }
            cout << endl; // End of a sub-row within the ultimate board
        }

        // Clear separation between sub-board rows
        cout << string((sub_board_size * (sub_board_size * 8 + 4)), '-') << endl;
    }
    cout << endl;
}

template<typename T>
bool UltimateTicTacToe_Board<T>::check_sub_board_win(int row, int col, char player) const {
    // Check rows, columns, and diagonals in the specific sub-board
    for (int i = 0; i < 3; i++) {
        if (this->board[row][col][i][0] == player && this->board[row][col][i][1] == player && this->board[row][col][i][2] == player)
            return true; // Row win
        if (this->board[row][col][0][i] == player && this->board[row][col][1][i] == player && this->board[row][col][2][i] == player)
            return true; // Column win
    }
    // Diagonal wins
    if (this->board[row][col][0][0] == player && this->board[row][col][1][1] == player && this->board[row][col][2][2] == player)
        return true;
    if (this->board[row][col][0][2] == player && this->board[row][col][1][1] == player && this->board[row][col][2][0] == player)
        return true;

    return false;
}



template<typename T>
bool UltimateTicTacToe_Board<T>::is_win() {
    return false;
}

template<typename T>
bool UltimateTicTacToe_Board<T>::is_draw() {
    return this-> n_moves == 9 * 9 && !is_win();
}

template<typename T>
bool UltimateTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------------------------------------------------------


template<typename T>
UltimateTicTacToe_Player<T>::UltimateTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void UltimateTicTacToe_Player<T>::getmove(int &x, int &y) {
    cout << "Please enter the coordinates of the move : (e.g. 0 2)\n";
    cin >> x;
    cin >> y;
    cin.ignore();
}

template<typename T>
UltimateTicTacToe_RandomPlayer<T>::UltimateTicTacToe_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

}

template<typename T>
void UltimateTicTacToe_RandomPlayer<T>::getmove(int &x, int &y) {
    x = rand() % 9;  // Random number between 0 and 8
    y = rand() % 9;  // Random number between 0 and 8

}
#endif //ULTIMATETICTACTOE_H
