#include <iostream>

bool is_prefix(const char *substring, const char *primary) {
    if(*primary == *substring) {
        if(*(substring + 1) == '\0') {
            return true;
        }
        return is_prefix(substring + 1, primary + 1);
    }
    return false;
}

int substring_position(const char *substring, const char *primary, int counter = 0) {
    if(*substring == '\0' || *primary == '\0') {
        return -1;
    }
    else if(is_prefix(substring, primary)) {
        return counter;
    }
    return substring_position(substring, primary + 1, counter + 1);
}

int main() {
    std::cout << substring_position("germany", "this is a simple exercise");
}