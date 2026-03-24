#include "role.hpp"

void Role::validate(string role){
    if (role != "DESENVOLVEDOR" && role != "MESTRE SCRUM" && role != "PROPRIETARIO DE PRODUTO") {
        throw invalid_argument("Invalid Role");
    }
}

void Role::set(string role){
    validate(role);
    this->role = role;
}

string Role::get() const {
    return this->role;
}