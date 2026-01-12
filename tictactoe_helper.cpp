/*
 * File: tictactoe_helper.cpp
 * Author: Christopher Lin
 * Date: 2026-01-04
 *
 * GitHub: https://github.com/titancoder12/CS12-TicTacToe
 *
 * Description:
 * This file defines the functions declared in 'tictactoe_helper.h'.
 * Notes:
 * Comments in this file are implementation level.
 * More details regarding the purpose and use of each function can be found in 'tictactoe_helper.h'.
 */

#include "tictactoe_helper.h"
#include <map>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <iostream>

// Define colors
const string RED = "\033[41m";
const string GREEN = "\033[42m";
const string RESET = "\033[0m";

// Define extern consts
const int SIZE = 3;
const char X = 'X';
const char O = 'O';

// Runs the game loop
void run_game(char human, char AI, vector<vector<char> > board, char difficulty) {
    // Run game loop until one player wins
    char turn = 'X';
    string message = "";
    while (true) {
        cout << "\033[2J\033[1;1H" << flush;
        // Check if game has ended
        if (terminal(board)) {
            char winner_ = winner(board);
            
            // Check for winner or tie
            if (winner_ != ' ') {
                // Check if human won
                if (winner_ == human){
                    cout << GREEN << "YOU WON!" << RESET << endl;
                }
                // Otherwise, AI won and human lost
                else {
                    cout << RED << "YOU LOST!" << RESET << endl;
                }
                cout << "------------------" << endl << endl;
                render_board(board);
                break;
            }
            // Must be a tie
            else {
                cout << GREEN << "TIE!"<< RESET << endl;
                cout << "------------------" << endl << endl;
                render_board(board);
                break;
            }
        }
        
        // Margin
        cout << endl;
        
        // Determine if it is the human or AI's turn
        if (turn == human) {
            pair<int, int> coordinates;
            
            // Keep looping until valid value
            while (true) {
                // Flush previous input
                cout << "\033[2J\033[1;1H" << flush;
                
                // Indicate who human is playing as. Also include message if needed (for invalid inputs).
                cout << "PLAYING AS " << human << " " << message << endl;
                cout << "------------------" << endl << endl;
                
                message = "";
                
                // Render the board
                render_board(board);
                
                // Prompt user for coordinates
                cout << endl << "Enter coordinates of move (row, col): ";
                string input;
                getline(cin, input);
                cout << '\r';
                
                // Parse coordinates from string to pair<int,int>
                // Also catch errors (invalid formatting) and indicate that
                try {
                    coordinates = parse_input(input);
                }
                catch (const invalid_argument&) {
                    message = RED + "[Action is invalid]" + RESET;
                    continue;
                }
                catch (const out_of_range&) {
                    message = RED + "[Action is invalid]" + RESET;
                    continue;
                }
                
                // Define sentinel value (value that signifies )
                pair<int, int> sentinel {-1, -1};
                
                if (coordinates == sentinel) {
                    message = RED + "[Action is invalid]" + RESET;
                    continue;
                }
                
                // Using a set allows for faster, easier lookups
                set<pair<int, int> > possible_actions = actions(board);
                
                // Check to see if action taken is within possible action space
                if (possible_actions.count(coordinates)) {
                    break;
                }
                
                message = RED + "[Action is invalid]" + RESET;
            }
            
            // Update board and hand the turn over to the AI
            update(board, coordinates, human);
            turn = AI;
        }
        // AI's turn
        else if (turn == AI) {
            // Different levels have different probabilities of making the optimal/random move.
            
            // Generate random number
            int probability = rand() % 100;
            
            pair<int, int> coordinates;
            
            // Easy difficulty, 50% chance of a random move, 50% chance of an optimal move.
            if (difficulty == 'E') {
                if (probability < 50) {
                    coordinates = random_move(board);
                }
                else {
                    coordinates = minimax(board, AI);
                }
            }
            // Normal difficulty, 20% chance of a random move, 80% chance of an optimal move.
            else if (difficulty == 'N') {
                if (probability < 35) {
                    coordinates = random_move(board);
                }
                else {
                    coordinates = minimax(board, AI);
                }
            }
            // Impossible difficulty, 0% chance of a random move, 100% chance of an optimal move!
            else {
                // Run minimax to determine optimal move
                coordinates = minimax(board, AI);
            }
            
            // Update board and hand over turn to the human
            update(board, coordinates, AI);
            turn = human;
        }
    }
}

