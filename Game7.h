//
// Created by MALAK on 12/16/2024.
//

#ifndef GAME7_H
#define GAME7_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
using namespace std;

// Global variables to store random coordinates for moves
int globalX1;
int globalY1;

// TicTacToeBoard class definition - inherits from Board<T>
template <typename T>
class TicTacToe4x4_Board : public Board<T> {
public:
    TicTacToe4x4_Board(); // Constructor to initialize the board
    ~TicTacToe4x4_Board(); // Destructor to clean up dynamically allocated memory

    bool update_board(int row, int col, T symbol) override; // Update the board with a move
    void display_board() override; // Display the board to the console
    bool is_win() override; // Check if there's a win condition
    bool is_draw() override; // Check if the game is a draw
    bool game_is_over() override; // Check if the game is over
    static bool is_adjacent(int x1, int y1, int x2, int y2); // Check if two cells are adjacent
};

// TicTacToePlayer class definition - inherits from Player<T>
template <typename T>
class TicTacToe4x4_Player : public Player<T> {
public:
    TicTacToe4x4_Player(string name, T symbol); // Constructor to initialize the player with a name and symbol
    void getmove(int& x, int& y) override; // Get the player's move
};

// TicTacToeRandomPlayer class definition - inherits from Player<T>
template <typename T>
class TicTacToe4x4_RandomPlayer : public Player<T> {
public:
    TicTacToe4x4_RandomPlayer(T symbol); // Constructor to initialize the random player with a symbol
    void getmove(int& x, int& y) override; // Generate a random move
    bool is_valid_move(int row, int col); // Check if a move is valid
};

// Implementation of TicTacToeBoard methods

template <typename T>
TicTacToe4x4_Board<T>::TicTacToe4x4_Board() {
    this->rows = 4; // Set number of rows
    this->columns = 4; // Set number of columns

    // Allocate memory for the board
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' '; // Initialize all cells with empty spaces
        }
    }

    this->n_moves = 0; // Initialize move counter

    // Initialize specific cells for starting board state
    if (this->n_moves == 0) {
        this->board[0][0] = 'O'; this->board[0][1] = 'X'; this->board[0][2] = 'O'; this->board[0][3] = 'X';
        this->board[2][0] = 'X'; this->board[2][1] = 'O'; this->board[2][2] = 'X'; this->board[2][3] = 'O';
    }
}

// Destructor to clean up the dynamically allocated memory
template <typename T>
TicTacToe4x4_Board<T>::~TicTacToe4x4_Board() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i]; // Delete each row
    }
    delete[] this->board; // Delete the array of rows
}

// Check if two cells are adjacent
template <typename T>
bool TicTacToe4x4_Board<T>::is_adjacent(int x1, int y1, int x2, int y2) {
    return (abs(x1 - x2) == 1 && y1 == y2) || (abs(y1 - y2) == 1 && x1 == x2); // Adjacent if one cell is directly next to the other
}

// Update the board with a move
template <typename T>
bool TicTacToe4x4_Board<T>::update_board(int row, int col, T symbol) {
    // Random player logic
    if (symbol == '1' || symbol == '2') {
        if (row >= 0 && row < this->rows && col >= 0 && col < this->columns) {
            symbol = (symbol == '1') ? 'X' : 'O'; // Convert player identifier to symbol
            if (this->board[row][col] == symbol) {
                // Check if the move is valid and adjacent
                if (is_adjacent(row, col, globalX1, globalY1)) {
                    if (this->board[globalX1][globalY1] == ' ') { // Ensure target cell is empty
                        this->board[row][col] = ' '; // Clear current cell
                        this->board[globalX1][globalY1] = symbol; // Move to target cell
                        ++this->n_moves; // Increment move counter
                        cout << endl;
                        return true;
                    }
                    return false;
                }
                return false;
            }
            return false; // The cell is not owned by the player
        }
        return false; // Coordinates are out of bounds
    }

    // Human player logic
    if (row >= 0 && row < this->rows && col >= 0 && col < this->columns) {
        int nextRow, nextCol;
        if (this->board[row][col] == symbol) {
            cout << "Enter the row and column where you want to move: ";
            cin >> nextRow >> nextCol;

            if (this->board[nextRow][nextCol] == ' ' && is_adjacent(row, col, nextRow, nextCol)) {
                this->board[row][col] = ' '; // Clear current cell
                this->board[nextRow][nextCol] = symbol; // Move to target cell
                ++this->n_moves; // Increment move counter
                cout << endl;
                return true;
            }
            cout << "The destination cell must be empty and adjacent to the current cell." << endl;
            return false;
        }
    }
    return false; // General error
}

