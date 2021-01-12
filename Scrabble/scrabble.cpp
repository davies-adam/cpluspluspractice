#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"

using namespace std;

int tile_score(char tile) {
    if(tile == ' ' || tile == '?') {
        return 0;
    }
    if(!isalpha(tile)) {
        return -1;
    }
    char standardized = toupper(tile);
    int score = 0;
    switch(standardized) {
        case 'A':
        case 'E':
        case 'I':
        case 'L':
        case 'N':
        case 'O':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
            score = 1;
            break;
        case 'D':
        case 'G':
            score = 2;
            break;
        case 'B':
        case 'C':
        case 'M':
        case 'P':
            score = 3;
            break;
        case 'F':
        case 'H':
        case 'V':
        case 'Y':
        case 'W':
            score = 4;
            break;
        case 'K':
            score = 5;
            break;
        case 'J':
        case 'X':
            score = 8;
            break;
        case 'Q':
        case 'Z':
            score = 10;
            break;
    }
    return score;
}

bool equiv_tiles(const char *first, const char *second) {
    if((*first == '\0' && *second == '\0')) {
        return true;
    }
    if(*first != *second && !(*first == '?' || *second == '?' || *first == ' ' || *second == ' ')) {
        if(*first == '\0' && !isalpha(*second)) {
            return true;
        }
        return false;
    }
    return equiv_tiles(first + 1, second + 1);
}

int next_free(const char *word) {
    int i = 0;
    while(i<strlen(word) && (isalpha(word[i]) || word[i] == '?' || word[i] == ' ')) {
        i++;
    }
    return i;
}

int count(const char *str, const char item) {
    int val = 0;
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == item) {
            val++;
        }
    }
    return val;
}

bool can_form(const char *word, const char *constant_word, const char *tiles, char *played_tiles, char *used) {
    if(equiv_tiles(constant_word, played_tiles)) {
        played_tiles[next_free(played_tiles)] = '\0';
        return true;
    }
    for(int i = 0; i < strlen(tiles); i++) {
        if((*word == tiles[i] || tiles[i] == ' ' || tiles[i] == '?')) {
            int times_used = count(used, tiles[i]);
            int times_avail = count(tiles, tiles[i]);
            if(!(times_used >= times_avail)) {
                played_tiles[next_free(played_tiles)] = tiles[i];
                used[next_free(used)] = tiles[i];
                if(can_form(word + 1, constant_word, tiles, played_tiles, used)) {
                    return true;
                }
            }
        }
    }
    strcpy(played_tiles, "");
    strcpy(used, "");
    return false;
}

bool can_form_word_from_tiles(const char *word, const char *tiles, char *played_tiles) {
    char *used = new char[strlen(tiles)];
    bool result = can_form(word, word, tiles, played_tiles, used);
    delete used;
    return result;
}

int compute_score(const char *played_tiles, ScoreModifier *modifiers) {
    int running_total = 0;
    int multiplier = 1;
    int i = 0;
    while(played_tiles[i] != '\0') {
        switch(modifiers[i]) {
            case(NONE):
                running_total += tile_score(played_tiles[i]);
                break;
            case(DOUBLE_LETTER_SCORE):
                running_total += 2 * tile_score(played_tiles[i]);
                break;
            case(TRIPLE_LETTER_SCORE):
                running_total += 3 * tile_score(played_tiles[i]);
                break;
            case(DOUBLE_WORD_SCORE):
                running_total += tile_score(played_tiles[i]);
                multiplier = 2;
                break;
            case(TRIPLE_WORD_SCORE):
                running_total += tile_score(played_tiles[i]);
                multiplier = 3;
                break;
        }
        i++;
    }
    int bonus = 0;
    if(i == 7) {
        bonus = 50;
    }
    return (running_total * multiplier) + bonus;
}

int highest_scoring_word_from_tiles(const char *tiles, ScoreModifier *score_modifiers, char *word) {
    ifstream file;
    file.open("words.txt");
    char line[50] = {};
    int top_score = 0;
    while(file.getline(line, 50)) {
        char working_space[50] = {};
        if(can_form_word_from_tiles(line, tiles, working_space)) {
            int new_score = compute_score(working_space, score_modifiers);
            if(new_score > top_score) {
                strcpy(word, working_space);
                top_score = new_score;
            }
        }
    }
    file.close();
    return top_score;
}