// Prompts the human if they want to play as X or O
pair<char, char> choose_player() {
    char human;
    char AI;
    
    // Let user choose player
    while (true) {
        cout << "Choose your player (X or O): ";
        string input;
        getline(cin, input);
        
        // Handle both upper and lower case values
        if (input == "X" || input == "x") {
            cout << "Playing as X." << endl;
            // Assign respective variables
            human = X;
            AI = O;
            break;
        }
        else if (input == "O" || input == "o") {
            cout << "Playing as O." << endl;
            // Assign respective variables
            human = O;
            AI = X;
            break;
        }
        else {
            cout << "Invalid input." << endl << endl;
        }
    }
    
    pair<char, char> return_data {human, AI};
    
    return return_data;
}

// Parses input from string to coordinate pair (x, y)
pair<int, int> parse_input(string input) {
    // Check for open parenthesis
    int open = input.find('(');
    if (open != string::npos) {
        // Erase it
        input.erase(open, 1);
    }
    
    // Check for close parenthesis
    int close = input.find(')');
    if (close != string::npos) {
        // Erase it
        input.erase(close, 1);
    }
    
    // If no comma is found, the input is invalid
    int comma = input.find(',');
    if (comma == string::npos) {
        // Return a sentinel value
        return {-1, -1};
    }
    
    // Get numbers
    int row = stoi(input.substr(0, comma));
    int col = stoi(input.substr(comma+1));
    
    // Return numbers as a pair<int, int>
    pair<int, int> coordinates = {row, col};
    return coordinates;
}

// Render the board in the terminal.
void render_board(vector<vector<char> > board) {
    // Margin
    cout << "  ";
    
    // Grid indicators (rows)
    for (int i = 0; i < board.size(); i++) {
        cout << i << "  ";
    }
    cout << endl;
    
    for (int i = 0; i < board.size(); i++) {
        // Grid indicator (cols)
        cout << i << " ";
        
        // Print each coordinate
        for (int j = 0; j < board.size(); j++) {
            int pos = board[i][j];
            if (pos == ' ') {
                cout << ".";
            }
            else if (pos == X) {
                cout << "X";
            }
            else if(pos == O) {
                cout << "O";
            }
            cout << "  ";
        }
        
        cout << endl;
    }
}

// Create an empty board (starting state).
vector<vector<char> > empty_board() {
    // Define the 2D vector being used
    vector<vector<char> > board;
    
    // Iterate SIZE rows
    for (int i = 0; i < SIZE; i++) {
        // Define the temporary row
        vector<char> row;
        
        // Iterate SIZE cols
        for (int j = 0; j < SIZE; j++) {
            // Push back blank value to row
            row.push_back(' ');
        }
        
        // Add the temporary row to the 2D vector
        board.push_back(row);
    }
    
    // Return the 2D vector
    return board;
}

// Return true if the game is over, false otherwise.
bool terminal(vector<vector<char> > &board) {
    // Check if winner returns a value.
    if (utility(board) == 1 || utility(board) == -1) {
        return true;
    }
    
    // Check if the grid is full.
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    
    return true;
}

// Return current player
char player(vector<vector<char> > board) {
    // Keep track of how many Xs and Os
    int X_count = 0;
    int O_count = 0;
    
    // Add to respective count each time X/O is found
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == X) {
                X_count++;
            }
            else if (board[i][j] == O) {
                O_count++;
            }
        }
    }
    
    // Return player based on count
    if (X_count == O_count) {
        return X;
    }
    else if (X_count < O_count) {
        return X;
    }
    else if (X_count > O_count) {
        return O;
    }
    
    // Sentinel value, some sort of error must have happened.
    return '?';
}

