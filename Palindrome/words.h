#include <ctype.h>
#include <iostream>

// reverses strings. second parameter must already be allocated to
// hold a string of the same size as the first.
void reverse(char const *str1, char *str2);

// recrusively compares value of strings, ignoring case, punctuation, and spaces
bool compare(char const *one, char const *two);

// checks whether given string is palindromic, ignoring case, punctuation, and spaces
bool palindrome(const char *input);

// checks whether given string is anagram, ignoring case, punctuation, and spaces
bool palindrome(const char *input);