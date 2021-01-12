#include "words.h"

void reverse(char const *str1, char *str2) {
    int counter = 0;
    while(*str1 != '\0') {
        str1++;
        counter++;
    }
    while(counter > 0) {
        str1--;
        *str2 = *str1;
        str2++;
        counter--;
    }
    return;
}

bool compare(char const *one, char const *two) {
    if(*one == '\0' && *two == '\0') {
        return true;
    }
    if(ispunct(*one) || *one == ' ') {
        return compare(one + 1, two);
    }
    if(ispunct(*two) || *two == ' ') {
        return compare(one, two + 1);
    }
    if(tolower(*one) != tolower(*two)) {
        return false;
    }
    return compare(one + 1, two + 1);
}

bool palindrome(const char *input) {
    int length = 0;
    const char *cursor = input;
    while(*cursor != '\0') {
        length++;
        cursor++;
    }
    char *reversed = new char[length + 1];
    reverse(input, reversed);
    bool result = compare(reversed, input);
    delete reversed;
    return result;
}

void letter_use(const char *str, int *results) {
    for(int i = 0; i < 26; i++) {
        results[i] = 0;
    }
    while(*str != '\0') {
        if(isalpha(*str)) {
            int position = toupper(*str) - 'A';
            results[position]++;
        }
        str++;
    }
}

bool anagram(const char *str1, const char *str2) {
    int first_letter_use[26] = {};
    int second_letter_use[26] = {};
    letter_use(str1, first_letter_use);
    letter_use(str2, second_letter_use);
    for(int i = 0; i < 26; i++) {
        if(first_letter_use[i] != second_letter_use[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    bool y = anagram("William Shakespeare", "I am not a weakish speller");
    std::cout << y;
    return 0;
}