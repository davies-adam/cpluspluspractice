#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <fstream>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

int count_words(char const *str) {
    int count = 1;
    if(*str == '\0') {
        return 0;
    }
    while(*str != '\0') {
        if(*str == ' ' && *(str + 1) != '\0') {
            count++;
        }
        str++;
    }
    return count;
}

bool find_phonetic_ending(char const *word, char *ending) {
    std::ifstream dict;
    dict.open("dictionary.txt");
    if(dict.fail()) {
        return false;
    }
    std::string line;
    while(std::getline(dict, line)) {
      int i = 0;
      bool no_diff = false;
      for(auto& each : line) {
        if(each != ' ') {
          if(each != word[i]) {
            break;
          }
          i++;
        }
        else {
          no_diff = true;
          break;
        }
      }
      if(no_diff && strlen(word) == i) {
        char reversed_answer[60] = {};
        int reversed_index = 0;
        for(int i = line.length() - 1; i >= 0; i--) {
          if(line[i] != ' ') {
            if(line[i] == 'A' || line[i] == 'E' || line[i] == 'I' || line[i] == 'O' || line[i] == 'U') {
              reversed_answer[reversed_index] = line[i];
              break;
            }
            reversed_answer[reversed_index] = line[i];
            reversed_index++;
          }
        }
        int length = reversed_index;
        for(int i = 0; i <= length; i++) {
          ending[i] = reversed_answer[reversed_index];
          reversed_index--;
        }
        return true;
      }
    }
    return false;
}

bool find_rhyme_scheme(const char *filename, char *scheme) {
  ifstream file;
  file.open(filename);
  if(file.fail()) {
    return false;
  }
  rhyming_letter(RESET);
  char line[100] = {};
  int line_num = 0;
  while(file.getline(line, 100)) {
    char word[35] = {};
    char ending[15] = {};
    int length = count_words(line);
    bool find_success = get_word(line, length, word);
    if(!find_success) {
      std::cout << "Error in finding last word in " << line << std::endl;
      return false;
    }
    bool phon_success = find_phonetic_ending(word, ending);
    if(!phon_success) {
      std::cout << "Error in finding ending for " << word << std::endl;
      return false;
    }
    scheme[line_num] = rhyming_letter(ending);
    line_num++;
  }
  file.close();
  return true;
}

bool same(const char *first, const char *second) {
  if((*first == '\0' && *second != '\0') || (*first != '\0' && *second == '\0')) {
    return false;
  }
  if(*first == '\0' && *second == '\0') {
    return true;
  }
  if(*first != *second) {
    return false;
  }
  return same(first + 1, second + 1);
}

std::string identify_sonnet(const char *filename) {
  char scheme[15] = {};
  bool success = find_rhyme_scheme(filename, scheme);
  if(success) {
    const char* shakes = "ababcdcdefefgg";
    const char* petr = "abbaabbacdcdcd";
    if(same("ababbcbccdcdee", scheme)) {
      return "Spenserian";
    }
    else if(same("abbaabbacdcdcd", scheme)) {
      return "Petrarchan";
    }
    else if(same("ababcdcdefefgg", scheme)) {
      return "Shakespearean";
    }
  }
  return "Unknown";
}