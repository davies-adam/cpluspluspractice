#include <iostream>
#include <cctype>

using namespace std;

void prepare(const char *str, char *output) {
    int input_index = 0;
    int output_index = 0;
    char current;
    while(str[input_index] != '\0') {
        current = str[input_index];
        if(isalnum(current)) {
            if(islower(current)) {
                current = toupper(current);
            }
            output[output_index] = current;
            output_index++;
        }
        input_index++;
    }
    if(output_index % 2 != 0) {
        output[output_index] = 'X';
        output_index++;
    }
    output[output_index] = '\0';
    return;
}

bool contains_before(const char *str, char item, int end = 100000) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == item && i < end) {
            return true;
        }
        i++;
    }
    return false;
}

void grid(const char *codeword, char square[6][6]) {
    char flat_grid[36] = {};
    int codeword_index = 0;
    int grid_index = 0;
    while(codeword[codeword_index] != '\0') {
        if(!contains_before(codeword, codeword[codeword_index], codeword_index)) {
            flat_grid[grid_index] = codeword[codeword_index];
            grid_index++;
        }
        codeword_index++;
    }
    char insertion;
    for(int i = 0; i < 26; i++) {
        insertion = static_cast<char>(i + 'A');
        if(!contains_before(codeword, insertion)) {
            flat_grid[grid_index] = insertion;
            grid_index++;
        }
    }
    for(int i = 0; i < 10; i++) {
        insertion = static_cast<char>(i + '0');
        if(!contains_before(codeword, insertion)) {
            flat_grid[grid_index] = insertion;
            grid_index++;
        }
    }
    grid_index = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            square[i][j] = flat_grid[grid_index];
            grid_index++;
        }
    }
    return;
}

int find_row(const char square[6][6], char tile) {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(square[i][j] == tile) {
                return i;
            }
        }
    }
    return -1;
}

int find_column(const char square[6][6], char tile) {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(square[i][j] == tile) {
                return j;
            }
        }
    }
    return -1;
}

void bigram(const char square[6][6], char inchar1, char inchar2, char& outchar1, char& outchar2) {
    int row_of_first = find_row(square, inchar1);
    int column_of_second = find_column(square, inchar2);
    int column_of_first = find_column(square, inchar1);
    int row_of_second = find_row(square, inchar2);
    outchar1 = square[row_of_first][column_of_second];
    outchar2 = square[row_of_second][column_of_first];
    return;
}

bool encode(const char square[6][6], char *prepared, char *encoded) {
    if(*prepared == '\0') {
        *encoded = '\0';
        return true;
    }
    char first_output, second_output;
    bigram(square, *prepared, *(prepared + 1), first_output, second_output);
    *encoded = first_output;
    *(encoded + 1) = second_output;
    return encode(square, prepared + 2, encoded + 2);
}