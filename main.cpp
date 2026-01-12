/*
 * File: main.cpp
 * Author: Christopher Lin
 * Date: 2026-01-04
 *
 * Description:
 * Using functions declared in 'tictactoe_helper.h', 
 * determine if human player is playing as 'X' or 'O', then run the game loop
 */

#include "tictactoe_helper.h"
#include <iostream>
#include <set>
#include <stdlib.h>
#include <ctime>

using namespace std;

// Runs the game
int main() {
    // Seed rand
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Print welcome
    cout << "WELCOME TO TICTACTOE!" << endl;
    cout << "---------------------" << endl << endl;
    
    // Loop until user exits game
    while (true) {
        // Set difficulty of the game
        char difficulty;
        
        // Keep prompting user until valid input is given
        while (true) {
            cout << "Choose your difficulty ('E' for easy, 'N' for normal, 'I' for impossible): ";
            string input;
            getline(cin, input);
            
            // Check if input is valid
            if (input == "E" || input == "e" || input == "N" || input == "n" || input == "I" || input == "i") {
                // Assign difficulty as a char
                difficulty = toupper(input[0]);
                cout << endl;
                break;
            }
            
            cout << "Invalid input." << endl;
            cout << endl;
        }
        
        // Create empty board
        vector<vector<char> > board = empty_board();
        
        // Asks which player the user wants to be
        pair<char, char> data = choose_player();
        
        // Store info
        char human = data.first;
        char AI = data.second;
        
        // Margin
        cout << endl;
        
        // Run game loop
        run_game(human, AI, board, difficulty);
        
        // Prompt user if they would like to play again
        cout << endl << "Play again? (Y/N): ";
        string input;
        getline(cin, input);
        
        // Evaluate input
        if (input == "Y" || input == "y") {
            // Continue looping
            cout << endl;
            continue;
        }
        else {
            // Exit the loop
            break;
        }
    }
    
    return 0;
}