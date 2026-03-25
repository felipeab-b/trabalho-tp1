#include "email.hpp"

void Email::validate(string email) {
    int pos = email.find('@');
    if (pos == string::npos) {
        throw invalid_argument("Invalid format");
    }

    if (email.find('@') != email.rfind('@')) {
        throw invalid_argument("Invalid format");
    }

    string local = email.substr(0, pos);
    if (local.empty()) {              
        throw invalid_argument("Invalid format");
    }

    if (local.length() > 64) {
        throw invalid_argument("Invalid size");
    }

    if (local[0] == '.' || local[0] == '-' || local[local.length() - 1] == '.' || local[local.length() - 1] == '-') {
        throw invalid_argument ("Invalid format");
    }

    for (int i = 0; i < local.length(); i++) {
        if (!isalnum(local[i]) && local[i] != '.' && local[i] != '-') {
            throw invalid_argument("Invalid format");
        }

        if (i+1 < local.length()) {
            if (local[i] == '.' || local[i] == '-') {
                if (!isalnum(local[i+1])) {
                    throw invalid_argument("Invalid format");
                }
        }
        }
    }

    string dominio = email.substr(pos+1);
        if (dominio.empty()) {            
    throw invalid_argument("Invalid format");
    }

    if (dominio.find('.') == string::npos) {
        throw invalid_argument("Invalid format");
    }

    if (dominio.length() > 255) {
        throw invalid_argument("Invalid size");
    }

    if (dominio[0] == '.' || dominio[0] == '-' || dominio[dominio.length() - 1] == '.' || dominio[dominio.length() - 1] == '-') {
        throw invalid_argument ("Invalid format");
    }

    for (int i = 0; i < dominio.length(); i++) {
        if (!isalnum(dominio[i]) && dominio[i] != '.' && dominio[i] != '-') {
            throw invalid_argument("Invalid format");
        }

        if (i+1 < dominio.length()) {
            if (dominio[i] == '.' && dominio[i+1] == '-') {
                throw invalid_argument("Invalid format");
            }

            if (dominio[i] == '-' && dominio[i+1] == '.') {
                throw invalid_argument("Invalid format");
            }

            if (dominio[i] == '.' && dominio[i+1] == '.') {
                throw invalid_argument("Invalid format");
            }
        }
    }
};

void Email::set(string email) {
    validate(email);
    this->email = email;
};

string Email::get() const {
    return email;
}