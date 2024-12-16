#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <string>
using namespace std;
/*
rows: the number of rows in the board
columns: the number of columns in the board
board: a 2D array to store the board state
n_moves: the number of moves made on the board
 */

template <typename T>
class Board {//an abstract base class that defines the interface for a board game board
protected:
    int rows, columns;
    T** board; //dynamic allocation (**)
    int n_moves = 0; //Useful for win/draw logic.

public:

    //pure virtual methods:
    /// Return true if move is valid and put it on the board
    /// within board boundaries in an empty cell
    /// Return false otherwise
    virtual bool update_board(int x, int y, T symbol) = 0;

    /// Display the board and the pieces on it
    virtual void display_board() = 0;

    /// Returns true if there is any winner
    virtual bool is_win() = 0;

    /// Return true if all moves are done and no winner
    virtual bool is_draw() = 0;

    /// Return true if the game is over
    virtual bool game_is_over() = 0;
};

/*
name: the name of the player
symbol: the symbol used by the player on the board
boardPtr: a pointer to the board object (why?)
 */
template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr; //a pointer to the Board object
/*Points to the associated board object , Why pointers?
Allows players to interact with any board without copying it
Flexibility for games with different board implementations
*/
public:
    virtual ~Player() = default;

    /// Two constructors to initiate players
    /// Give the player a symbol to use in playing
    /// It can be X, O, or others
    /// Optionally, you can give them a name
    Player(string n, T symbol);
    Player(T symbol); // For computer players

    virtual void getmove(int& x, int& y) = 0; //by reference : Enables the method to update x and y directly without returning them.

    T getsymbol();
    string getname();
    void setBoard(Board<T>* b); //Links the player to a board.
};

/// This class represents a random computer player
/// that generates random positions x, y
/// If invalid, the game manager asks to regenerate
template <typename T>
class RandomPlayer : public Player<T> {
protected:
    int dimension; //the size of the board
public:
    // Take a symbol and pass it to the parent
    RandomPlayer(T symbol);
    // Generate a random move
    virtual void getmove(int& x, int& y) = 0;//(why by reference ?)Enables the method to update x and y directly without returning them.
};

template <typename T>
class GameManager {
    Board<T>* boardPtr; // Links the manager to a board.
    Player<T>* players[2]; //Array of two player pointers.->Flexibility for any Player implementation.
public:
    GameManager(Board<T>*, Player<T>* playerPtr[2]);

    void run();
};


//--------------------------------------- IMPLEMENTATION
template <typename T>
GameManager<T>::GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

template <typename T>
void GameManager<T>::run() {
    ///the main game loop that alternates between the two players, updates the board,and checks for a winner or a draw.
    int x, y;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i : {0, 1}) { //i only = 0 or 1 corresponding to the 2 players
            players[i]->getmove(x, y);
            while (!boardPtr->update_board(x, y, players[i]->getsymbol())) {
                players[i]->getmove(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_win()) {
                cout << players[i]->getname() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}


// Constructor for Player with a name and symbol
template <typename T>
Player<T>::Player(std::string n, T symbol) {
    this->name = n;
    this->symbol = symbol;
}

// Constructor for Player with only a symbol (e.g., for computer players)
template <typename T>
Player<T>::Player(T symbol) {
    this->name = "Computer";
    this->symbol = symbol;
}

// Constructor for RandomPlayer, passing the symbol to the parent Player class
template <typename T>
RandomPlayer<T>::RandomPlayer(T symbol) : Player<T>(symbol) {}

// Getter for player's name
template <typename T>
std::string Player<T>::getname() {
    return this->name;
}

// Getter for player's symbol
template <typename T>
T Player<T>::getsymbol() {
    return this->symbol;
}

// Method to set the board pointer in the Player class
template <typename T>
void Player<T>::setBoard(Board<T>* b) {
    this->boardPtr = b;
}


#endif //_BOARDGAME_CLASSES_H

