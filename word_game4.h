#ifndef WORD_GAME4_H
#define WORD_GAME4_H

#include "BoardGame_Classes.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Class representing a Word Board
// Derived from Board<T>
template <typename T>
class word_Board: public Board<T> {
public:
    word_Board(); // Constructor to initialize the board
    bool update_board(int x, int y, T symbol); // Update the board after each turn
    void display_board(); // Display the current state of the board
    bool is_win(); // Check for a winning condition
    bool is_draw(); // Check if the game ended in a draw
    bool game_is_over(); // Check if the game is over
};

// Class representing a Player for Word Game
// Derived from Player<T>
template <typename T>
class word_Player : public Player<T> {
public:
    word_Player(string name, T symbol); // Constructor to initialize player with name and symbol
    void getmove(int& x, int& y); // Prompt the player for their move
};

// Class representing a Random Player for Word Game
// Derived from RandomPlayer<T>
template <typename T>
class word_Random_Player : public RandomPlayer<T> {
public:
    explicit word_Random_Player(T symbol); // Constructor to initialize with a symbol
    void getmove(int &x, int &y); // Generate a random move
};

//--------------------------------------- IMPLEMENTATION

// Constructor for word_Board
// Initializes the board with 3 rows and 3 columns
template <typename T>
word_Board<T>::word_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Update the board with a player's move
template <typename T>
bool word_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0; // Reset the cell
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark); // Update the cell with the player's mark
        }
        return true;
    }
    return false;
}

// Display the board with formatting
template <typename T>
void word_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Check if there is a winner
template <typename T>
bool word_Board<T>::is_win() {
    ifstream file("dic.txt");
    if (!file) {
        cerr << "Error: Could not open dictionary file.\n";
        return false;
    }

    // Read dictionary words
    vector<string> dictionary;
    string word;
    while (getline(file, word)) {
        dictionary.push_back(word);
    }
    file.close();

    // Check rows, columns, and diagonals
    for (int i = 0; i < this->rows; i++) {
        string row = "", column = "";
        for (int j = 0; j < this->columns; j++) {
            row += toupper(this->board[i][j]);
            column += toupper(this->board[j][i]);
        }

        string rev_row = row;
        reverse(rev_row.begin(), rev_row.end());
        string rev_column = column;
        reverse(rev_column.begin(), rev_column.end());

        for (const auto& dict_word : dictionary) {
            if (row == dict_word || column == dict_word || rev_row == dict_word || rev_column == dict_word) {
                return true;
            }
        }
    }

    string diag1 = "", diag2 = "";
    for (int i = 0; i < this->rows; i++) {
        diag1 += toupper(this->board[i][i]);
        diag2 += toupper(this->board[i][this->columns - i - 1]);
    }

    string rev_diag1 = diag1;
    reverse(rev_diag1.begin(), rev_diag1.end());
    string rev_diag2 = diag2;
    reverse(rev_diag2.begin(), rev_diag2.end());

    for (const auto& dict_word : dictionary) {
        if (diag1 == dict_word || diag2 == dict_word || rev_diag1 == dict_word || rev_diag2 == dict_word) {
            return true;
        }
    }

    return false;
}

// Check if the game ended in a draw
template <typename T>
bool word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template <typename T>
bool word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for word_Player
template <typename T>
word_Player<T>::word_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Prompt the player for their move
template <typename T>
void word_Player<T>::getmove(int& x, int& y) {
    char ch;
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "\nPlease enter your letter: ";
    cin >> ch;
    ch = toupper(ch);
    this->symbol = ch;
}

// Constructor for word_Random_Player
template <typename T>
word_Random_Player<T>::word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

// Generate a random move
template <typename T>
void word_Random_Player<T>::getmove(int& x, int& y) {
    char ch;
    x = rand() % this->dimension; // Random number between 0 and 2
    y = rand() % this->dimension;
    ch = 'A' + rand() % 26; // Random uppercase character between 'A' and 'Z'
    this->symbol = ch;
}

#endif // WORD_GAME4_H
