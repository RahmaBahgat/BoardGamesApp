/*
 * Created by pc on 02-12-2024.
 */
#ifndef A2_GAME1_GAME1_H
#define A2_GAME1_GAME1_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include "BoardGame_Classes.h"
using namespace std;

// Class representing a Pyramid X-O Board
// Derived from Board<T>
template <typename T>
class pyramid_X_O_Board:public Board<T> {
public:
    pyramid_X_O_Board (); // Constructor to initialize the board
    bool update_board (int x , int y , T mark); // Updates the board with a move
    void display_board () ; // Displays the current state of the board
    bool is_win() ; // Checks if there is a winning condition
    bool is_draw(); // Checks if the game is a draw
    bool game_is_over(); // Checks if the game is over

};

// Class representing a Player for Pyramid X-O
// Derived from Player<T>
template <typename T>
class pyramid_X_O_Player : public Player<T> {
public:
    pyramid_X_O_Player (string name, T symbol); // Constructor to initialize player with name and symbol
    void getmove(int& x, int& y) ; // Prompts the player for their move

};

// Class representing a Random Player for Pyramid X-O
// Derived from RandomPlayer<T>
template <typename T>
class pyramid_X_O_Random_Player : public RandomPlayer<T>{
public:
    explicit pyramid_X_O_Random_Player (T symbol); // Constructor to initialize with a symbol
    void getmove(int &x, int &y) ; // Generates a random move
};

//------------------------------------------------------------------------IMPLEMENTATION

// Constructor for pyramid_X_O_Board
// Initializes the board with 3 rows and 5 columns
template <typename T>
pyramid_X_O_Board<T>::pyramid_X_O_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Updates the board with a player's move
template <typename T>
bool pyramid_X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (((x == 0 && y == 0) ||
         (x == 1 && y >= 0 && y <= 2) ||
         (x == 2 && y >= 0 && y <= 4)) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0; // Reset the cell
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark); // Update the cell with the player's mark
        }

        return true;
    }
    return false;
}

// Displays the board with formatting
template <typename T>
void pyramid_X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        // Calculate the number of "stars" (indexes) for the current row
        int indexes = 1 + (i * (this->columns - 1)) / (this->rows - 1);
        // Calculate the spaces required for centering the stars
        int spaces = (this->columns - indexes) / 2;
        // Print spaces for centering
        for (int j = 0; j < spaces; j++) {
            cout << "     "; // Four spaces for better alignment
        }
        // Print the board content for the current row
        for (int k = 0; k < indexes; k++) {
            cout << "|" << setw(2) << this->board[i][k];
            cout << "(" << i << "," << k << ")";

        }
        cout << "|\n";

        // Print row separator
        cout << string(9 * this->columns, '-') << endl;
    }
    cout << endl << endl;
}

// Checks if there is any winner
template <typename T>
bool pyramid_X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[1][0] == this->board[1][1] && this->board[1][1] == this->board[1][2] &&
             this->board[1][0] != 0) ||
            (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] &&
             this->board[0][0] != 0) ||
            (this->board[2][i] == this->board[2][i + 1] && this->board[2][i + 1] == this->board[2][i + 2] &&
             this->board[2][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[0][0] != 0) ||
        (this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != 0)) {
        return true;
    }

    return false;
}

// Checks if the game is a draw
template <typename T>
bool pyramid_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Checks if the game is over (either win or draw)
template <typename T>
bool pyramid_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for pyramid_X_O_Player
// Initializes the player with their name and symbol
template <typename T>
pyramid_X_O_Player<T>::pyramid_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Prompts the player for their move
template <typename T>
void pyramid_X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for pyramid_X_O_Random_Player
// Initializes a random player with their symbol and default name
template <typename T>
pyramid_X_O_Random_Player<T>::pyramid_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Generates a random move for the player
template <typename T>
void pyramid_X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif //A2_GAME1_GAME1_H
