/*
 * File: tictactoe_helper.cpp
 * Author: Christopher Lin
 * Date: 2026-01-04
 *
 * GitHub: https://github.com/titancoder12/CS12-TicTacToe
 *
 * Description:
 * These are the helper functions for the tictactoe game.
 * Intended for the main function to run the game using functions declared in this file.
 */
 
#ifndef _tictactoe_helper_h
#define _tictactoe_helper_h

#include <string>
#include <vector>
#include <set>

using namespace std;

// Note: Extern keyword is used here to share access to the following consts (these are defined in 'tictactoe_helper.cpp')

// Size of tictactoe grid
extern const int SIZE;

// Character that repersents X
extern const char X;

// Character that repersents O
extern const char O;

/*
 * Function: run_game()
 * Description: Runs the game loop, including tasks like rendering the game frame, flushing previous frames, 
 *              indicating invalid inputs to players, and indicating terminal states.
 * Parameter(s): 
 *     human: char repersenting which player the human is.
 *     AI: char repersenting which player the AI is.
 *     board: A vector<vector<char> > of size SIZE filled with '.'; the starting state of the board.
 *     difficulty: A char repersenting the difficulty of the game being played (Easy, Normal, or Impossible).
 * Returns: Void.
 */
void run_game(char human, char AI, vector<vector<char> > board, char difficulty);

/*
 * Function: choose_player()
 * Description: Prompts the human with which player ('X' or 'O') they would like to play as.
 * Parameter(s): 
 *
 * Returns: Pair of characters; .first is the player of the human, .second is the player of the AI.
 */
pair<char, char> choose_player();

/*
 * Function: parse_input()
 * Description: Parses coordinate input (x, y) into two numbers. 
 * Parameter(s): 
 *     input: coordinate input in the form of a string.
 * Returns: Pair of numbers; .first repersents x, .second repersents y.
 */
pair<int, int> parse_input(string input);

/*
 * Function: render_board()
 * Description: Renders the board grid 
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: void.
 */
void render_board(vector<vector<char> > board);

/*
 * Function: empty_board()
 * Description: Creates an empty board of size SIZE full of space chars - ' '.
 * Parameter(s): 
 *     input: coordinate input in the form of a string
 * Returns: 2D vector of chars repersenting the board.
 */
vector<vector<char> > empty_board();

/*
 * Function: terminal()
 * Description: Checks if the current state of the board is a terminal one. 
 *              In other words, this function checks if the game is over.
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: Boolean value; true if game is over, false otherwise.
 */
bool terminal(vector<vector<char> > &board);

/*
 * Function: player()
 * Description: Returns which player has the current turn based on the board.
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: Char repersenting which player has the current turn.
 */
char player(vector<vector<char> > board);

/*
 * Function: winner()
 * Description: Returns which player has won the game.
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: Char repersenting which player has won. Returns ' ' as a sentinel value if no player has won.
 */
char winner(vector<vector<char> > &board);

/*
 * Function: utility()
 * Description: Returns 1 if X wins, -1 if O wins, 0 if tied.
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: Integer type; 1 if X wins, -1 if O wins, 0 if tied.
 */
int utility(vector<vector<char> > board);

/*
 * Function: actions()
 * Description: Based on the board, returns all available actions
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: Set of coordinates (type pair<int,int>) repersenting available actions. 
 *          Set type is used to ensure there are no duplicates.
 */
set<pair<int, int> > actions(vector<vector<char> > &board);

/*
 * Function: update()
 * Description: Update the board with given action
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 *     location: Pair of ints repersenting the coordinate at which the action should take place.
 *     team: The team (X or O) that the function should place at the location.
 * Returns: void
 */
void update(vector<vector<char> > &board, pair<int, int> location, char team);

/*
 * Function: result()
 * Description: Returns a copy of the board with specified action. 
 *              Similar to update function above but does not directly modify the board.
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 *     location: Pair of ints repersenting the coordinate at which the action should take place.
 *     team: The team (X or O) that the function should place at the location.
 * Returns: 2D vector of chars repersenting the board.
 */
vector<vector<char> > result(vector<vector<char> > board, pair<int, int> location);

/*
 * Function: min_value()
 * Description: Calculates the minimum possible utility (see utility function) of a board given optimal play.
 *              This is done using mutual recursive backtracking with max_value. 
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: Minimum possible utility of a board.
 */
int min_value(vector<vector<char> > board);

/*
 * Function: random_move()
 * Description: Selects a random move out of all possible moves
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: Coordinates; the location of the random move.
 */
pair<int, int> random_move(vector<vector<char> > &board);

/*
 * Function: max_value()
 * Description: Calculates the maximum possible utility (see utility function) of a board given optimal play.
 *              This is done using mutual recursive backtracking with min_value. 
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 * Returns: Maximum possible utility of a board.
 */
int max_value(vector<vector<char> > board);

/*
 * Function: minimax()
 * Description: Returns the optimal move for the AI. 
 *              It does this by looping over all possible actions and choosing the action with the minimum/Maximum
 *              possible utility, depending on which player the AI is. It calls min_value() and max_value() to do so.
 * Parameter(s): 
 *     board: 2D vector of chars repersenting the board.
 *     AI: Char repersenting which player the AI is.
 * Returns: Optimal move for the AI.
 */
pair<int, int> minimax(vector<vector<char> > board, char AI);

#endif