#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "ConnectFour.h"
#include "NumericalTicTacToe.h"
#include "SUS.h"


using namespace std;

int main() {
    int choice ;
    Player<int>* players[2];
    auto* board = new NumericalTicTacToe_Board<int>();
    string player1Name, player2Name;
    cout<<"_______________________________________________\n";
    cout << "  Welcome to Numerical Tic Tac Toe Game !\n";
    cout<<"_______________________________________________\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new NumericalTicTacToe_Player<int>(player1Name,0);
        break;
        case 2:
            players[0] = new NumericalTicTacToe_RandomPlayer<int>(1);
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1 ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player's type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;
    switch(choice) {
        case 1:
            players[1] = new NumericalTicTacToe_Player<int>(player2Name, 0);
        break;
        case 2:
            players[1] = new NumericalTicTacToe_RandomPlayer<int>(2);
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1 ;
    }
    // Create the game manager and run the game
    GameManager<int>NumericalTicTacToeGame(board, players);
    NumericalTicTacToeGame.run();

    // Clean up
    delete board;
    for (auto & player : players) {
        delete player;
    }

    return 0;

}








void mainG2() {
    int choice;
    Player<char>* players[2];
    auto* board = new ConnectFourBoard<char>();
    string playerXName, playerOName;
    cout<<"________________________________________\n";
    cout << "  Welcome to X-O Connect-Four Game !\n";
    cout<<"________________________________________\n";

    // Set up player 1
    cout << "Enter Symbol\'X\' Player's name: ";
    cin >> playerXName;
    cout << "Choose Symbol\'X\' Player's type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new ConnectFourPlayer<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new ConnectFourRandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return ; //1

    }

    // Set up player 2
    cout << "Enter Symbol\'O\' Player's name: ";
    cin >> playerOName;
    cout << "Choose Symbol\'O\' Player's type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new ConnectFourPlayer<char>(playerOName, 'O');
            break;
        case 2:
            players[1] = new ConnectFourRandomPlayer<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return ; //1
    }

    // Create the game manager and run the game
    GameManager<char>ConnectFourGame(board, players);
    ConnectFourGame.run();

    // Clean up
    delete board;
    for (auto & player : players) {
        delete player;
    }
    //return 0
}


void mainG9() {
    int choice;
    Player<char>* players[2];
    SUS_Board<char>* board = new SUS_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to the FCAI SUS Game!\n";

    // Player 1 setup
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    if (choice == 1) {
        players[0] = new SUS_Player<char>(player1Name, 'S');
    } else {
        players[0] = new SUS_Random_Player<char>('S');
    }

    // Player 2 setup
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    if (choice == 1) {
        players[1] = new SUS_Player<char>(player2Name, 'U');
    } else {
        players[1] = new SUS_Random_Player<char>('U');
    }

    board->setPlayers(players[0], players[1]);

    GameManager<char> gameManager(board, players);
    gameManager.run();

    board->display_scores();

    delete board;
    delete players[0];
    delete players[1];
}
