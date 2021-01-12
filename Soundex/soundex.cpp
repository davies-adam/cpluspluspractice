#include <iostream>

void encode(char const *surname, char *result, int length = 0) {
    if(length == 0) {
        result[0] = toupper(*surname);
        return encode(surname + 1, result, 1);
    }
    else if(length == 4) {
        return;
    }
    if(*surname == '\0') {
        if(length < 4) {
            result[length] = '0';
            return encode(surname, result, length + 1);
        }
        return;
    }
    char in = tolower(*surname);
    char out = '0';
    if(in == 'b' || in == 'f' || in == 'p' || in == 'v') {
        out = '1';
    }
    else if(in == 'c' || in == 'g' || in == 'j' || in == 'k' 
            || in == 'q' || in == 's' || in == 'x' || in == 'z') {
        out = '2';
    }
    else if(in == 'd' || in == 't') {
        out = '3';
    }
    else if(in == 'l') {
        out = '4';
    }
    else if(in == 'm' || in == 'n') {
        out = '5';
    }
    else if(in == 'r') {
        out = '6';
    }
    if(out != '0' && out != result[length - 1]) {
        result[length] = out;
        return encode(surname + 1, result, length + 1);
    }
    return encode(surname + 1, result, length);
}

bool compare(const char *first, const char *second) {
    if(*first != *second) {
        return false;
    }
    else if(*first == '\0' && *second == '\0') {
        return true;
    }
    return compare(first + 1, second + 1);
}

int count(char const  *surname, char const *sentence, int num = 0) {
    if(*sentence == '\0' || *surname == '\0') {
        return num;
    }
    char sentence_name[20] = {};
    int i = 0;
    while(toupper(*sentence) >= 'A' && toupper(*sentence) <= 'Z') {
        sentence_name[i] = *sentence;
        sentence++;
        i++;
    }
    char given_encoded[5] = {};
    char sentence_encoded[5] = {};
    encode(surname, given_encoded);
    encode(sentence_name, sentence_encoded);
    while(*sentence != '\0' &&
        (toupper(*sentence) < 'A' 
        || toupper(*sentence) > 'Z')) {
        sentence++;
    }
    if(compare(given_encoded, sentence_encoded)) {
        return count(surname, sentence, num + 1);
    }
    return count(surname, sentence, num);
}

int main() {
    auto sentence = "Linnings, Leasonne, Lesson and Lemon";
    std::cout << count("Leeson", sentence);
    return 0;
}