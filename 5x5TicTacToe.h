#ifndef FIVE_BY_FIVE_TICTACTOE_H
#define FIVE_BY_FIVE_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class TicTacToeBoard : public Board<T> {
public:
    TicTacToeBoard(); // Constructor
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template <typename T>
class TicTacToePlayer : public Player<T> {
public:
    TicTacToePlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class TicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    TicTacToeRandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};


template <typename T>
class GameManager5x5 : public GameManager<T> {
public:
    GameManager5x5(Board<T>* bPtr, Player<T>* playerPtr[2]) : GameManager<T>(bPtr, playerPtr) {}
    void run();
};

//--------------------------------------- IMPLEMENTATION

// Constructor for TicTacToeBoard
template <typename T>
TicTacToeBoard<T>::TicTacToeBoard() {
    this->rows = this->columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // Initialize empty spaces
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool TicTacToeBoard<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

template <typename T>
void TicTacToeBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ") " << setw(2) << this->board[i][j] << " | ";
        }
        cout << "\n-----------------------------------------------------";
    }
    cout << endl;
}

template <typename T>
bool TicTacToeBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] != 0 &&
            this->board[i][0] == this->board[i][1] &&
            this->board[i][1] == this->board[i][2] &&
            this->board[i][2] == this->board[i][3] &&
            this->board[i][3] == this->board[i][4]) {
            return true;
        }
    }
    for (int j = 0; j < this->columns; j++) {
        if (this->board[0][j] != 0 &&
            this->board[0][j] == this->board[1][j] &&
            this->board[1][j] == this->board[2][j] &&
            this->board[2][j] == this->board[3][j] &&
            this->board[3][j] == this->board[4][j]) {
            return true;
        }
    }
    if (this->board[0][0] != 0 &&
        this->board[0][0] == this->board[1][1] &&
        this->board[1][1] == this->board[2][2] &&
        this->board[2][2] == this->board[3][3] &&
        this->board[3][3] == this->board[4][4]) {
        return true;
    }
    if (this->board[0][4] != 0 &&
        this->board[0][4] == this->board[1][3] &&
        this->board[1][3] == this->board[2][2] &&
        this->board[2][2] == this->board[3][1] &&
        this->board[3][1] == this->board[4][0]) {
        return true;
    }
    return false;
}

template <typename T>
bool TicTacToeBoard<T>::is_draw() {
    return (this->n_moves == 25 && !is_win());
}

template <typename T>
bool TicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
TicTacToePlayer<T>::TicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void TicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\n" << this->getname() << ", enter your move (x y): ";
    cin >> x >> y;
}

template <typename T>
TicTacToeRandomPlayer<T>::TicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void TicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


template <typename T>
void GameManager5x5<T>::run() {
    int x, y;
    this->boardPtr->display_board();
    while (!this->boardPtr->game_is_over()) {
        for (int i : {0, 1}) {
            this->players[i]->getmove(x, y);
            while (!this->boardPtr->update_board(x, y, this->players[i]->getsymbol())) {
                this->players[i]->getmove(x, y);
            }
            this->boardPtr->display_board();
            if (this->boardPtr->is_win()) {
                cout << this->players[i]->getname() << " wins!\n";
                return;
            }
            if (this->boardPtr->is_draw()) {
                cout << "It's a draw!\n";
                return;
            }
        }
    }
}

#endif // FIVE_BY_FIVE_TICTACTOE_H
