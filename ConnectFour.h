//
// Created by MALAK on 12/3/2024.
//

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "BoardGame_Classes.h"

template <typename T>
class ConnectFourBoard : public Board<T> {
public:
    ConnectFourBoard ();
    bool update_board (int x , int y , T symbol) override;
    void display_board () override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template <typename T>
class ConnectFourPlayer : public Player<T> {
    public:
    ConnectFourPlayer (string name , T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class ConnectFourRandomPlayer : public RandomPlayer<T> {
    public:
    ConnectFourRandomPlayer (T symbol);
    void getmove(int& x, int& y) override;
};

//------------- IMPLEMENTATION-------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

//Constructor for connect 4 board
template<typename T>
ConnectFourBoard<T>::ConnectFourBoard() {
    this -> columns = 7 ;
    this -> rows = 6 ;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0 ;
}

template<typename T>
bool ConnectFourBoard<T>::update_board(int x, int y, T symbol) {
    if ( x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != ' ') {
        cout << "Invalid input" << endl;
        return false;
    }

    for (int i = this -> rows - 1 ; i >= 0; --i) {//Must start from the bottom so for the fiven col chechk the rows from down
        if(this->board[i][y] == ' ') {
            if (x != i ) {
                return false;
            }
            if (x == i) {
                this->board[x][y] = toupper(symbol);
                ++this->n_moves;
                return true;
            }
        }
    }
    this->board[x][y] = toupper(symbol);
    ++this->n_moves;
    return true;
}

template<typename T>
void ConnectFourBoard<T>::display_board() {
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
bool ConnectFourBoard<T>::is_win() {
//first player to get four-in-a-row vertically, horizontally, or diagonally wins.

    //Diagonals for O
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if(i - 4 >= 0 && j + 4 < this->columns) {
                if (this->board[i][j] == 'O' && this->board[i - 1 ][j + 1] == 'O' && this->board[i - 2 ][j + 2] == 'O' && this->board[i - 3][j + 3] == 'O') {
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
template<typename T>
ConnectFourPlayer<T>::ConnectFourPlayer(string name, T symbol) : Player<T>(name, symbol){}

template<typename T>
void ConnectFourPlayer<T>::getmove(int &x, int &y) {
    cout << "Please enter the coordinates of the move : (e.g. 0 2)\n";
    cin >> x;
    cin >> y;
    cin.ignore();
}
template<typename T>
ConnectFourRandomPlayer<T>::ConnectFourRandomPlayer(T symbol) : RandomPlayer<T>(symbol){}

template<typename T>
void ConnectFourRandomPlayer<T>::getmove(int &x, int &y) {
    x = rand() % 6;  // Random number between 0 and 5
    y = rand() % 7;  // Random number between 0 and 6
}

#endif //CONNECTFOUR_H
