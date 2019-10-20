void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool make_move(const char move[2], const char number, char board[9][9]);
bool save_board(const char *filename, const char board[9][9]);
bool solve_board(char board[9][9]);
bool solve_board(char board[9][9], int &back_count, int &depth);

