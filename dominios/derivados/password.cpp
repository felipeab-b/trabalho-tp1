#include "password.hpp"

void Password::validate(std::string password) {
    if (password.length() != 6)
        throw std::invalid_argument("Invalid size");

    int min = 0, mai = 0, dig = 0;

    for (int i = 0; i < (int)password.length(); i++) {
        if (!isalnum(password[i]))
            throw std::invalid_argument("Invalid format");

        if (i < 5) {
            if (isdigit(password[i]) && isdigit(password[i + 1]))
                throw std::invalid_argument("Invalid format");
            if (isalpha(password[i]) && isalpha(password[i + 1]))
                throw std::invalid_argument("Invalid format");
        }

        if (isdigit(password[i])) dig++;
        if (islower(password[i])) min++;
        if (isupper(password[i])) mai++;
    }

    if (dig == 0 || min == 0 || mai == 0)
        throw std::invalid_argument("Invalid format");
}

