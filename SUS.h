#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

template <typename T>
class SUS_Board : public Board<T> {
private:
    Player<T>* players[2];
    int counters[2] = {0, 0}; // Player scores

public:
    SUS_Board();
    void setPlayers(Player<T>* player1, Player<T>* player2);
    bool update_board(int x, int y, T mark);
    void display_board();
    bool is_win(); // Always false, as winning is score-based
    bool is_draw();
    bool game_is_over();
    void display_scores();

private:
    bool completes_SUS(int x, int y, T mark); // New helper function to check if SUS is formed
    bool check_sequence(int x, int y, char expected); // Helper function to validate cell contents
};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
    SUS_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // Initialize board cells to 0
        }
    }
    this->n_moves = 0;
}

template <typename T>
void SUS_Board<T>::setPlayers(Player<T>* player1, Player<T>* player2) {
    players[0] = player1;
    players[1] = player2;
}

template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->n_moves++;
        this->board[x][y] = toupper(mark);

        int playerIndex = (mark == players[0]->getsymbol()) ? 0 : 1;

        // *** Check if this move completes a "SUS" and update the player's score ***
        if (completes_SUS(x, y, mark)) {
            counters[playerIndex]++;
        }

        return true;
    }
    return false;
}

template <typename T>
bool SUS_Board<T>::completes_SUS(int x, int y, T mark) {
    // Directions for checking row, column, diagonal, and anti-diagonal
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (auto& dir : directions) {
        int dx = dir[0], dy = dir[1];
        // Check if placing the mark completes "SUS"
        if (check_sequence(x - dx, y - dy, 'S') &&
            check_sequence(x, y, 'U') &&
            check_sequence(x + dx, y + dy, 'S')) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool SUS_Board<T>::check_sequence(int x, int y, char expected) {
    return x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == expected;
}

template <typename T>
void SUS_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) {
                // Display coordinates for empty cells, (i, j) for 0-indexed coordinates
                cout << "(" << i << "," << j << ")";
            } else {
                // Display the symbol for non-empty cells
                cout << setw(3) << this->board[i][j];
            }
            cout << " | ";
        }
        cout << "\n-------------------------\n";
    }
}




template <typename T>
bool SUS_Board<T>::is_win() {
    return false; // Winning is determined by score comparison
}

template <typename T>
bool SUS_Board<T>::is_draw() {
    return this->n_moves == this->rows * this->columns; // Game ends when board is full
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_draw();
}

template <typename T>
void SUS_Board<T>::display_scores() {
    cout << "\nGame Over! Final Scores:\n";
    cout << players[0]->getname() << ": " << counters[0] << " points\n";
    cout << players[1]->getname() << ": " << counters[1] << " points\n";

    if (counters[0] > counters[1]) {
        cout << "Winner: " << players[0]->getname() << "!\n";
    } else if (counters[1] > counters[0]) {
        cout << "Winner: " << players[1]->getname() << "!\n";
    } else {
        cout << "It's a draw!\n";
    }
}

template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << this->getname() << ", enter your move (row and column): ";
    cin >> x >> y;
}

template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(nullptr)));
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif //SUS_H
