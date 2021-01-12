#include <iostream>

bool is_prefix(char const *prefix, char const *primary) {
    if(*prefix == '\0' && *primary != '\0') {
        return true;
    }
    if(*prefix == *primary) {
        return is_prefix(prefix + 1, primary + 1);
    }
    return false;
}

int substring_position(const char *sub, const char *primary, int position = 0) {
    if(*primary == '\0') {
        return -1;
    }
    if(is_prefix(sub, primary)) {
        return position;
    }
    return substring_position(sub, primary + 1, position + 1);
}

int main() {
    int x = substring_position("simple", "this is a simple exercise");
    std::cout << x;
}