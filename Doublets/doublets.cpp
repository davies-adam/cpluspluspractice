#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

int num_diff(const char *first, const char *second) {
    int out = 0;
    while(*first != '\0' && *second != '\0') {
        if(*first != *second) {
            out++;
        }
        first++;
        second++;
    }
    return out;
}

bool valid_step(const char *first, const char *second) {
    if(!dictionary_search(first) || !dictionary_search(second)) {
        return false;
    }
    int differences = num_diff(first, second);
    if(differences > 1) {
        return false;
    }
    return !((*first == '\0' && *second != '\0') || (*first != '\0' && *second == '\0'));
}

bool display_chain(const char **chain, ostream& out) {
    int i = 0;
    while(chain[i] != NULL) {
        if(i == 0 || chain[i+1] == NULL) {
            out << chain[i] << endl;
        }
        else {
            int j = 0;
            while(chain[i][j] != '\0') {
                out << static_cast<char>(tolower(chain[i][j]));
                j++;
            }
            out << endl;
        }
        i++;
    }
    return !out.fail();
}

bool str_equal(const char *first, const char *second) {
    if(first == nullptr || second == nullptr || *first != *second) {
        return false;
    }
    else if(*first == '\0' && *second == '\0') {
        return true;
    }
    return str_equal(first + 1, second + 1);
}

bool valid_chain(const char **chain) {
    int i = 0;
    const char *previous = nullptr;
    while(chain[i] != NULL && chain[i+1] != NULL) {
        if(str_equal(chain[i], chain[i+1]) || str_equal(chain[i+1], previous)) {
            return false;
        }
        if(!valid_step(chain[i], chain[i+1])) {
            return false;
        }
        previous = chain[i];
        i++;
    }
    return true;
}

bool find_chain(const char *start_word, const char *target_word, const char **answer_chain, int max_steps, int branch_level) {
    if(branch_level == 0) {
        answer_chain[0] = start_word;
    }
    if(branch_level > max_steps || (num_diff(target_word, start_word) > (max_steps - branch_level))) {
        return false;
    }
    if(str_equal(start_word, target_word)) {
        return true;
    }
    int i = 0;
    while(start_word[i] != '\0') {
        for(int j = 1; j < 26; j++) {
            char *new_word = new char[20];
            strcpy(new_word, start_word);
            char changed_char = static_cast<char>(((new_word[i] - 'A' + j) % 26) + 'A');
            new_word[i] = changed_char;
            if(dictionary_search(new_word)) {
                if(find_chain(new_word, target_word, answer_chain, max_steps, branch_level + 1)) {
                    answer_chain[branch_level + 1] = new_word;
                    return true;
                }
            }
        }
        i++;
    }
    int backtrace_index = branch_level;
    while(answer_chain[backtrace_index] != NULL) {
        answer_chain[backtrace_index] = NULL;
        backtrace_index++;
    }
    return false;
}