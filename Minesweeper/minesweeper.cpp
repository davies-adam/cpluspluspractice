#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "minesweeper.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load mine positions from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || buffer[n] == '*' || buffer[n] == ' ' || buffer[n] == '?' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << "|";
  for (int i=0; i<9; i++) 
    cout << ( (data[i]=='.') ? ' ' : data[i]);
  cout << "|" << endl;
}

/* pre-supplied function to display a minesweeper board */
void display_board(const char board[9][9]) {
  cout << "  ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r);
  cout <<  endl;
  cout << " +---------+" << endl;
  for (int r=0; r<9; r++) 
    print_row(board[r],r);
  cout << " +---------+" << endl;
}

/* pre-supplied function to initialise playing board */ 
void initialise_board(char board[9][9]) {
  for (int r=0; r<9; r++)
    for (int c=0; c<9; c++)
      board[r][c] = '?';
}

bool is_complete(const char mines[9][9], const char revealed[9][9]) {
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if(mines[i][j] == '*' && revealed[i][j] != '*') {
                return false;
            }
            else if(mines[i][j] == '.' && !(revealed[i][j] == ' ' || isdigit(revealed[i][j]))) {
                return false;
            }
        }
    }
    return true;
}

int count_mines(const char *position, const char board[9][9]) {
    if(strlen(position) != 2) {
        return -1;
    }
    int row = position[0] - 'A';
    int column = position[1] - '0' - 1;
    int mine_count = 0;
    if(row != 0 && board[row - 1][column] == '*') {
        mine_count++;
    }
    if(row != 0 && column != 0 && board[row - 1][column - 1] == '*') {
        mine_count++;
    }
    if(column != 0 && board[row][column - 1] == '*') {
        mine_count++;
    }
    if(row != 8 && column != 0 && board[row + 1][column - 1] == '*') {
        mine_count++;
    }
    if(row != 8 && board[row+1][column] == '*') {
        mine_count++;
    }
    if(row != 8 && column != 8 && board[row+1][column+1] == '*') {
        mine_count++;
    }
    if(column != 8 && board[row][column+1] == '*') {
        mine_count++;
    }
    if(row != 0 && column != 8 && board[row-1][column+1] == '*') {
        mine_count++;
    }
    return mine_count;
}

MoveResult make_move(const char *position, const char mines[9][9], char revealed[9][9]) {
    int row = position[0] - 'A';
    int column = position[1] - '0' - 1;
    bool flagging = position[2] == '*';
    if(row < 0 || row > 8 || column < 0 || column > 8) {
        return INVALID_MOVE;
    }
    if(is_complete(mines, revealed)) {
        return SOLVED_BOARD;
    }
    if(!flagging && mines[row][column] == '*') {
        return BLOWN_UP;
    }
    if(revealed[row][column] == ' ' || isdigit(revealed[row][column]) || revealed[row][column] == '*') {
        return REDUNDANT_MOVE;
    }
    if(flagging) {
        revealed[row][column] = '*';
        return VALID_MOVE;
    }
    int mine_count = count_mines(position, revealed);
    if(mine_count == 0) {
        revealed[row][column] = ' ';
        for(int row_offset = -1; row_offset < 2; row_offset++) {
            for(int column_offset = -1; column_offset < 2; column_offset++) {
                int testing_row = row + row_offset;
                int testing_column = column + column_offset;
                if(testing_row >=0 && testing_row <= 8 && testing_column >= 0 && testing_column <= 8) {
                    char new_pos[3] = {static_cast<char>(testing_row + 'A'), static_cast<char>(testing_column + '0' + 1), '\0'};
                    make_move(new_pos, mines, revealed);
                }
            }
        }
    }
    else {
        revealed[row][column] = static_cast<char>(mine_count + '0');
    }
    return VALID_MOVE;
}

bool find_safe_move(char revealed[9][9], char *move) {
    for(int i = 0; i < strlen(move); i++){
        move[i] = '\0';
    }
    for(int row = 0; row < 9; row++) {
        for(int column = 0; column < 9; column++) {
            if(revealed[row][column] == '?') {
                for(int row_offset = -1; row_offset < 2; row_offset++) {
                    for(int column_offset = -1; column_offset < 2; column_offset++) {
                        int testing_row = row + row_offset;
                        int testing_column = column + column_offset;
                        if(testing_row >=0 && testing_row <= 8 && testing_column >= 0 && testing_column <= 8) {
                            if(isdigit(revealed[testing_row][testing_column])) {
                                int running_score = revealed[testing_row][testing_column] - '0';
                                for(int in_off_row = -1; in_off_row < 2; in_off_row++) {
                                    for(int in_off_col = -1; in_off_col < 2; in_off_col++) {
                                        int inner_row = in_off_row + testing_row;
                                        int inner_column = in_off_col + testing_column;
                                        if(revealed[inner_row][inner_column] == '*') {
                                            running_score--;
                                        }
                                    }
                                }
                                if(running_score == 0) {
                                    move[0] = static_cast<char>(row + 'A');
                                    move[1] = static_cast<char>(column + '0' + 1);
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            if(isdigit(revealed[row][column])) {
                int row_last, col_last;
                int unknown_neighbors = 0;
                for(int row_offset = -1; row_offset < 2; row_offset++) {
                    for(int column_offset = -1; column_offset < 2; column_offset++) {
                        int testing_row = row + row_offset;
                        int testing_column = column + column_offset;
                        if(testing_row >=0 && testing_row <= 8 && testing_column >= 0 && testing_column <= 8) {
                            if(revealed[testing_row][testing_column] == '?') {
                                unknown_neighbors++;
                                row_last = testing_row;
                                col_last = testing_column;
                            }
                        }
                    }
                }
                int known_value = revealed[row][column] - '0';
                if(known_value == unknown_neighbors) {
                    move[0] = static_cast<char>(row_last + 'A');
                    move[1] = static_cast<char>(col_last + '0' + 1);
                    move[2] = '*';
                    return true;
                }
            }
        }
    }       
    return false;
}