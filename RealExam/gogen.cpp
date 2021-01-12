#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

#include "common.h"
#include "mask.h"
#include "gogen.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which removes unprintable characters like carriage returns and newlines from strings */
void filter (char *line) {
  while (*line) {
    if (!isprint(*line))
     *line = '\0';
    line++;
  }
}

/* loads a Gogen board from a file */
char **load_board(const char *filename) {
  char **board = allocate_2D_array(5, 6);
  ifstream input(filename);
  assert(input);
  char buffer[512];
  int lines = 0;
  input.getline(buffer, 512);
  while (input && lines < HEIGHT) {
    filter(buffer);
    if (strlen(buffer) != WIDTH)
      cout << "WARNING bad input = [" << buffer << "]" << endl;
    assert(strlen(buffer) == WIDTH);
    strcpy(board[lines], buffer);
    input.getline(buffer, 512);
    lines++;
  }
  input.close();
  return board;
}

/* saves a Gogen board to a file */
bool save_board(char **board, const char *filename) {
  ofstream out(filename); 
  if (!out)
    return false;
  for (int r=0; r<HEIGHT; r++) {
    for (int c=0; c<WIDTH; c++) {
      out << board[r][c];
    }
    out << endl;
  }
  bool result = out.good();
  out.close();
  return result;
}

/* internal helper function for counting number of words in a file */
int count_words(const char *filename) {
  char word[512];
  int count = 0;
  ifstream in(filename);
  while (in >> word)
    count++;
  in.close();
  return count;
}

/* loads a word list from a file into a NULL-terminated array of char *'s */
char **load_words(const char *filename) {
  int count = count_words(filename);
  ifstream in(filename);
  assert(in);
  int n=0;
  char **buffer = new char *[count+1]; // +1 because we NULL terminate 
  char word[512];
  for (; (in >> word) && n<count; n++) {
    buffer[n] = new char[strlen(word) + 1];
    strcpy(buffer[n], word);
  }
  buffer[n] = NULL;
  in.close();
  return buffer;
}

/* prints a Gogen board in appropriate format */
void print_board(char **board) {
  for (int r=0; r<HEIGHT; r++) {
    for (int c=0; c<WIDTH; c++) {
      cout << "[" << board[r][c] << "]";
      if (c < WIDTH-1)
	cout << "--";
    }
    cout <<endl;
    if (r < HEIGHT-1) {
      cout << " | \\/ | \\/ | \\/ | \\/ |" << endl;
      cout << " | /\\ | /\\ | /\\ | /\\ |" << endl;
    }
  }
}

/* prints a NULL-terminated list of words */
void print_words(char **words) {
  for (int n=0; words[n]; n++) 
    cout << words[n] << endl;
}

/* frees up the memory allocated in load_board(...) */
void delete_board(char **board) {
  deallocate_2D_array(board, HEIGHT);
}

/* frees up the memory allocated in load_words(...) */
void delete_words(char **words) {
  int count = 0;
  for (; words[count]; count++);
  deallocate_2D_array(words, count);
}

bool get_position(char **board, char ch, int& row, int& column) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(board[i][j] == ch) {
                row = i;
                column = j;
                return true;
            }
        }
    }
    row = -1;
    column = -1;
    return false;
}

bool valid_solution(char **board, char **words) {
    int i = 0;
    while(words[i] != nullptr) {
        int j = 0;
        while(words[i][j] != '\0') {
            Mask m(false);
            int row, column;
            bool success = get_position(board, words[i][j], row, column);
            if(!success) {
                return false;
            }
            m.set_element(row, column, true);
            Mask n = m.neighbourhood();
            if(words[i][j+1] != '\0') {
                int next_row, next_column;
                bool inner_success = get_position(board, words[i][j+1], next_row, next_column);
                if(!inner_success) {
                    return false;
                }
                if(!n[next_row][next_column]) {
                    return false;
                }
            }
            j++;
        }
        i++;
    }
    return true;
}

void update(char **board, char ch, Mask& mask) {
    int row, column;
    if(get_position(board, ch, row, column)) {
        mask.set_all(false);
        mask.set_element(row, column, true);
        return;
    }
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(board[i][j] != '.') {
                mask.set_element(i, j, false);
            }
        }
    }
    if(mask.count() == 1) {
        int only_true_row, only_true_column;
        mask.get_position(true, only_true_row, only_true_column);
        board[only_true_row][only_true_column] = ch;
    }
}

void neighbourhood_intersect(Mask& one, Mask& two) {
    Mask first_n = one.neighbourhood();
    first_n.intersect_with(two);
    one = first_n;
    two = first_n;
    return;
}

bool solve_board(char **board, char **words) {
    Mask masks[25] = {};
    for(int i = 0; i < 25; i++) {
        update(board, static_cast<char>('A' + i), masks[i]);
    }
    int word_index = 0;
    while(words[word_index] != nullptr) {
        int inner_index = 0;
        while(words[word_index][inner_index+1] != '\0') {
            int mask_index = words[word_index][inner_index] - 'A';
            int next_mask_index = words[word_index][inner_index+1] - 'A';

            neighbourhood_intersect(masks[mask_index], masks[next_mask_index]);

            inner_index++;
        }
        word_index++;
    }
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j< WIDTH; j++) {
            for(int m = 0; m < 25; m++) {
                if(masks[m][i][j]) {
                   board[i][j] = static_cast<char>(m + 'A');
                }
            }
        }
    }
    return true;
}

int main() {
  Mask x, e;
  char** board = load_board("board-easy.txt");
  update(board, 'X', x);
  update(board, 'E', e);
  neighbourhood_intersect(x, e); // from BOXED
  e.print();
}