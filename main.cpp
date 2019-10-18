#include <iostream>
#include <cstdio>
#include <chrono>
#include <cstring>
#include "sudoku.h"

using namespace std;

void load_solve_and_display_board(const char filename[9], char board[9][9]);

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  // Should fail due to invalid position.
  cout << "Putting '9' into Ko is ";
  if (!make_move("Ko", '9', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should fail due to invalid digit.
  cout << "Putting 'a' into A1 is ";
  if (!make_move("A1", 'a', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  
  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should fail because position already has digit.
  cout << "Putting '3' into I8 is ";
  if (!make_move("I8", '3', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  
  // Should fail due to column check.
  cout << "Putting '1' into D4 is ";
  if (!make_move("D4", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should fail due to row check.
  cout << "Putting '9' into D8 is ";
  if (!make_move("D8", '9', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should fail due to box check.
  cout << "Putting '2' into D7 is ";
  if (!make_move("D7", '2', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  
  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  char board_two[9][9];
  load_board("easy-copy.dat", board_two);
  cout << '\n' << "Displaying Sudoku board_two with display_board():" << '\n';
  display_board(board_two);
  cout << "Done!" << "\n\n";
  
  cout << "=================== Question 4 ===================" << "\n\n";

  /* Load, solve and save easy board. */
  load_board("easy.dat", board);
  
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';
  
  if (save_board("easy-generated-solution.dat", board))
    cout << "Save board to 'easy-generated-solution.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  /* Load, solve and save medium board. */
  load_board("medium.dat", board);
  
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  if (save_board("medium-solution.dat", board))
    cout << "Save board to 'medium-solution.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  cout << "=================== Question 5 ===================" << "\n\n";

  char filename[9];
  strncpy(filename, "mystery1", 9);
  load_solve_and_display_board(filename, board);

  strncpy(filename,"mystery2", 9);
  load_solve_and_display_board(filename, board);

  strncpy(filename, "mystery3", 9);
  load_solve_and_display_board(filename, board);

  return 0;
}

/* This function loads a board from a file, solves and displays it. */
void load_solve_and_display_board(const char filename[9], char board[9][9]) {

  char full_filename[13];
  strncpy(full_filename, filename, 9);
  strcat(full_filename, ".dat");
  load_board(full_filename, board);

  cout << endl << "Displaying unsolved Sudoku board " << filename;
  cout << " with display_board():" << endl;
  display_board(board);
  
  chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
  bool board_solve = solve_board(board);
  chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
  chrono::duration<double> diff = end-start;
  
  if (board_solve) {
    cout << "The '" << filename << "' board has a solution:" << endl;
    display_board(board);
  } else {
    cout << "A solution cannot be found." << endl;
    display_board(board);
  }

  cout << "Time taken: " << diff.count() << " s" << endl << endl;
}
