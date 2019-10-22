#include <iostream>
#include <cstdio>
#include <chrono> // used for timing.
#include <cstring>
#include "sudoku.h"

using namespace std;

void load_easy_board_and_check_complete(char board[9][9]);
void solve_board_and_print_result(char filename[30], char board[9][9], bool should_analyse);
void load_solve_and_display_board(char filename[30], char board[9][9], bool should_analyse = false);
void attempt_move_and_display_board(const char move[2], const char digit, char board[9][9]);
void check_board_saves_correctly(char *filename, char board[9][9]);
void print_result_of_save_board(char *filename, char board[9][9]);

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

  load_easy_board_and_check_complete(board);

  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  // Should fail due to invalid position.
  attempt_move_and_display_board("k9",'8', board);
  attempt_move_and_display_board("J2",'4', board);
  attempt_move_and_display_board("11",'7', board);
  attempt_move_and_display_board("A0",'2', board);
  attempt_move_and_display_board("I10",'0', board);
  attempt_move_and_display_board("Io",'9', board);

  // Should fail due to invalid digit.
  attempt_move_and_display_board("A1",'0', board);
  attempt_move_and_display_board("A1",'a', board);  

  // Should work.
  attempt_move_and_display_board("I8",'1', board);
  attempt_move_and_display_board("H7",'4', board);
  attempt_move_and_display_board("A8",'7', board);
  
  // Should fail because position already has digit.
  attempt_move_and_display_board("I8",'3', board);
  
  // Should fail due to column check.
  attempt_move_and_display_board("D4",'1', board);
  
  // Should fail due to row check.
  attempt_move_and_display_board("D8",'9', board);
  
  // Should fail due to box check.
  attempt_move_and_display_board("D7",'2', board);
  
  cout << "=================== Question 3 ===================" << "\n\n";

  // should save correctly.
  char filename[40] = "easy";
  check_board_saves_correctly(filename, board);

  // should not save invalid board state.
  board[1][2] = 'r';
  strcpy(filename, "invalid");
  cout << "Check board with invalid character is not saved." << endl;
  print_result_of_save_board(filename, board);

  board[3][2] = '0';
  cout << "Check board with invalid '0' digit is not saved." << endl;
  print_result_of_save_board(filename, board);
  
  cout << "=================== Question 4 ===================" << "\n\n";

  /* load, solve and save easy board. */
  strcpy(filename, "easy");
  load_solve_and_display_board(filename, board);
  print_result_of_save_board(filename, board);
  
  /* load, solve and save medium board. */
  strcpy(filename, "medium");
  load_solve_and_display_board(filename, board);
  print_result_of_save_board(filename, board);

  /* these solves should fail because of an invalid board. */
  strcpy(filename, "invalid_1");
  load_board("easy.dat", board);
  board[1][2] = '0';
  solve_board_and_print_result(filename, board, false);

  strcpy(filename, "invalid_2");
  board[1][2] = 'a';
  solve_board_and_print_result(filename, board, false);
    
  cout << "=================== Question 5 ===================" << "\n\n";

  /* solve, display and analyse sudoku solves for each board. */
  bool should_analyse = true;
  strcpy(filename, "mystery1");
  load_solve_and_display_board(filename, board, should_analyse);

  strcpy(filename, "mystery2");
  load_solve_and_display_board(filename, board, should_analyse);

  strcpy(filename, "mystery3");
  load_solve_and_display_board(filename, board, should_analyse);

  return 0;
}

void load_easy_board_and_check_complete(char board[9][9]) {
  // load easy board.
  load_board("easy.dat", board);

  // shouldn't be complete.
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  // load easy solution board.
  load_board("easy-solution.dat", board);

  // should be complete.
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";
}

/* attempt move and display result on board. */
void attempt_move_and_display_board(const char move[2],
				    const char digit,
				    char board[9][9]) {

  // output whether move is valid.
  cout << "Putting '" << digit << "' into '" << move << "' is ";
  if (!make_move(move, digit, board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';

  /* display board to check move was undone if invalid, or updated
     board otherwise. */
  display_board(board);
}

/* visually checking if board saved correctly. */
void check_board_saves_correctly(char *filename, char board[9][9]) {

  // load board with file extension.
  char filename_extended[40];
  strcpy(filename_extended, filename);
  strcat(filename_extended, ".dat");
  load_board(filename_extended, board);

  // print message if save was successful / failure.
  print_result_of_save_board(filename, board);

  // display saved board.
  char board_two[9][9];
  load_board(filename, board_two);
  cout << endl << "Displaying '" << filename << "' board:" << endl;
  display_board(board_two);
  cout << "Done!" << endl << endl;
}

void solve_board_and_print_result(char filename[30], char board[9][9], bool should_analyse) {
  bool board_solve;
  chrono::duration<double> diff;
  int back_count = 0;
  int depth = 0;
  /* time profiling for sudoku solve. */
  if (should_analyse) {
    chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
    board_solve = solve_board(board, back_count, depth);
    chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
    diff = end-start;
  } else {
    board_solve = solve_board(board);
  }
  
  /* display solution board. */
  if (board_solve) {
    cout << "The '" << filename << "' board has a solution:" << endl;
    display_board(board);
  } else {
    cout << "A solution cannot be found." << endl;
    display_board(board);
  }

  /* print out time taken. */
  if (should_analyse) {
    cout << "Time taken: " << diff.count() << " s" << endl << endl;
    cout << "Recursion depth: " << depth << endl;
    cout << "Backwards recurse count: " << back_count << endl << endl;
  }
}

/* This function loads a board from a file, solves and displays it.
   It also optionally displays the time taken to solve it. */
void load_solve_and_display_board(char filename[30], char board[9][9], bool should_analyse) {

  /* get filename with .dat extension. */
  char full_filename[40];
  strcpy(full_filename, filename);
  strcat(full_filename, ".dat");
  load_board(full_filename, board);

  /* display unsolved board. */
  cout << endl << "Displaying unsolved Sudoku board " << filename;
  cout << " with display_board():" << endl;
  display_board(board);

  solve_board_and_print_result(filename, board, should_analyse);
}

/* save board to file helper. */
void print_result_of_save_board(char *filename, char board[9][9]) {
  strcat(filename, "-copy.dat");
  if (save_board(filename, board))
    cout << "Save board to '" << filename << "' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << endl;
}
