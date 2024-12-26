#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "X_O_pyramid.h"
#include "ConnectFour.h"
#include "5x5TicTacToe.h"
#include "MisereTicTacToe.h"
#include "NumericalTicTacToe.h"
#include "SUS.h"
#include "UltimateTicTacToeVer2.h"
#include "word_game4.h"
#include "Game7.h"
using namespace std;

// Function prototypes for the games
void mainG1();  // Pyramid Tic-Tac-Toe
void mainG2();  // Four-in-a-row
void mainG3();  // 5x5 Tic Tac Toe
void mainG4();  // Word Tic-Tac-Toe
void mainG5();  // Numerical Tic-Tac-Toe
void mainG6();  // Misère Tic Tac Toe
void mainG7();  // Tic-Tac-Toe
void mainG8();  // Ultimate Tic Tac Toe
void mainG9();  // SUS

// Function to display game brief
void showGameBrief(int choice) {
    switch (choice) {
        case 1:
            cout << "1- Pyramid Tic-Tac-Toe\n";
            cout << "The board is shaped like a pyramid. Get three-in-a-row vertically, horizontally, or diagonally to win.\n";
            mainG1();
            break;
        case 2:
            cout << "2- Four-in-a-row\n";
            cout << "Played on a 7x6 grid. Place Xs or Os at the lowest possible spot in a column. Get four-in-a-row to win.\n";
            mainG2();
            break;
        case 3:
            cout << "3- 5x5 Tic Tac Toe\n";
            cout << "Played on a 5x5 grid. Count the most three-in-a-rows to win.\n";
            mainG3();
            break;
        case 4:
            cout << "4- Word Tic-Tac-Toe\n";
            cout << "Form valid words with letters on a 3x3 grid. First to form a word wins.\n";
            mainG4();
            break;
        case 5:
            cout << "5- Numerical Tic-Tac-Toe\n";
            cout << "Place numbers (From 1 to 9) on a 3x3 grid to achieve a sum of 15 in a row, column, or diagonal.\n First Player -> Odd Numbers.\n Second Player -> Even Numbers.\n";
            mainG5();
            break;
        case 6:
            cout << "6- Misere Tic Tac Toe\n";
            cout << "Avoid getting three-in-a-row on a 3x3 grid. The first to do so loses.\n";
            mainG6();
            break;
        case 7:
            cout << "7- Tic-Tac-Toe\n";
            cout << "4x4 Tic-Tac-Toe is played on a 4x4 grid where players move tokens to align three in a row, horizontally, vertically, or diagonally,to win.\n" ;
            mainG7();
            break;
        case 8:
            cout << "8- Ultimate Tic Tac Toe\n";
            cout << "Win three smaller Tic Tac Toe games in a row to win on the main 3x3 grid.\n";
            mainG8();
            break;
        case 9:
            cout << "9- SUS\n";
            cout << "Create the sequence 'S-U-S' on a 3x3 grid as many times as possible. The most points win.\n";
            mainG9();
            break;
        default:
            cout << "Invalid choice. This should not occur.\n";
    }
}

// Function to validate and retrieve user input
int getValidChoice() {
    int choice;
    while (true) {
        cout << "Enter your choice (between 1 to 8, 0 to EXIT): ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear(); // Clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        }
        else if (choice >= 0 && choice <= 9) {
            return choice;  // Valid input
        }
        else {
            cout << "Invalid choice. Please select a valid game number.\n";
        }
    }
}

int main() {
    cout<< "__________________________________________________________________________\n";
    cout << "                WELCOME TO OUR BOARD GAMES PROGRAM                       \n";
    cout<< "__________________________________________________________________________\n";

    while (true) {
        cout << "\nHere is the list of games:\n";
        cout << "1- Pyramid Tic-Tac-Toe\n";
        cout << "2- Four-in-a-row\n";
        cout << "3- 5x5 Tic Tac Toe\n";
        cout << "4- Word Tic-Tac-Toe\n";
        cout << "5- Numerical Tic-Tac-Toe\n";
        cout << "6- Misere Tic Tac Toe\n";
        cout << "7- Tic Tac Toe\n";
        cout << "8- Ultimate Tic Tac Toe\n";
        cout << "9- SUS\n";

        // Get the user's choice
        int choice = getValidChoice();

        if (choice == 0) {
            cout << "Thank you for playing! Goodbye!\n";
            break;
        }

        // Display brief and call the corresponding game
        showGameBrief(choice);
        cout << "\n--------------------------------------------\n";
    }

    return 0;
}