// Returns if X has won the game, O has won, or otherwise.
char winner(vector<vector<char> > &board) {
    
    for (int i = 0; i < board.size(); i++) {
        // Check rows
        if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && board[i][0] != ' ') {
            return board[i][0];
        }
        
        // Check columns
        if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    
    // Check diagonals (left to right, right to left)
    if ((((board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) || ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))) && board[1][1] != ' ') {
        return board[1][1];
    }
    
    // If satisfied none, must be otherwise (return setinel value)
    return ' ';
}

// Returns 1 if X wins, -1 if O wins, or 0 if tied.
int utility(vector<vector<char> > board) {
    if (winner(board) == X) {
        return 1;
    }
    else if (winner(board) == O) {
        return -1;
    }
    else {
        return 0;
    }
}

// Return set of all possible actions (i, j) available on the board.
set<pair<int, int> > actions(vector<vector<char> > &board) {
    // Add to vector available each time an empty coordinate is found
    set<pair<int, int> > available;
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == ' ') {
                pair<int, int> location = {i, j};
                available.insert(location);
            }
        }
    }
    
    return available;
}

// Updates board with move (i, j).
void update(vector<vector<char> > &board, pair<int, int> location, char team) {
    board[location.first][location.second] = team;
    return;
}

// Returns board as a result of move (i, j)
vector<vector<char> > result(vector<vector<char> > board, pair<int, int> location) {
    board[location.first][location.second] = player(board);
    return board;
}

// Returns a random move
pair<int, int> random_move(vector<vector<char> > &board) {
    // Get all available actions
    set<pair<int, int> > available_actions_set = actions(board);
    vector<pair<int,int> > available_actions(available_actions_set.begin(), available_actions_set.end());
    
    // Pick a random index
    int random_index = rand() % (available_actions.size());
    
    // Return move at random index
    return available_actions[random_index];
}

// Return lowest possible utility (score) given that both players play optimally.
// This function represents player O trying to minimize score.
int min_value(vector<vector<char> > board) {
    // Base case
    if (terminal(board)) {
        // Return 
        return utility(board);
    }
    
    // Infintely large (1000 is an impossible value)
    int v = 1000;
    
    // Mutual recursive backtracking with max_value
    // Try out each action, return the minimum out of the other player's maximums
    for (pair<int, int> action : actions(board)) {
        v = min(v, max_value(result(board, action)));
    }
    return v;
}

// Return highest possible utility (score) given that both players play optimally. (Opposite of min_value)
// This function represents player X trying to maximize score.
int max_value(vector<vector<char> > board) {
    // Base case
    if (terminal(board)) {
        return utility(board);
    }
    
    // Infintely small (-1000 is an impossible value)
    int v = -1000;
    
    // Mutual recursive backtracking with min_value
    // Try out each action, return the maximum out of the other player's minimums
    for (pair<int, int> action : actions(board)) {
        v = max(v, min_value(result(board, action)));
    }
    
    return v;
}

// Returns optimal move
pair<int, int> minimax(vector<vector<char> > board, char AI) {
    // Set inital values and define variables
    pair<int, int> optimalX;
    pair<int, int> optimalO;
    
    // Infintely small (-1000 is an impossible value) so that first value will always be greater.
    int optimalX_util = -1000;
    
    // Infintely large (1000 is an impossible value) so that first value will always be less.
    int optimalO_util = 1000;
    
    // Iterate through every action
    for (pair<int, int> action : actions(board)) {
        // If AI playing as X, look for action that yields the highest possible utility (score)
        if (AI == X) {
            int max_value_action = min_value(result(board,action));
            // Compare utility to current highest
            if (max_value_action > optimalX_util) {
                optimalX_util = max_value_action;
                optimalX = action;
            }
            
        }
        // If AI playing as O, look for action that yields the lowest possible utility 
        else {
            int min_value_action = max_value(result(board,action));
            // Compare utility to current lowest
            if (min_value_action < optimalO_util) {
                optimalO_util = min_value_action;
                optimalO = action;
            }
        }
    }
    
    // Return the move that corresponds to the player the AI is playing as
    if (AI == X) {
        return optimalX;
    }
    else {
        return optimalO;
    }
}