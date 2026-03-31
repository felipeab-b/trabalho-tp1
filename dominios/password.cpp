#include "password.hpp"

void Password::validate(std::string password) {
    if (password.empty() || password.length() > 6) {
        throw invalid_argument("Invalid size");
    }
    for (int i; i < password.length(); i++) {
        if (!isalnum(password[i])) throw invalid_argument("Invalid format");
        if (isdigit(password[i]) & isdigit(password[i + 1])) throw invalid_argument("Invalid format");
        if (isalpha(password[i]) & isalpha(password[i + 1])) throw invalid_argument("Invalid format");

        int min, mai, dig = 0;
        if (isdigit(password[i])) dig++;
        if (islower(password[i])) min++;
        if (isupper(password[i])) mai++;
        if (dig == 0 || min == 0 || mai == 0) throw invalid_argument("Invalid format");
    }
}

void Password::set(string password) {
    validate(password);
    this->password = password;
}

string Password::get() {
    return password;
}