#include "name.hpp"

void Name::validate(std::string name) {
    if (name.empty() || name.length() > 10) {
        throw std::invalid_argument("Invalid size");
    }
    if (name[0] == ' ') {
        throw std::invalid_argument("Invalid format");
    }
    if (name[name.length() - 1] == ' ') {
        throw std::invalid_argument("Invalid format");
    }

    for(int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            throw std::invalid_argument("Invalid format");
        } 

        if (i+1 < name.length() && name[i] == ' ' && !isalpha(name[i+1])) {
            throw std::invalid_argument("Invalid format");
        }
    }
}
