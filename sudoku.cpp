#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* Question 1 */

/* this function returns true if all row positions are occupied by digits,
   and false otherwise */
bool is_complete_row(const char* row) {
  for (int column_index = 0; column_index < 9; column_index++) {
    if (row[column_index] < 49 || row[column_index] > 57)
      return false;
  }
  return true;
}

/* this function returns true if all board positions are occupied by digits,
   and false otherwise */
bool is_complete(const char board[9][9]) {
  for (int row_index = 0; row_index < 9; row_index++) {
    if (!is_complete_row(board[row_index]))
      return false;
  }
  return true;
}

/* Question 2 */

/* this function tests if the position exists on the sudoku grid. */
bool position_is_valid(const char position[2]) {
  return (position[0] > 64 && position[0] < 74 &&
	  position[1] > 48 && position[1] < 58);
}

/* this function tests if the digit already exists in a particular row. */
bool digit_exists_in_row(const char digit, const char *row) {
  for (int column_index = 0; column_index < 9; column_index++) {
    if (row[column_index] == digit)
      return true;
  }
  return false;
}

/* this function tests if the digit already exists in a particular column. */
bool digit_exists_in_column(const char digit,
			    const char board[9][9],
			    const int column_index) {
  for (int row_index = 0; row_index < 9; row_index++) {
    if (board[row_index][column_index] == digit)
      return true;
  }
  return false;
}

/* this function tests if the digit already exists in the
   3 x 3 box for a given position. */
bool digit_exists_in_box(const char digit,
		         const char board[9][9],
			 const int row_index,
			 const int column_index) {
  
  int box_row = (row_index / 3) * 3;
  int box_column = (column_index / 3) * 3;
  
  for (int row = box_row; row < box_row + 3; row++) {
    for (int column = box_column; column < box_column + 3; column++) {
      if (board[row][column] == digit)
	return true;
    }
  }
  
  return false;
}

/* this function checks if a digit already exists at a given board
   position. */
bool digit_exists_on_position(const char board[9][9],
			      const int row_index,
			      const int column_index) {
  char value = board[row_index][column_index];
  return (value > 48 && value < 58);
}

/* this function checks if the digit can be placed at a position. */ 
bool digit_is_allowed(const int row_index,
		      const int column_index,
		      const char digit,
		      char board[9][9]) {  

  if (digit_exists_on_position(board, row_index, column_index))
    return false;

  char *row = board[row_index];
  if (digit_exists_in_row(digit, row))
    return false;

  if (digit_exists_in_column(digit, board, column_index))
    return false;

  /* check if the digit exists in the 3 x 3 block for the position. */ 
  if (digit_exists_in_box(digit, board, row_index, column_index))
    return false;

  /* the digit can be placed at this position, so return true. */
  return true;
}

/* This function attempts to place a digit onto a Sudoku board at a given 
   position. If the position is invalid, or the placing of the digit at 
   position is invalid, the function returns false and the board is not
   altered. Otherwise, the function returns true and the board is updated. */
bool make_move(const char position[2], const char digit, char board[9][9]) {
  /* check if digit is in range. */
  if (digit < 49 || digit > 57)
    return false;

  if (!position_is_valid(position))
    return false;

  int row_index = position[0] - 65;
  int column_index = position[1] - 49;

  /* checks if digit is allowed according to game rules. */
  if (!digit_is_allowed(row_index, column_index, digit, board))
    return false;
  
  /* the position is valid, so we set the position's digit,
     and return true. */
  board[row_index][column_index] = digit;
  return true;
}

/* Question 3 */

/* This function saves the board into a file called 'filename'. */
bool save_board(const char *filename, const char board[9][9]) {

  ofstream out(filename);

  if (!out)
    return false;
  
  int row = 0;
  while (out && row < 9) {
    for (int column = 0; column < 9; column++) {
      if (board[row][column] != '.' && !digit_exists_on_position(board, row, column)) {
	out.close();
	return false;
      }
      out.put(board[row][column]);
      out.flush();
    }
    out << endl;
    out.flush();
    row++;
  }

  if (out.fail())
    return false;

  //the file has saved successfully
  
  return row == 9;
}		  

/* Question 4 */

/* this is a function which tests if the board only contains digits 1-9. */
bool board_is_valid(const char board[9][9]) {
  for (int row = 0; row < 9; row++) {
    for (int column = 0; column < 9; column++) {
      if (board[row][column] != '.' && !digit_exists_on_position(board, row, column)) {
	  return false;
	}
    }
  }
    return true;
}

/* this is a helper function to clear a square. */
bool set_square_empty(const char position[2], char board[9][9]) {

  if (!position_is_valid(position))
    return false;
  
  int row_index = position[0] - 65;
  int column_index = position[1] - 49;
  board[row_index][column_index] = '.';

  return true;
}

/* this function points the position to an empty square. */
void load_empty_position(char position[2], const char board[9][9]) {
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      if (board[r][c] == '.') {
	position[0] = r + 65;
	position[1] = c + 49;
      }	
    }
  }
}

/* this function returns true if the board can be solved and updates
   the board with the solution. Otherwise, it returns false. */
bool solve_board(char board[9][9]) {

  /* test if board contains only valid digits. */
  if (!board_is_valid(board))
    return false;
  
  /* if the board is complete, we have solved the board. */
  if (is_complete(board))
    return true;

  /* find the next empty position to make a move. */
  char position[2];
  load_empty_position(position, board);

  
  /* try each digit for the loaded position. */
  for (char digit = '1'; digit <= '9'; digit++) {

    /* make the move if it's possible. */
      if (make_move(position, digit, board)) {
	
	/*  return true if the move solves the board. */
	  if (solve_board(board))
	    return true;

	  /* clear the move if it doesn't solve the board. */
	  set_square_empty(position, board);
      }
  }
  /* the board has no solution, every digit has been tried. */
  
  return false;
}


/* this function is identical to the above, but measures the recursion
   depth and backward recurses of the function. I have kept both functions
   to ensure the function definition in the specification matches the 
   solution. */
bool solve_board(char board[9][9], int &back_count, int &depth) {

  /* test if board contains only valid digits. */
  if (!board_is_valid(board))
    return false;
  
  /* if the board is complete, we have solved the board. */
  if (is_complete(board))
    return true;

  /* find the next empty position to make a move. */
  char position[2];
  load_empty_position(position, board);

  
  /* try each digit for the loaded position. */
  for (char digit = '1'; digit <= '9'; digit++) {

    /* make the move if it's possible. */
      if (make_move(position, digit, board)) {

	/* increment recursion depth on recursive call. */
	depth++;
	
	/*  return true if the move solves the board. */
	if (solve_board(board, back_count, depth))
	  return true;

	/* backward recurse happened. */
	back_count++;
	depth--;
	
	/* clear the move if it doesn't solve the board. */
	set_square_empty(position, board);
      }
  }
  /* the board has no solution, every digit has been tried. */
  
  return false;
}
