#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"

// Class definition for the Misere Tic-Tac-Toe board
template <typename T>
class Misere_Board : public Board<T> {
public:
    Misere_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();  // Method to check if a player has won (for Misere, this means they lose)
    bool is_draw();
    bool game_is_over();
};

// Class definition for a player
template <typename T>
class Misere_Player : public Player<T> {
public:
    Misere_Player(string name, T symbol);
    void getmove(int& x, int& y);  // Method to get the player's move
};

// Class definition for a random player
template <typename T>
class Misere_Random_Player : public RandomPlayer<T> {
public:
    Misere_Random_Player(T symbol);  
    void getmove(int& x, int& y);  // Method to generate a random move
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// Constructor for Misere_Board
template <typename T>
Misere_Board<T>::Misere_Board() {
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
bool Misere_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;  // Increment the number of moves
        this->board[x][y] = toupper(mark); 
        return true;
    }
    return false;  // Return false if move is invalid
}

// Method to display the current state of the board
template <typename T>
void Misere_Board<T>::display_board() {
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
bool Misere_Board<T>::is_win() {
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
bool Misere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());  // Return true if 9 moves are made and no winner
}

// Method to check if the game is over (either win or draw)
template <typename T>
bool Misere_Board<T>::game_is_over() {
    return is_win() || is_draw();  // Return true if the game is over
}

//--------------------------------------

// Constructor for Misere_Player
template <typename T>
Misere_Player<T>::Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Method for getting the player's move input
template <typename T>
void Misere_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;  // Input coordinates for the move
}

// Constructor for Misere_Random_Player
template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;  // Set the board size to 3x3
    this->name = "Random Computer Player";  // Name for the random player
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Method for generating a random move for the computer player
template <typename T>
void Misere_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Generate a random x coordinate between 0 and 2
    y = rand() % this->dimension;  // Generate a random y coordinate between 0 and 2
}

// Class definition for the Misere game manager
template <typename T>
class MisereGameManager : public GameManager<T> {
public:
    MisereGameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) : GameManager<T>(bPtr, playerPtr) {}
    void run();  // Method to run the game
};

// Method to run the game (override)
template <typename T>
void MisereGameManager<T>::run() {
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
                cout << this->players[(i + 1) % 2]->getname() << " wins\n"; // Opponent wins
                return;
            }
            if (this->boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}

#endif //_3X3X_O_H
