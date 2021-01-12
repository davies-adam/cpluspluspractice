#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

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

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

bool get_symbol_position(char **map, int height, int width, char target, int& r, int& c) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(map[i][j] == target) {
                r = i;
                c = j;
                return true;
            }
        }
    }
    r = -1;
    c = -1;
    return false;
}

char match_symbol(const char *filename, const char *name) {
    ifstream file;
    file.open(filename);
    if(file.fail()) {
        return '\0';
    }
    char return_char = '\0';
    char line[100] = {};
    while(file.getline(line, 100)) {
        bool any_diffs = false;
        int name_index = 0;
        int line_index = 2;
        while(line[line_index] != '\0') {
            if(name[name_index] != line[line_index]) {
                any_diffs = true;
            }
            name_index++;
            line_index++;
        }
        if(!any_diffs) {
            return_char = line[0];
        }
    }
    return return_char;
}

char get_symbol_for_station_or_line(const char *name) {
    char line_attempt = match_symbol("lines.txt", name);
    if(line_attempt != '\0') {
        return line_attempt;
    }
    char station_attempt = match_symbol("stations.txt", name);
    if(station_attempt != '\0') {
        return station_attempt;
    }
    return ' ';
}

void reverse_symbol(const char *filename, const char symbol, char *name) {
    ifstream file;
    file.open(filename);
    strcpy(name, "");
    if(file.fail()) {
        return;
    }
    char line[100] = {};
    while(file.getline(line, 100)) {
        if(line[0] == symbol) {
            int i = 0;
            while(line[i+2] != '\0') {
                name[i] = line[i+2];
                i++;
            }
            name[i] = '\0';
        }
    }
}

void identify_symbol(const char symbol, char *result) {
    reverse_symbol("lines.txt", symbol, result);
    if(strcmp("", result) == 0) {
        reverse_symbol("stations.txt", symbol, result);
    }
    return;
}

int validate_route(char **map, int height, int width, const char *start, char *route, char *destination) {
    char start_char = get_symbol_for_station_or_line(start);
    if(start_char == ' ' || ispunct(start_char)) {
        return ERROR_START_STATION_INVALID;
    }
    int current_row, current_column;
    bool initial_success = get_symbol_position(map, height, width, start_char, current_row, current_column);
    if(!initial_success) {
        return ERROR_START_STATION_INVALID;
    }
    Direction sequence[50];
    for(int i = 0; i < 50; i++) {
        sequence[i] = INVALID_DIRECTION;
    }
    int step_index = 0;
    int str_index = 0;
    while(route[str_index] != '\0') {
        char chunk[3] = {};
        if(route[str_index != ',']) {
            if(route[str_index + 1] != '\0' && route[str_index + 1] != ',') {
                chunk[0] = route[str_index];
                chunk[1] = route[str_index + 1];
                chunk[2] = '\0';
                str_index += 2;
            }
            else {
                chunk[0] = route[str_index];
                chunk[1] = '\0';
                str_index++;
            }
        }
        str_index++;
        Direction parsed = string_to_direction(chunk);
        /* if(parsed == INVALID_DIRECTION) {
            return ERROR_INVALID_DIRECTION;
        } */
        sequence[step_index] = parsed;
        step_index++;
    }
    Direction most_recent_direction = INVALID_DIRECTION;
    char current_line = '\0';
    int sequence_index = 0;
    int lines_taken = 0;
    while(sequence[sequence_index] != INVALID_DIRECTION) {
        switch(sequence[sequence_index]) {
            case(S):
                current_row++;
                break;
            case(SE):
                current_row++;
                current_column++;
                break;
            case(E):
                current_column++;
                break;
            case(NE):
                current_row--;
                current_column++;
                break;
            case(N):
                current_row--;
                break;
            case(NW):
                current_row--;
                current_column--;
                break;
            case(W):
                current_column--;
                break;
            case(SW):
                current_column--;
                current_row++;
                break;
        }
        if(current_row < 0 || current_row >= height || current_column < 0 || current_column >= width) {
            return ERROR_OUT_OF_BOUNDS;
        }
        char whatsthere = map[current_row][current_column];
        if(ispunct(whatsthere)) {
            if(current_line == '\0') {
                current_line = whatsthere;
                most_recent_direction = sequence[sequence_index];
            }
            else if(whatsthere != current_line) {
                return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
            }
            /* else if(most_recent_direction != sequence[sequence_index]) {
                return ERROR_BACKTRACKING_BETWEEN_STATIONS;
            } */
        }
        else if (whatsthere == ' ') {
            return ERROR_OFF_TRACK;
        }
        else {
            current_line = '\0';
            most_recent_direction = INVALID_DIRECTION;
            lines_taken++;
        }
        sequence_index++;
    }
    if(ispunct(map[current_row][current_column])) {
        return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
    }
    identify_symbol(map[current_row][current_column], destination);
    return lines_taken - 1;
}