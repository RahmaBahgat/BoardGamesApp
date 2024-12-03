//
// Created by MALAK on 12/3/2024.
//

#ifndef NUMERICALTICTACTOE_H
#define NUMERICALTICTACTOE_H

#include "BoardGame_Classes.h"

template <typename T>
class NumericalTicTacToe_Board : public Board<T> {
public:
    NumericalTicTacToe_Board ();
    bool update_board (int x , int y , T symbol) override;
    void display_board () override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template <typename T>
class NumericalTicTacToe_Player : public Player<T> {
public:
    NumericalTicTacToe_Player (string name , T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class NumericalTicTacToe_RandomPlayer : public RandomPlayer<T> {
public:
    NumericalTicTacToe_RandomPlayer (T symbol);
    void getmove(int& x, int& y) override;
};

//------------- IMPLEMENTATION-------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

//Constructor for NumericalTicTacToe board
template<typename T>
NumericalTicTacToe_Board <T>::NumericalTicTacToe_Board () {
    this -> columns = 3 ;
    this -> rows = 3 ;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0 ;
        }
    }
    this->n_moves = 0 ;
}

template<typename T>
bool NumericalTicTacToe_Board<T>::update_board(int x, int y, T number) {
    vector<int>keepTrack(9 , 0);
    if ( x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        cout << "Invalid input" << endl;
        return false;
    }
    if(keepTrack[number] > 1) { //numbers are only used once
        return false;
    }
    if(this->n_moves % 2 == 0) {
        if(number % 2 == 0) {
            cout << "First Player Must choose an ood number \n";
            return false;
        }
    }
    if(this->n_moves % 2 == 1) {
        if(number % 2 != 0) {
            cout << "Second Player Must choose an even number \n";
            return false;
        }
    }

    this->board[x][y] = number;
    ++keepTrack[number - 1];
    ++this->n_moves;
    return true;
}

template<typename T>
void NumericalTicTacToe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            cout << "[" << i << "," << j << "]   ";
            cout << this->board[i][j] << "| ";
        }
    }
    cout << endl;
}

template<typename T>
bool NumericalTicTacToe_Board<T>::is_win() {
//Winning: A player wins by placing three numbers in a row, column, or diagonal that add up to 15.

    //Diagonal
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if(i - 2 >= 0 && j + 2 < this->columns) {
                if (this->board[i][j] + this->board[i - 1 ][j + 1] + this->board[i - 2 ][j + 2] == 15) {
                    return true;
                }
            }
            else if(i + 4 < this->rows && j - 4 >= 0) {
                if (this->board[i][j] == 'O' && this->board[i + 1 ][j + 1] == 'O' && this->board[i + 2 ][j + 2] == 'O' && this->board[i + 3][j + 3] == 'O') {
                    return true;
                }
            }
        }
    }

    //Diagonals for X
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if(i - 4 >= 0 && j + 4 < this->columns) {
                if (this->board[i][j] == 'X' && this->board[i - 1 ][j + 1] == 'X' && this->board[i - 2 ][j + 2] == 'X' && this->board[i - 3][j + 3] == 'X') {
                    return true;
                }
            }
            else if(i + 4 < this->rows && j - 4 >= 0) {
                if (this->board[i][j] == 'X' && this->board[i + 1 ][j + 1] == 'X' && this->board[i + 2 ][j + 2] == 'X' && this->board[i + 3][j + 3] == 'X') {
                    return true;
                }
            }
        }
    }

    //Horizontal O - Next to each other
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(i + 3 <= this->columns - 1) {
                if (this->board[j][i] == 'O' && this->board[j][i + 1] == 'O' && this->board[j][i + 2] == 'O' && this->board[j][i + 3] == 'O') {
                    return true;
                }
            }
        }
    }

    //Horizontal X - Next to each other
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(i + 3 < this->columns ) {
                if (this->board[j][i] == 'X' && this->board[j][i + 1] == 'X' && this->board[j][i + 2] == 'X' && this->board[j][i + 3] == 'X') {
                    return true;
                }
            }
        }
    }

    //Vertical X - Next to each other
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(j + 3 <= this->rows - 1) {
                if (this->board[j][i] == 'X' && this->board[j + 1 ][i] == 'X' && this->board[j + 2 ][i] == 'X' && this->board[j + 3 ][i] == 'X') {
                    return true;
                }
            }
        }
    }

    //Vertical O - Next to each other
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(j + 3 <= this->rows - 1) {
                if (this->board[j][i] == 'O' && this->board[j + 1 ][i] == 'O' && this->board[j + 2 ][i] == 'O' && this->board[j + 3 ][i] == 'O') {
                    return true;
                }
            }
        }
    }
    return false;
}

template<typename T>
bool ConnectFourBoard<T>::is_draw() {
    return this-> n_moves == 7*6 && !is_win();
}

template<typename T>
bool ConnectFourBoard<T>::game_is_over() {
    return is_win() || is_draw();
}
//--------------------------------------------------------------------------------------

// Constructor for connect 4 player

#endif //NUMERICALTICTACTOE_H
