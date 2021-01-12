/*  This pre-supplied function looks up a given word in the dictionary
    of approved words. It is assumed that the input word is in uppercase.
    The function returns true if the word is in the dictionary.
    Otherwise returns false. */
bool dictionary_search(const char *word);

// determines whether given uppercase words form a valid step in a Doublet chain
bool valid_step(const char *first, const char *second);

// outputs NULL-terminated Doublet chain to given stream. does not check for validity.
bool display_chain(const char **chain, ostream& out);

// helper function for determing equality of strings recursively
bool str_equal(const char *first, const char *second);

// helper function for determing differences between strings
int num_diff(const char *first, const char *second);

// determines whether given series of steps forms a valid Doublet chain
bool valid_chain(const char **chain);

// recursively attempts to find valid Doublet chain to go from start to target. returns false if impossible.
// will only attempt to build a chain with as many steps as passed in argument max_steps
bool find_chain(const char *start_word, const char *target_word, const char **answer_chain, int max_steps, int branch_level = 0);