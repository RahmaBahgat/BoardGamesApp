// Created by MALAK on 12/3/2024.
//

#ifndef NUMERICALTICTACTOE_H
#define NUMERICALTICTACTOE_H

#include "BoardGame_Classes.h"

template<typename T>
class NumericalTicTacToe_Board : public Board<T> {
    vector<int> keepTrack; // Track usage of numbers (1 to 9)
public:
    NumericalTicTacToe_Board();
    ~NumericalTicTacToe_Board(); // Destructor for cleanup
    bool update_board(int x, int y, T symbol) override; // Update the board with a player's move
    void display_board() override; // Display the current board state
    bool is_win() override; // Check if there is a winner
    bool is_draw() override; // Check if the game is a draw
    bool game_is_over() override; // Determine if the game is over
};

template <typename T>
class NumericalTicTacToe_Player : public Player<T> {
public:
    NumericalTicTacToe_Player (string name , T symbol); // Initialize player with a name and symbol
    void getmove(int& x, int& y) override; // Prompt the player for a move
};

template <typename T>
class NumericalTicTacToe_RandomPlayer : public RandomPlayer<T> {
public:
    NumericalTicTacToe_RandomPlayer (T symbol); // Initialize random player with a symbol
    void getmove(int& x, int& y) override; // Generate a random move
};

//------------- IMPLEMENTATION-------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

// Constructor for NumericalTicTacToe board
// Initializes a 3x3 board and the keepTrack vector to track used numbers

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

// Destructor for NumericalTicTacToe board
// Releases dynamically allocated memory

template<typename T>
NumericalTicTacToe_Board<T>::~NumericalTicTacToe_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

// Update the board with a player's move
// Validates the move, enforces game rules, and updates the board state

template<typename T>
bool NumericalTicTacToe_Board<T>::update_board(int x, int y, T number) {
    // For random player moves
    int numberPC = rand() % 10; // Generate random number between 0 and 9

    // If number is -1 or -2, handle special cases for odd/even numbers
    if (number == -1 || number == -2) {

        // Validate coordinates and check if the cell is empty
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
            return false;
        }

        if (number == -1) {
            // Generate a random odd number
            while (numberPC % 2 == 0) {
                numberPC = rand() % 10;
            }
        } else if (number == -2) {
            // Generate a random even number
            while (numberPC % 2 != 0) {
                numberPC = rand() % 10;
            }
        }
        number = numberPC;

        // Check if the number has already been used
        if (keepTrack[number - 1] > 0) {
            return false;
        }

        // Place the number on the board
        this->board[x][y] = number;
        ++keepTrack[number - 1]; // Mark the number as used
        ++this->n_moves;

        return true;
    }

    // For human player moves

    // check if the cell is empty
    if (this->board[x][y] != 0) {
        cout << "Invalid input: Cell is either out of bounds or already occupied.\n";
        return false;
    }

    // Check if the number has already been used
    if (keepTrack[number - 1] > 0) {
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

// Display the current state of the board

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

// Check if the current board state is a win
// Winning condition: Three numbers in a row, column, or diagonal add up to 15

template<typename T>
bool NumericalTicTacToe_Board<T>::is_win() {
    // Check all rows, columns, and diagonals for the winning condition
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            // Check row (horizontal)
            if (j + 2 < this->columns &&
                this->board[i][j] != 0 && this->board[i][j + 1] != 0 && this->board[i][j + 2] != 0 &&
                this->board[i][j] + this->board[i][j + 1] + this->board[i][j + 2] == 15) {
                return true;
                }

            // Check column (vertical)
            if (i + 2 < this->rows &&
                this->board[i][j] != 0 && this->board[i + 1][j] != 0 && this->board[i + 2][j] != 0 &&
                this->board[i][j] + this->board[i + 1][j] + this->board[i + 2][j] == 15) {
                return true;
                }

            // Check diagonal (top-left to bottom-right)
            if (i + 2 < this->rows && j + 2 < this->columns &&
                this->board[i][j] != 0 && this->board[i + 1][j + 1] != 0 && this->board[i + 2][j + 2] != 0 &&
                this->board[i][j] + this->board[i + 1][j + 1] + this->board[i + 2][j + 2] == 15) {
                return true;
                }

            // Check diagonal (bottom-left to top-right)
            if (i - 2 >= 0 && j + 2 < this->columns &&
                this->board[i][j] != 0 && this->board[i - 1][j + 1] != 0 && this->board[i - 2][j + 2] != 0 &&
                this->board[i][j] + this->board[i - 1][j + 1] + this->board[i - 2][j + 2] == 15) {
                return true;
                }
        }
    }

    return false;
}


// Check if the game is a draw
// A draw occurs when all cells are filled and there is no winner

template<typename T>
bool NumericalTicTacToe_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

// Check if the game is over
// The game is over if there is a win or a draw

template<typename T>
bool NumericalTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------------------------------------------------------

// Constructor for NumericalTicTacToe player
// Initializes a player with a name and a symbol

template<typename T>
NumericalTicTacToe_Player<T>::NumericalTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {

}

// Prompt the player for a move
// Input coordinates (x, y) and a number between 1 and 9

template<typename T>
void NumericalTicTacToe_Player<T>::getmove(int &x, int &y) {
    while (true) {
        cout << "Please enter the coordinates of the move (row and column between 0 and 2):\n";

        // Validate coordinates input
        if (!(cin >> x >> y)) {
            cin.clear(); // Clear invalid input flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter two numbers separated by a space.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear remaining input buffer

        // Validate that coordinates are within board limits (assuming a 3x3 grid)
        if (x >= 0 && x < 3 && y >= 0 && y < 3) {
            break; // Valid coordinates
        } else {
            cout << "Invalid coordinates! Row and column must be between 0 and 2.\n";
        }
    }
    while (true) {
        cout << "Enter a number between 1 and 9:\n";

        // Validate number input
        if (!(cin >> this->symbol)) {
            cin.clear(); // Clear invalid input flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a valid number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear remaining input buffer

        // Validate number is within the valid range
        if (this->symbol >= 1 && this->symbol <= 9) {
            break; // Valid number
        }
        else {
            cout << "Invalid number! Please choose a number between 1 and 9.\n";
        }
    }
}




// Constructor for NumericalTicTacToe random player
// Initializes a random player with a symbol and seeds the random generator

template<typename T>
NumericalTicTacToe_RandomPlayer<T>::NumericalTicTacToe_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->name = (symbol == 0) ? "Random Player 1" : "Random Player 2";

    this->dimension = 9;
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

// Generate a random move
// Assign random coordinates (x, y) within the board's bounds

template<typename T>
void NumericalTicTacToe_RandomPlayer<T>::getmove(int &x, int &y) {
    x = rand() % 3; // Random number between 0 and 2
    y = rand() % 3; // Random number between 0 and 2
    this->symbol = this->symbol; // Symbol remains unchanged
}

#endif //NUMERICALTICTACTOE_H
