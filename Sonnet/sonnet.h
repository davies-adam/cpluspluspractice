// RESET is a constant used by function rhyming_letter(...)
#define RESET NULL

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int number, char *output_word);

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending);

// count number of space-seperated words in sentence
int count_words(char const *str);

// finds phonetic encoding of terminal syllable of given uppercase word
bool find_phonetic_ending(char const *word, char *ending);

// pulls out rhyme scheme (in "abcdefabc" format) out of poem.
bool find_rhyme_scheme(const char *filename, char *scheme);

// classifies sonnet into Shakespearean, Petrarchan, or Spenserian on rhyme scheme.
// returns "Unknown" if unidentified
std::string identify_sonnet(const char *filename);