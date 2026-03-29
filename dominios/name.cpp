#include "name.hpp"

void Name::validate(string name) {
    if (name.empty() || name.length() > 10) {
        throw invalid_argument("Invalid size");
    }
    if (name[0] == ' ') {
        throw invalid_argument("Invalid format");
    }
    if (name[name.length() - 1] == ' ') {
        throw invalid_argument("Invalid format");
    }

    for(int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            throw invalid_argument("Invalid format");
        } 

        if (i+1 < name.length() && name[i] == ' ' && !isalpha(name[i+1])) {
            throw invalid_argument("Invalid format");
        }
    }
}

void Name::set(string name) {
    validate(name);
    this->name = name;
}

string Name::get() const {
    return name;
}