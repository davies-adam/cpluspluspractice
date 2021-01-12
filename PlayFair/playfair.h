#include <iostream>
#include <cctype>

// breaks given string into upper-case pairs into memory already allocated for second argument.
void prepare(const char *str, char *output);

// produces 6x6 playfair grid for given code word, ovewriting whatever is there.
void grid(const char *codeword, char square[6][6]);

// encrypts given pair of characters through provided playfair grid. outputs to 4th and 5th args.
void bigram(const char square[6][6], char inchar1, char inchar2, char& outchar1, char& outchar2);

// encodes series of upper-case pairs of letters through provided playfair code grid
bool encode(const char square[6][6], char *prepared, char *encoded);