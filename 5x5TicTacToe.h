#ifndef FIVE_BY_FIVE_TICTACTOE_H
#define FIVE_BY_FIVE_TICTACTOE_H

// Including necessary header files
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


template <typename T>
class fiveByFiveTicTacToeBoard : public Board<T> {
public:
    fiveByFiveTicTacToeBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

// class representing a player
template <typename T>
class TicTacToePlayer : public Player<T> {
public:
    TicTacToePlayer(string name, T symbol); // Constructor to initialize player with a name and symbol
    void getmove(int& x, int& y) override; // Function to get the player's move (coordinates)
};

//class representing a random player
template <typename T>
class TicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    TicTacToeRandomPlayer(T symbol); // Constructor to initialize random player with a symbol
    void getmove(int& x, int& y) override; // Function to generate random move
};

// class to manage the game with a 5x5 TicTacToe board
template <typename T>
class GameManager5x5 : public GameManager<T> {
public:
    GameManager5x5(Board<T>* bPtr, Player<T>* playerPtr[2]) : GameManager<T>(bPtr, playerPtr) {} // Constructor passing board and players
    void run(); // Function to run the game
};

//--------------------------------------- IMPLEMENTATION

// Constructor for TicTacToeBoard
template <typename T>
fiveByFiveTicTacToeBoard<T>::fiveByFiveTicTacToeBoard() {
    // Initialize the board dimensions (5x5)
    this->rows = this->columns = 5;

    // Create a 2D array  for the board
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // Initialize empty spaces with 0
        }
    }
    this->n_moves = 0; // Initialize number of moves to 0
}

// Function to update the board with a player's move
template <typename T>
bool fiveByFiveTicTacToeBoard<T>::update_board(int x, int y, T mark) {
    // Check if the position is valid
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->n_moves++; // Increment move count
        this->board[x][y] = toupper(mark); // Mark the position with the player's symbol
        return true;
    }
    return false; // Return false if the move is invalid
}

// Function to display the board
template <typename T>
void fiveByFiveTicTacToeBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            // Display each cell, with coordinates for reference
            cout << "(" << i << "," << j << ") " << setw(2) << this->board[i][j] << " | ";
        }
        cout << "\n-----------------------------------------------------"; // Row separator
    }
    cout << endl;
}

// Function to check if there is a winner
template <typename T>
bool fiveByFiveTicTacToeBoard<T>::is_win() {
    // Check rows for a winning condition
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] != 0 &&
            this->board[i][0] == this->board[i][1] &&
            this->board[i][1] == this->board[i][2] &&
            this->board[i][2] == this->board[i][3] &&
            this->board[i][3] == this->board[i][4]) {
            return true;
        }
    }

    // Check columns for a winning condition
    for (int j = 0; j < this->columns; j++) {
        if (this->board[0][j] != 0 &&
            this->board[0][j] == this->board[1][j] &&
            this->board[1][j] == this->board[2][j] &&
            this->board[2][j] == this->board[3][j] &&
            this->board[3][j] == this->board[4][j]) {
            return true;
        }
    }

    // Check diagonals for a winning condition
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

    return false; // Return false if no winning
}

// Function to check if the game is a draw
template <typename T>
bool fiveByFiveTicTacToeBoard<T>::is_draw() {
    return (this->n_moves == 25 && !is_win()); // Game is a draw if 25 moves are made and there is no winner
}

// Function to check if the game is over (either a win or a draw)
template <typename T>
bool fiveByFiveTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw(); // Game is over if there's a win or a draw
}

// Constructor for TicTacToePlayer to initialize player with name and symbol
template <typename T>
TicTacToePlayer<T>::TicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

// Function to get the player's move (coordinates) from input
template <typename T>
void TicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\n" << this->getname() << ", enter your move (x y): ";
    cin >> x >> y; // Get x and y coordinates from user input
}

// Constructor for TicTacToeRandomPlayer to initialize random player with symbol
template <typename T>
TicTacToeRandomPlayer<T>::TicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5; // Set the dimension of the board (5x5)
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

// Function to generate a random move for the random player
template <typename T>
void TicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension; // Generate random x coordinate (0-4)
    y = rand() % this->dimension; // Generate random y coordinate (0-4)
}

// Function to run the game, alternating turns between players and checking for game over
template <typename T>
void GameManager5x5<T>::run() {
    int x, y;
    this->boardPtr->display_board(); // Display initial board
    while (!this->boardPtr->game_is_over()) {
        for (int i : {0, 1}) { // Loop over both players
            this->players[i]->getmove(x, y); // Get the move from the current player
            while (!this->boardPtr->update_board(x, y, this->players[i]->getsymbol())) {
                this->players[i]->getmove(x, y); // If the move is invalid, ask for another move
            }
            this->boardPtr->display_board(); // Display the updated board
            if (this->boardPtr->is_win()) { // Check if the current player has won
                cout << this->players[i]->getname() << " wins!\n";
                return;
            }
            if (this->boardPtr->is_draw()) { // Check if the game is a draw
                cout << "It's a draw!\n";
                return;
            }
        }
    }
}

#endif // FIVE_BY_FIVE_TICTACTOE_H
