# Board Game Framework

A generic **board game framework** that demonstrates the power of Object-Oriented Programming (OOP) in enabling modularity and reusability. This framework allows developers to easily create new board games by extending its core functionality without modifying the existing code. 

## Features

- **Game Manager**: Manages the game flow, player turns, and determines the game outcome.
- **Abstract Player**: Represents a generic player, which can be extended to define game-specific player behaviors.
- **Abstract Board**: Defines the core structure of a game board with customizable rules.
- **Random Player**: Implements random move generation for any board game.

## Framework Overview

The framework supports easy development of multiple board games like Tic-Tac-Toe and its variants. It adheres to the **Open/Closed Principle**, enabling developers to extend the framework by creating new child classes for specific game rules and player behaviors.

### Key Framework Classes

1. **`GameManager`**  
   Manages the game logic, including board display, turn switching, and checking win/draw conditions.

2. **`Player`**  
   Represents a generic game player with attributes such as name, symbol, and ability to make moves.

3. **`Board`**  
   Abstract class defining the core board structure and rules, to be extended by specific game implementations.

4. **`RandomPlayer`**  
   A computer player that generates random moves adhering to game rules.

### Example Game Implementation

The framework includes a demo implementation of **Tic-Tac-Toe (X-O)**:
- **`X_O_Board`**: Implements a 3x3 grid and rules for X-O.
- **`X_O_Player`**: Represents a player for X-O.
- **`X_O_Random_Player`**: A random player for X-O.

## Games Developed Using the Framework

The framework has been extended to support the following games:

### 1. Pyramid Tic-Tac-Toe
- **Description**: Played on a pyramid-shaped board with rows of 5, 3, and 1 square.
- **Winning**: First player to get three in a row (horizontal, vertical, or diagonal) wins.

### 2. Four-in-a-Row
- **Description**: A 7x6 grid where players place their symbols from the bottom up.
- **Winning**: Achieve four in a row horizontally, vertically, or diagonally.

### 3. 5x5 Tic-Tac-Toe
- **Description**: Played on a 5x5 grid with up to 12 turns per player.
- **Winning**: Count the most three-in-a-row sequences.

### 4. Word Tic-Tac-Toe
- **Description**: Players place letters on a 3x3 grid to form valid words.
- **Winning**: Form a valid word (from `dic.txt`) horizontally, vertically, or diagonally.

### 5. Numerical Tic-Tac-Toe
- **Description**: Players use numbers (odd/even) to sum to 15 in a row, column, or diagonal.
- **Winning**: Form a sum of 15 in a line.

### 6. Misere Tic-Tac-Toe
- **Description**: Players aim to avoid forming three in a row.
- **Losing**: Player who forms three in a row loses.

### 7. 4x4 Tic-Tac-Toe
- **Description**: Players move tokens on a 4x4 grid aiming to align three tokens.
- **Winning**: Align three tokens horizontally, vertically, or diagonally.

### 8. Ultimate Tic-Tac-Toe
- **Description**: A meta-game where smaller Tic-Tac-Toe boards make up a larger 3x3 grid.
- **Winning**: Win three smaller boards in a row on the larger grid.

### 9. SUS Game
- **Description**: Form the sequence "S-U-S" on a 3x3 grid.
- **Winning**: Create the most "S-U-S" sequences.

## How to Use the Framework

1. **Clone the Repository**:  
   ```bash
   git clone https://github.com/Malaknourr/BoardGames
   cd board-game-framework
