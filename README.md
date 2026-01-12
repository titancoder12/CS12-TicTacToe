CS12-TicTacToe
==============

Overview
--------
Simple command-line Tic-Tac-Toe game written in C++.

Files
-----
- main.cpp: Program entry point and game loop.
- tictactoe_helper.cpp: Helper functions for game logic and display.
- tictactoe_helper.h: Declarations for helper functions.

Code Structure
--------------
The game is split into a small driver and a helper module. `main.cpp` handles
startup, user prompts (player selection and difficulty), and loops the game
until the player quits. The bulk of the gameplay logic lives in
`tictactoe_helper.cpp` and is declared in `tictactoe_helper.h`. This helper
module provides utilities for rendering, parsing input, updating board state,
checking terminal states, and computing available actions.

AI (MiniMax)
------------
The AI move selection uses the minimax algorithm. Recursion is used to evaluate
the game tree: each possible move leads to a smaller subproblem that asks, “what
is the best outcome from this new board state?” The `minimax` function evaluates
all possible actions and chooses the move with the best outcome for the AI. It
relies on recursive `min_value` and `max_value` functions to explore the game
tree: one assumes the opponent plays optimally to minimize the score, while the
other assumes the AI plays optimally to maximize it. A `utility` function scores
terminal boards (win, loss, or tie), which becomes the base case that stops the
recursion.
