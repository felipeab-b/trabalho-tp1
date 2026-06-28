#include "password.hpp"
#include <cctype>
#include <stdexcept>

void Password::validate(std::string password) {
    if (password.length() != 6) {
        throw std::invalid_argument("Invalid size");
    }

    int min = 0, mai = 0, dig = 0;

    for (int i = 0; i < 6; i++) {
        char c = password[i];

        if (!isalnum(c)) {
            throw std::invalid_argument("Invalid format");
        }

        if (i < 5) {
            char next = password[i + 1];
            if ((isalpha(c) && isalpha(next)) || (isdigit(c) && isdigit(next))) {
                throw std::invalid_argument("Invalid format");
            }
        }

        if (islower(c)) min++;
        else if (isupper(c)) mai++;
        else if (isdigit(c)) dig++;
    }

    if (min == 0 || mai == 0 || dig == 0) {
        throw std::invalid_argument("Invalid format");
    }
}