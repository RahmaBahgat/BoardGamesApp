#ifndef word_game4_H
#define word_game4_H


#include "BoardGame_Classes.h"
#include <fstream>
#include <algorithm>
template <typename T>
class word_Board:public Board<T> {
public:
    word_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class word_Player : public Player<T> {
public:
    word_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};
template <typename T>
class word_Random_Player : public RandomPlayer<T>{
public:
    explicit word_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;
// Constructor for X_O_Board
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

template <typename T>
bool word_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}


// Display the board and the pieces on it
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
        // Construct row and column strings
        string row = "";
        string column = "";
        for (int j = 0; j < this->columns; j++) {
            row += toupper(this->board[i][j]);
            column += toupper(this->board[j][i]);
        }


        string rev_row = row;
        reverse(rev_row.begin(), rev_row.end());
        string rev_column = column;
        reverse(rev_column.begin(), rev_column.end());
        // Check if any row or column matches a word in the dictionary
        for (const auto& dict_word : dictionary) {
            if (row == dict_word || column == dict_word || rev_column == dict_word || rev_row == dict_word) {
                return true;
            }
        }
    }

    // Check diagonals
    string diag1 = "";
    string diag2 = "";
    for (int i = 0; i < this->rows; i++) {
        diag1 += toupper(this->board[i][i]);
        diag2 += toupper(this->board[i][this->columns - i - 1]);
    }

    string rev_diag1 = diag1;
    reverse(rev_diag1.begin(), rev_diag1.end());
    string rev_diag2 = diag2;
    reverse(rev_diag2.begin(), rev_diag2.end());
    // Check if any diagonal matches a word in the dictionary
    for (const auto& dict_word : dictionary) {
        if (diag1 == dict_word || diag2 == dict_word || rev_diag1 == dict_word || rev_diag2 == dict_word) {
            return true;
        }
    }

    return false; // No matches found
}

// Return true if 9 moves are done and no winner
template <typename T>
bool word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for X_O_Player
template <typename T>
word_Player<T>::word_Player(string name, T symbol) : Player<T>(name, symbol) {}

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

template <typename T>
word_Random_Player<T>::word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void word_Random_Player<T>::getmove(int& x, int& y) {
    char ch;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    ch = 'A' + rand() % 26;// Random uppercase character between 'A' and 'Z'
    this->symbol = ch;
}
#endif //word_game4_H