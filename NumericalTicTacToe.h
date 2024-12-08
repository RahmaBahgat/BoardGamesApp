//
// Created by MALAK on 12/3/2024.
//

#ifndef NUMERICALTICTACTOE_H
#define NUMERICALTICTACTOE_H

#include "BoardGame_Classes.h"

template<typename T>
class NumericalTicTacToe_Board : public Board<T> {
    vector<int> keepTrack; // Persistent across moves
public:
    NumericalTicTacToe_Board();
    ~NumericalTicTacToe_Board(); // Destructor for cleanup
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
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
NumericalTicTacToe_Board<T>::NumericalTicTacToe_Board() : keepTrack(9, 0) {
    this->columns = 3;
    this->rows = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns]{0};
    }
    this->n_moves = 0;
}

template<typename T>
NumericalTicTacToe_Board<T>::~NumericalTicTacToe_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template<typename T>
bool NumericalTicTacToe_Board<T>::update_board(int x, int y, T number) {


    // Validate coordinates and check if the cell is empty
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        cout << "Invalid input: Cell is either out of bounds or already occupied.\n";
        return false;
    }

    // Check if the number has already been used
    if (keepTrack[number - 1] > 0) { // Numbers are only used once
        cout << "Invalid input: Number " << number << " has already been used.\n";
        return false;
    }

    // Enforce odd/even number rules based on the move count
    if (this->n_moves % 2 == 0) { // First Player
        if (number % 2 == 0) {
            cout << "First Player must choose an odd number.\n";
            return false;
        }
    } else { // Second Player
        if (number % 2 != 0) {
            cout << "Second Player must choose an even number.\n";
            return false;
        }
    }

    // Place the number on the board
    this->board[x][y] = number;
    ++keepTrack[number - 1]; // Mark the number as used
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

    //Diagonals
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if(i - 2 >= 0 && j + 2 < this->columns) {
                if (this->board[i][j] + this->board[i - 1 ][j + 1] + this->board[i - 2 ][j + 2] == 15) {
                    return true;
                }
            }
            else if(i + 2 < this->rows && j + 2 < this ->columns) {
                if (this->board[i][j] + this->board[i + 1 ][j + 1] + this->board[i + 2 ][j + 2] == 15) {
                    return true;
                }
            }
        }
    }


    //Horizontal
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(i + 2 < this->columns) {
                if (this->board[j][i] + this->board[j][i + 1] + this->board[j][i + 2] == 15) {
                    return true;
                }
            }
        }
    }


    //Vertical X
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(j + 2 < this->rows ) {
                if (this->board[j][i] +  this->board[j + 1 ][i] + this->board[j + 2 ][i] ==  15) {
                    return true;
                }
            }
        }
    }

    return false;
}

template<typename T>
bool NumericalTicTacToe_Board<T>::is_draw() {
    return this-> n_moves == 9 && !is_win();
}

template<typename T>
bool NumericalTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
//--------------------------------------------------------------------------------------

// Constructor for NumericalTicTacToe player
template<typename T>
NumericalTicTacToe_Player<T>::NumericalTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol){}

template<typename T>
void NumericalTicTacToe_Player<T>::getmove(int &x, int &y) {
    cout << "Please enter the coordinates of the move : (e.g. 0 2)\n";
    cin >> x;
    cin >> y;
    cout << "Enter a number between 1 to 9 :\n";
    cin >> this->symbol;
    cin.ignore();
}
template<typename T>
NumericalTicTacToe_RandomPlayer <T>::NumericalTicTacToe_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this ->dimension = 9;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

}
template<typename T>
void NumericalTicTacToe_RandomPlayer <T>::getmove(int &x, int &y) {
    x = rand() % 3;  // Random number between 0 and 2
    y = rand() % 3;  // Random number between 0 and 2
    int numberPC = rand() % 10;
    if(this->symbol == 1) {
        while(numberPC % 2 == 0 ) {
            numberPC = rand() % 10;
        }
    }
    else if(this->symbol == 2) {
        while(numberPC % 2 != 0 ) {
            numberPC = rand() % 10;
        }
    }
    this->symbol = numberPC;
    
}
#endif //NUMERICALTICTACTOE_H