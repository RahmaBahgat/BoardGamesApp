#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// SUS_Board class
template <typename T>
class SUS_Board : public Board<T> {
    Player<T>* players[2]; // Array to hold two players
    int counters[2] = {0, 0}; // Player scores

    bool completes_SUS(int x, int y, T mark); // Check if SUS is formed
    bool checker(int x, int y, char expected); // Check sequence
public:
    SUS_Board();
    void setPlayers(Player<T>* player1, Player<T>* player2);
    bool update_board(int x, int y, T mark);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void display_scores();
};

// SUS_Player class
template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player(string name, T symbol);
    void getmove(int& x, int& y); // Get the player's move
};

// SUS_Random_Player class
template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
    SUS_Random_Player(T symbol);
    void getmove(int& x, int& y); // Get a random move
};

//--------------------------------------- IMPLEMENTATION

// SUS_Board constructor
template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' '; // Initialize board cells to empty
        }
    }
    this->n_moves = 0;

    // Initialize players to nullptr
    players[0] = nullptr;
    players[1] = nullptr;
}

// Set players
template <typename T>
void SUS_Board<T>::setPlayers(Player<T>* player1, Player<T>* player2) {
    players[0] = player1;
    players[1] = player2;
}

// Update the board with a move
template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    // Validate the coordinates and the cell
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->n_moves++;
        this->board[x][y] = toupper(mark);

        // Ensure players are initialized
        if (!players[0] || !players[1]) {
            cerr << "Error: Players not initialized.\n";
            exit(EXIT_FAILURE); // Or handle it gracefully
        }

        // Determine the player index based on the mark
        int playerIndex = (toupper(mark) == toupper(players[0]->getsymbol())) ? 0 : 1;

        // Check if this move completes a "SUS" and update the player's score
        if (completes_SUS(x, y, mark)) {
            counters[playerIndex]++;
        }

        return true;
    }
    return false;
}

// Check if a "SUS" is formed
template <typename T>
bool SUS_Board<T>::completes_SUS(int x, int y, T mark) {
    bool susFound = false;

    // Check the row of the current move
    if (checker(x, 0, 'S') && checker(x, 1, 'U') && checker(x, 2, 'S')) {
        susFound = true;
    }

    // Check the column of the current move
    if (checker(0, y, 'S') && checker(1, y, 'U') && checker(2, y, 'S')) {
        susFound = true;
    }

    // Check the diagonal 1
    if (x == y && checker(0, 0, 'S') && checker(1, 1, 'U') && checker(2, 2, 'S')) {
        susFound = true;
    }

    // Check the diagonal 2
    if (x + y == this->rows - 1 && checker(0, 2, 'S') && checker(1, 1, 'U') && checker(2, 0, 'S')) {
        susFound = true;
    }

    return susFound;
}


template <typename T>
bool SUS_Board<T>::checker(int x, int y, char expected) {
    // Ensure the coordinates are within the board boundaries
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
        return this->board[x][y] == expected;
    }
    return false;
}

// Display the board
template <typename T>
void SUS_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == ' ') {
                cout << "(" << i << "," << j << ")";
            } else {
                cout << setw(3) << this->board[i][j];
            }
            cout << " | ";
        }
        cout << "\n-------------------------\n";
    }
}

// Unused condition
template <typename T>
bool SUS_Board<T>::is_win() {
    return false;
}

// Check if the game is a draw
template <typename T>
bool SUS_Board<T>::is_draw() {
    return this->n_moves == this->rows * this->columns; // Full board
}

// Check if the game is over
template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_draw();
}

// Display the final scores
template <typename T>
void SUS_Board<T>::display_scores() {
    cout << "\nFinal Scores:\n";
    cout << players[0]->getname() << ": " << counters[0] << " points\n";
    cout << players[1]->getname() << ": " << counters[1] << " points\n";

    if (counters[0] > counters[1]) {
        cout << "Winner: " << players[0]->getname() << " with " << counters[0] << " points!\n";
    } else if (counters[1] > counters[0]) {
        cout << "Winner: " << players[1]->getname() << " with " << counters[1] << " points!\n";
    } else {
        cout << "It's a draw!\n";
    }
}

// SUS_Player constructor
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Get the player's move
template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << this->getname() << ", enter your move (row and column): ";
    cin >> x >> y;
}

// SUS_Random_Player constructor
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(nullptr)));
}

// Get a random move
template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif //SUS_H