// Display the board to the console
template <typename T>
void TicTacToe4x4_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "|";
        for (int j = 0; j < this->columns; j++) {
            cout << '[' << i << "," << j << "]  " << this->board[i][j] << "|"; // Print cell with coordinates
        }
        cout << endl;
    }
}

// Check if there's a win condition
template <typename T>
bool TicTacToe4x4_Board<T>::is_win() {
    // Check rows and columns for a win

    //Horizontal O - Next to each other
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(i + 2 <= this->columns ) {
                if (this->board[j][i] == 'O' && this->board[j][i + 1] == 'O' && this->board[j][i + 2] == 'O') {
                    return true;
                }
            }
        }
    }

    //Horizontal X - Next to each other
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(i + 2 < this->columns ) {
                if (this->board[j][i] == 'X' && this->board[j][i + 1] == 'X' && this->board[j][i + 2] == 'X') {
                    return true;
                }
            }
        }
    }

    //Vertical X - Next to each other
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(j + 2 < this->rows ) {
                if (this->board[j][i] == 'X' && this->board[j + 1 ][i] == 'X' && this->board[j + 2 ][i] == 'X') {
                    return true;
                }
            }
        }
    }

    //Vertical O - Next to each other
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(j + 2 < this->rows ) {
                if (this->board[j][i] == 'O' && this->board[j + 1 ][i] == 'O' && this->board[j + 2 ][i] == 'O') {
                    return true;
                }
            }
        }
    }

    // Check diagonals for a win
    //Diagonals for O
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if(i - 2 >= 0 && j + 2 < this->columns) {
                if (this->board[i][j] == 'O' && this->board[i - 1 ][j + 1] == 'O' && this->board[i - 2 ][j + 2] == 'O' ) {
                    return true;
                }
            }
            else if(i + 2 < this->rows && j + 2 >= 0) {
                if (this->board[i][j] == 'O' && this->board[i + 1 ][j + 1] == 'O' && this->board[i + 2 ][j + 2] == 'O' ) {
                    return true;
                }
            }
        }
    }

    //Diagonals for X
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if(i - 2 >= 0 && j + 2 < this->columns) {
                if (this->board[i][j] == 'X' && this->board[i - 1 ][j + 1] == 'X' && this->board[i - 2 ][j + 2] == 'X' ) {
                    return true;
                }
            }
            else if(i + 2 < this->rows && j + 2 >= 0) {
                if (this->board[i][j] == 'X' && this->board[i + 1 ][j + 1] == 'X' && this->board[i + 2 ][j + 2] == 'X' ) {
                    return true;
                }
            }
        }
    }

    return false; // No win condition
}

// Check if the game is a draw
template <typename T>
bool TicTacToe4x4_Board<T>::is_draw() {
    return this->n_moves == 100; // Assume draw if max moves reached (arbitrary number)
}

// Check if the game is over
template <typename T>
bool TicTacToe4x4_Board<T>::game_is_over() {
    return is_win(); // Game is over if there's a win condition
}

// Implementation of TicTacToePlayer methods

template <typename T>
TicTacToe4x4_Player<T>::TicTacToe4x4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void TicTacToe4x4_Player<T>::getmove(int& x, int& y) {
    cout << "Choose which cell you will move?" << endl;
    cin >> x >> y; // Prompt user for coordinates
}

// Implementation of TicTacToeRandomPlayer methods

template <typename T>
TicTacToe4x4_RandomPlayer<T>::TicTacToe4x4_RandomPlayer(T symbol) : Player<T>(symbol) {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
bool TicTacToe4x4_RandomPlayer<T>::is_valid_move(int row, int col) {
    return this->boardPtr->update_board(row, col, this->symbol); // Check and update the board
}

template <typename T>
void TicTacToe4x4_RandomPlayer<T>::getmove(int& row, int& col) {
    row = rand() % 4; // Generate random row
    col = rand() % 4; // Generate random column
    globalX1 = rand() % 4; // Generate random target row
    globalY1 = rand() % 4; // Generate random target column
}

#endif