//Game 1 : Made by Basmala
void mainG1() {
    int choice;
    Player<char>* players[2] = {nullptr, nullptr};
    auto* board = new pyramid_X_O_Board<char>();
    string player1Name, player2Name;
    cout << "\n\nWelcome to Pyramid Tic-Tac-Toe :)\n";

    // Set up Player 1
    do {
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            players[0] = new pyramid_X_O_Player<char>(player1Name, 'X');
        } else if (choice == 2) {
            players[0] = new pyramid_X_O_Random_Player<char>('X');
        } else {
            cout << "Invalid choice for Player 1. Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);

    // Set up Player 2
    do {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Player 2 name: ";
            cin >> player1Name;
            players[1] = new pyramid_X_O_Player<char>(player1Name, 'O');
        } else if (choice == 2) {
            players[1] = new pyramid_X_O_Random_Player<char>('O');
        } else {
            cout << "Invalid choice for Player 2. Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);

    cout << "\nGame setup complete. Ready to play!\n";
    // Create the game manager and run the game
    GameManager<char> x_o_game(board, players);
    x_o_game.run();

    // Clean up memory
    delete players[0];
    delete players[1];
    delete board;
}

//Game 2 : Made by MALAK NOUR
void mainG2() {
    int choice;
    Player<char>* players[2];
    auto* board = new ConnectFourBoard<char>();
    string playerXName, playerOName;

    cout << "\nWelcome to X-O Connect-Four Game!\n";

    // Set up player 1 (Symbol 'X')
    do {
        cout << "Choose Symbol 'X' Player's type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Symbol 'X' Player's name:";
            cin >> playerXName;
            players[0] = new ConnectFourPlayer<char>(playerXName, 'X');
        } else if (choice == 2) {
            players[0] = new ConnectFourRandomPlayer<char>('X');
        } else {
            cout << "Invalid Choice! Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);

    // Set up player 2 (Symbol 'O')
    do {
        cout << "Choose Symbol 'O' Player's type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Symbol 'O' Player's name:";
            cin >> playerOName;
            players[1] = new ConnectFourPlayer<char>(playerOName, 'O');
        } else if (choice == 2) {
            players[1] = new ConnectFourRandomPlayer<char>('O');
        } else {
            cout << "Invalid Choice! Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);

    // Create the game manager and run the game
    GameManager<char>ConnectFourGame(board, players);
    ConnectFourGame.run();

    // Clean up dynamically allocated resources
    delete board;
    for (auto& player : players) {
        delete player;
    }
}



//Game 3 : Made by Rahma
void mainG3(){
    int choice;
    Player<char>* players[2];
    fiveByFiveTicTacToeBoard<char>* B = new fiveByFiveTicTacToeBoard<char>(); // Create a 5x5 board
    string playerXName, playerOName;

    cout << "Welcome to 5x5 Tic Tac Toe Game. :)\n";

    // Set up Player X
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new TicTacToePlayer<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new TicTacToeRandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player X. Exiting the game.\n";
            return ;
    }

    // Set up Player O
    cout << "Enter Player O name: ";
    cin >> playerOName;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new TicTacToePlayer<char>(playerOName, 'O');
            break;
        case 2:
            players[1] = new TicTacToeRandomPlayer<char>('O');
            break;
        default:
            cout << "Invalid choice for Player O. Exiting the game.\n";
            return ;
    }

    // Set the board pointer for players
    players[0]->setBoard(B);
    players[1]->setBoard(B);

    // Create the game manager and run the game
    GameManager5x5<char> ttt_game(B, players);
    ttt_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return ;
}

//Game 4 : Made by Basmala
void mainG4(){
    int choice;
    Player<char>* players[2] = {nullptr, nullptr};
    auto* board = new word_Board<char>();
    string player1Name, player2Name;

    cout << "\nWelcome to Word Tic-Tac-Toe :)\n";

    // Set up Player 1
    do {
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            players[0] = new word_Player<char>(player1Name, 'X');
        } else if (choice == 2) {
            players[0] = new word_Random_Player<char>('O');
        } else {
            cout << "Invalid choice for Player 1. Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);


    // Set up Player 2
    do {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Player 2 name: ";
            cin >> player1Name;
            players[1] = new word_Player<char>(player1Name, 'O');
        } else if (choice == 2) {
            players[1] = new word_Random_Player<char>('O');
        } else {
            cout << "Invalid choice for Player 2. Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);
    // Game logic here (if applicable)
    cout << "Game setup complete. Ready to play!\n";
    // Create the game manager and run the game
    GameManager<char> x_o_game(board, players);
    x_o_game.run();

    // Clean up memory
    delete players[0];
    delete players[1];
    delete board;
}
//Game 5 : Made by MALAK NOUR
void mainG5() {
    int choice;
    Player<int>* players[2];
    auto* board = new NumericalTicTacToe_Board<int>();
    string player1Name, player2Name;

    cout << "\nWelcome to Numerical Tic Tac Toe Game!\n";

    // Set up Player 1
    do {
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            players[0] = new NumericalTicTacToe_Player<int>(player1Name, 0);
        } else if (choice == 2) {
            players[0] = new NumericalTicTacToe_RandomPlayer<int>(-1);
        } else {
            cout << "Invalid choice for Player 1. Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);

    // Set up Player 2
    do {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            players[1] = new NumericalTicTacToe_Player<int>(player2Name, 0);
        } else if (choice == 2) {
            players[1] = new NumericalTicTacToe_RandomPlayer<int>(-2);
        } else {
            cout << "Invalid choice for Player 2. Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);

    // Create the game manager and run the game
    GameManager<int> NumericalTicTacToeGame(board, players);
    NumericalTicTacToeGame.run();


    delete board;
    for (auto& player : players) {
        delete player;
    }
}

// // Game 6 : Made by Rahma

void mainG6(){
    int choice;
    Player<char>* players[2];
    Misere_Board<char>* B = new Misere_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Misere Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Misere_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Misere_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Misere_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Misere_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return ;
    }

    // Create the Misere game manager and run the game
    MisereGameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    return ;
}

//Game 7 & 8 & 9 : Made by the 3 of us : Malak , Basmala , Rahma
void mainG7() {
    int choice;
    Player<char>* players[2] = {nullptr, nullptr};
    auto* board = new TicTacToe4x4_Board<char>(); // Instantiate the multi-board implementation

    string playerXName, playerOName;
    cout << "Welcome to Tic-Tac-Toe :)\n";

    // Set up Player X
    do {
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Player X name: ";
            cin >> playerXName;
            players[0] = new TicTacToe4x4_Player<char>(playerXName, 'X');
        } else if (choice == 2) {
            players[0] = new TicTacToe4x4_RandomPlayer<char>('1');
        } else {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);

    // Set up Player O
    do {
        cout << "Choose Player O type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Player O name: ";
            cin >> playerOName;
            players[1] = new TicTacToe4x4_Player<char>(playerOName, 'O');
        } else if (choice == 2) {
            players[1] = new TicTacToe4x4_RandomPlayer<char>('2');
        } else {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);

    // Create the game manager and run the game
    GameManager<char> Game7(board, players);
    Game7.run();

    // Clean up dynamically allocated resources
    delete players[0];
    delete players[1];
    delete board;
}



void mainG8() {
    int choice;
    Player<char>* players[2] = {nullptr, nullptr};
    auto* board = new X_O_Board(); // Instantiate the multi-board implementation
    string playerXName, playerOName;
    cout << "\nWelcome to Ultimate Tic-Tac-Toe :)\n";
    // Set up Player X
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new X_O_Player(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player('X');
            break;
        default:
            cout << "Invalid choice. Defaulting to Human Player.\n";
            players[0] = new X_O_Player(playerXName, 'X');
            break;
    }

    // Set up Player O
    cout << "Enter Player O name: ";
    cin >> playerOName;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new X_O_Player(playerOName, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player('O');
            break;
        default:
            cout << "Invalid choice. Defaulting to Human Player.\n";
            players[1] = new X_O_Player(playerOName, 'O');
            break;
    }

    // Assign the board to both players
    players[0]->setBoard(board);
    players[1]->setBoard(board);

    // Create the game manager and run the game
    GameManager<char> x_o_game(board, players);
    x_o_game.run();

    // Clean up memory
    delete players[0];
    delete players[1];
    delete board;

}

void mainG9() {
    int choice;
    Player<char>* players[2];
    SUS_Board<char>* board = new SUS_Board<char>();
    string player1Name, player2Name;

    cout << "\nWelcome to the FCAI SUS Game!\n";

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
