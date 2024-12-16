#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"

// Class definition for the Tic-Tac-Toe board
template <typename T>
class X_O_Board_ : public Board<T> {
public:
    X_O_Board_(); \
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();  // Method to check if a player has won (for Misere, this means they lose)
    bool is_draw();
    bool game_is_over();
};

// Class definition for a player
template <typename T>
class X_O_Player_ : public Player<T> {
public:
    X_O_Player_(string name, T symbol);  // Constructor to initialize player with a name and symbol
    void getmove(int& x, int& y);  // Method to get the player's move
};

// Class definition for a random player
template <typename T>
class X_O_Random_Player_ : public RandomPlayer<T> {
public:
    X_O_Random_Player_(T symbol);  // Constructor to initialize random player with a symbol
    void getmove(int& x, int& y);  // Method to generate a random move
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board_<T>::X_O_Board_() {
    this->rows = this->columns = 3;  // Set the board size to 3x3
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize each cell as empty (0)
        }
    }
    this->n_moves = 0;  // Initialize the number of moves to 0
}

// Method to update the board with the player's move
template <typename T>
bool X_O_Board_<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;  // Increment the number of moves
        this->board[x][y] = toupper(mark);  // Capitalize and place the mark (X or O)
        return true;
    }
    return false;  // Return false if move is invalid
}

// Method to display the current state of the board
template <typename T>
void X_O_Board_<T>::display_board() {
    // Loop through each row and column to print the board
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";  // Print the coordinates of each cell
            cout << setw(2) << this->board[i][j] << " |";  // Print the content of the cell
        }
        cout << "\n-----------------------------";  // Print a separator line
    }
    cout << endl;
}

// Method to check if a player has won (player loses by winning a row, column, or diagonal)
template <typename T>
bool X_O_Board_<T>::is_win() {
    // Check rows and columns for a winning line
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;  // A winning line is found, the player who made this move loses
        }
    }

    // Check diagonals for a winning line
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;  // A winning diagonal is found, the player who made this move loses
    }

    return false;  // No win condition found
}

// Method to check if the game is a draw
template <typename T>
bool X_O_Board_<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());  // Return true if 9 moves are made and no winner
}

// Method to check if the game is over (either win or draw)
template <typename T>
bool X_O_Board_<T>::game_is_over() {
    return is_win() || is_draw();  // Return true if the game is over
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player_<T>::X_O_Player_(string name, T symbol) : Player<T>(name, symbol) {}

// Method for getting the player's move input
template <typename T>
void X_O_Player_<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;  // Input coordinates for the move
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player_<T>::X_O_Random_Player_(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;  // Set the board size to 3x3
    this->name = "Random Computer Player";  // Name for the random player
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Method for generating a random move for the computer player
template <typename T>
void X_O_Random_Player_<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Generate a random x coordinate between 0 and 2
    y = rand() % this->dimension;  // Generate a random y coordinate between 0 and 2
}

#endif //_3X3X_O_H
